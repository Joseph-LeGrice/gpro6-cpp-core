#include "stdafx.h"
//#include "PerlinNoise.h"
//#include "SimpleTextureResources.h"
//
//
//SimpleTextureResources::SimpleTextureResources()
//{
//	m_pTexture = nullptr;
//	m_resources = new std::vector<ID3D11ShaderResourceView*>();
//}
//
//
//SimpleTextureResources::~SimpleTextureResources()
//{
//	SAFE_RELEASE(m_pTexture);
//
//	for (ID3D11ShaderResourceView* rv : *m_resources)
//	{
//		SAFE_RELEASE(rv);
//	}
//	SAFE_DELETE(m_resources);
//}
//
//struct COLOR_DATA
//{
//	FLOAT R;
//	FLOAT G;
//	FLOAT B;
//	FLOAT A;
//};
//
//bool SimpleTextureResources::Initialize(ID3D11Device* device)
//{
//	const int texture_size = 64;
//
//	D3D11_TEXTURE2D_DESC desc;
//	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
//
//	desc.Width = texture_size;
//	desc.Height = texture_size;
//	desc.MipLevels = desc.ArraySize = 1;
//	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	desc.SampleDesc.Count = 1;
//	desc.Usage = D3D11_USAGE_DEFAULT;
//	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//
//	COLOR_DATA* color_data = new COLOR_DATA[texture_size * texture_size];
//	
//	//FIXME: Memory Leak here if something goes wrong?
//	//for (int x = 0; x < texture_size; x++)
//	//{
//	//	for (int y = 0; y < texture_size; y++)
//	//	{
//	//		color_data[y * texture_size + x].R = x / 32.0f;
//	//		color_data[y * texture_size + x].G = y / 32.0f;
//	//		color_data[y * texture_size + x].B = 0.0f;
//	//		color_data[y * texture_size + x].A = 1.0f;
//	//	}
//	//}
//
//	for (int x = 0; x < texture_size; x++)
//	{
//		for (int y = 0; y < texture_size; y++)
//		{
//			double noiseVal = PerlinNoise::noise(
//				(double)(x * 3.6 + 4 * texture_size * 2.75),
//				(double)(y * 2.5 + 2 * texture_size * 232.75),
//				(double)(x * y * texture_size * 23.45));
//			noiseVal = noiseVal * 0.23 + noiseVal;
//			//double noiseVal = PerlinNoise::octaveNoise(x, y, x*y, 4, 2.6);
//			//double noiseVal = PerlinNoise::noise(x, y, x*y);
//
//			color_data[y * texture_size + x].R = (FLOAT)noiseVal;
//			color_data[y * texture_size + x].G = (FLOAT)noiseVal;
//			color_data[y * texture_size + x].B = (FLOAT)noiseVal;
//			color_data[y * texture_size + x].A = 1.0f;
//		}
//	}
//
//	D3D11_SUBRESOURCE_DATA data;
//	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
//	data.pSysMem = color_data;
//	data.SysMemPitch = sizeof(COLOR_DATA) * texture_size;
//	data.SysMemSlicePitch = sizeof(COLOR_DATA) * texture_size * texture_size;
//
//	ID3D11ShaderResourceView* resourceView;
//	if (device->CreateTexture2D(&desc, &data, &m_pTexture) == S_OK && device->CreateShaderResourceView(m_pTexture, NULL, &resourceView) == S_OK)
//	{
//		m_resources->push_back(resourceView);
//		return true;
//	}
//	else
//	{
//		SAFE_RELEASE(m_pTexture);
//		SAFE_RELEASE(resourceView);
//		delete[] color_data;
//		return false;
//	}
//}
//
//std::vector<ID3D11ShaderResourceView *>* SimpleTextureResources::GetPSResources()
//{
//	return m_resources;
//}
