#include "stdafx.h"
#include "ImagingFactory.h"

#include <map>

ImagingFactory* ImagingFactory::s_instance = nullptr;

struct WICTranslate
{
	WICPixelFormatGUID guid;
	DXGI_FORMAT format;
};

static WICTranslate g_WICFormats[] = {
	{ GUID_WICPixelFormat128bppRGBAFloat,		DXGI_FORMAT_R32G32B32A32_FLOAT },
	{ GUID_WICPixelFormat64bppRGBAHalf,			DXGI_FORMAT_R16G16B16A16_FLOAT },
	{ GUID_WICPixelFormat64bppRGBA,				DXGI_FORMAT_R16G16B16A16_UNORM },
	{ GUID_WICPixelFormat32bppRGBA,				DXGI_FORMAT_R8G8B8A8_UNORM },
	{ GUID_WICPixelFormat32bppBGRA,				DXGI_FORMAT_B8G8R8A8_UNORM }, // (DXGI 1.1)
	{ GUID_WICPixelFormat32bppBGR,				DXGI_FORMAT_B8G8R8X8_UNORM }, // (DXGI 1.1)
	{ GUID_WICPixelFormat32bppRGBA1010102XR,	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM }, // (DXGI 1.1)
	{ GUID_WICPixelFormat32bppRGBA1010102,		DXGI_FORMAT_R10G10B10A2_UNORM },
	{ GUID_WICPixelFormat32bppRGBE,				DXGI_FORMAT_R9G9B9E5_SHAREDEXP },
	{ GUID_WICPixelFormat16bppBGRA5551,			DXGI_FORMAT_B5G5R5A1_UNORM }, // (DXGI 1.2)
	{ GUID_WICPixelFormat16bppBGR565,			DXGI_FORMAT_B5G6R5_UNORM }, // (DXGI 1.2)
	{ GUID_WICPixelFormat32bppGrayFloat,		DXGI_FORMAT_R32_FLOAT }, // The single-channel DXGI formats are all red channel, so you need HLSL shader swizzles such as .rrr to render these as grayscale.
	{ GUID_WICPixelFormat16bppGrayHalf,			DXGI_FORMAT_R16_FLOAT }, // The single-channel DXGI formats are all red channel, so you need HLSL shader swizzles such as .rrr to render these as grayscale.
	{ GUID_WICPixelFormat16bppGray,				DXGI_FORMAT_R16_UNORM }, // The single-channel DXGI formats are all red channel, so you need HLSL shader swizzles such as .rrr to render these as grayscale.
	{ GUID_WICPixelFormat8bppGray,				DXGI_FORMAT_R8_UNORM },  // The single-channel DXGI formats are all red channel, so you need HLSL shader swizzles such as .rrr to render these as grayscale.
	{ GUID_WICPixelFormat8bppAlpha,				DXGI_FORMAT_A8_UNORM },
	{ GUID_WICPixelFormat96bppRGBFloat,			DXGI_FORMAT_R32G32B32_FLOAT } // Windows 8 WIC
};

HRESULT ImagingFactory::GetPixelDataFromFile(_In_ std::wstring filepath, _Out_ DXGI_FORMAT& pixelFormat, _Out_ BYTE* pbBuffer, _Out_ UINT& bpp, UINT& width, UINT& height)
{
	Initialize();
	return s_instance->GetPixelDataFromFileInternal(filepath, pixelFormat, pbBuffer, bpp, width, height);
}

HRESULT ImagingFactory::GetPixelDataFromFileInternal(_In_ std::wstring filepath, _Out_ DXGI_FORMAT& pixelFormat, _Out_ BYTE* pbBuffer, _Out_ UINT& bpp, UINT& width, UINT& height)
{
	IWICBitmapDecoder* bitmapDecoder;
	IWICBitmapFrameDecode* bitmapFrame;
	WICPixelFormatGUID* bitmapPixelFormat;

	HRESULT hr = m_factory->CreateDecoderFromFilename(filepath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapDecoder);
	if (SUCCEEDED(hr))
	{
		hr = bitmapDecoder->GetFrame(0, &bitmapFrame);
		if (SUCCEEDED(hr))
		{
			hr = bitmapFrame->GetPixelFormat(bitmapPixelFormat);
			if (SUCCEEDED(hr))
			{
				hr = bitmapFrame->GetSize(&width, &height);
				if (SUCCEEDED(hr))
				{
					UINT bitsPerPixel = GetBitsPerPixel(*bitmapPixelFormat);
					UINT bufferStride = width * bitsPerPixel;
					const UINT bufferSize = bufferStride * height;
					BYTE* buf = new BYTE[bufferSize];

					bpp = bitsPerPixel;
					pbBuffer = buf;
					pixelFormat = GetNativeFormat(*bitmapPixelFormat);
					hr = bitmapFrame->CopyPixels(NULL, bufferStride, bufferSize, buf);
				}
			}
		}
	}
	
	SAFE_RELEASE(bitmapDecoder);
	SAFE_RELEASE(bitmapFrame);
	SAFE_DELETE(bitmapPixelFormat);

	return hr;
}

DXGI_FORMAT ImagingFactory::GetNativeFormat(WICPixelFormatGUID bitmapPixelFormat)
{
	for (size_t i = 0; i < _countof(g_WICFormats); i++)
	{
		if (memcmp(&g_WICFormats[i].guid, &bitmapPixelFormat, sizeof(WICPixelFormatGUID) == 0))
		{
			return g_WICFormats->format;
		}
	}
	return DXGI_FORMAT_UNKNOWN;
}

UINT ImagingFactory::GetBitsPerPixel(WICPixelFormatGUID bitmapPixelFormat)
{
	UINT bpp = 0;
	IWICComponentInfo* cinfo;
	IWICPixelFormatInfo* pfinfo;

	HRESULT hr = m_factory->CreateComponentInfo(bitmapPixelFormat, &cinfo);
	if (SUCCEEDED(hr))
	{
		hr = cinfo->QueryInterface(__uuidof(IWICPixelFormatInfo), reinterpret_cast<void**>(&pfinfo));
		if (SUCCEEDED(hr))
		{
			hr = pfinfo->GetBitsPerPixel(&bpp);
		}
	}

	SAFE_RELEASE(cinfo);
	SAFE_RELEASE(pfinfo);

	return bpp;
}

ImagingFactory::ImagingFactory()
{
}

ImagingFactory::~ImagingFactory()
{
	SAFE_RELEASE(m_factory);
}

HRESULT ImagingFactory::Initialize()
{
	if (s_instance != nullptr)
	{
		s_instance = new ImagingFactory();
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&s_instance->m_factory);
		if (FAILED(hr))
		{
			SAFE_DELETE(s_instance);
		}
	}
	else
	{
		return S_OK;
	}
}
