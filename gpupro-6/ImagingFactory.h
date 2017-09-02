#pragma once

#include <string>

struct IWICImagingFactory;

class ImagingFactory
{
public:
	static HRESULT GetPixelDataFromFile(_In_ std::wstring filepath, _Out_ DXGI_FORMAT& pixelFormat, _Out_ BYTE* pbBuffer, _Out_ UINT& bufSize, UINT& width, UINT& height);

private:
	static ImagingFactory* s_instance;

	IWICImagingFactory* m_factory;

	ImagingFactory();
	~ImagingFactory();

	static HRESULT Initialize();
	HRESULT GetPixelDataFromFileInternal(_In_ std::wstring filepath, _Out_ DXGI_FORMAT& pixelFormat, _Out_ BYTE* pbBuffer, _Out_ UINT& bufSize, UINT& width, UINT& height);
	DXGI_FORMAT& GetNativeFormat(WICPixelFormatGUID bitmapPixelFormat);
	UINT GetBitsPerPixel(WICPixelFormatGUID bitmapPixelFormat);
};

