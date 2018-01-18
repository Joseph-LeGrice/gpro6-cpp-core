#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include "D3D11.h"
#include "FreeImage.h"
#include <string>

class Texture2D : public IResource
{
public:
    Texture2D(UINT resourceId);
	~Texture2D();

    UINT GetResourceViewID();
    void InitializeWithBitmap(const wchar_t* filepath);
    //void InitializeWithDimensions(UINT width, UINT width);
    
    virtual void Release() override;

private:
    UINT m_myShaderResourceViewId;
    FIBITMAP* m_bitmap;
	ManualRelease<ID3D11Texture2D> m_pTexture;
	
    void CreateResources();
};
