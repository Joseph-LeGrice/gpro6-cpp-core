#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"

#include <string>

struct Color;
struct FIBITMAP;
struct ID3D11Texture2D;


class Texture2D : public IResource
{
public:
    unsigned int Width();
    unsigned int Height();

    int GetResourceViewID();
    void InitializeWithBitmap(const wchar_t* filepath);
    void InitializeWithDimensions(UINT width, UINT height);
    void SetPixels(Color cArray[], size_t arraySize);
    
	virtual void Release() override;

	virtual const char* GetTypeName() override
	{
		return TO_STRING(Texture2D);
	}

private:
    int m_myShaderResourceViewIndex = -1;
    FIBITMAP* m_bitmap = nullptr;
	ManualRelease<ID3D11Texture2D> m_pTexture;
	
    void CreateResources();
};
REGISTER_TYPE(Texture2D, 5)
