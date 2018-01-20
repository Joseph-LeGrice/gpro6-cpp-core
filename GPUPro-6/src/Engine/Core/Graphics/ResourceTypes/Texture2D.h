#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include "D3D11.h"
#include "FreeImage.h"
#include <string>

class Texture2D : public IResource
{
public:
    Texture2D(UINT ai);
    Texture2D();
    ~Texture2D();

    int GetResourceViewID();
    void InitializeWithBitmap(const wchar_t* filepath);
    //void InitializeWithDimensions(UINT width, UINT width);
    
    virtual void Release() override;

private:
    int m_myShaderResourceViewId;
    FIBITMAP* m_bitmap = nullptr;
	ManualRelease<ID3D11Texture2D> m_pTexture;
	
    void CreateResources();
};
