#pragma once

#include "AssetManagement/IResource.h"
#include "D3D11.h"
#include "FreeImage.h"
#include <string>

class Texture2D : public IResource
{
public:
    Texture2D(UINT resourceId);
	~Texture2D();

    void InitializeWithBitmap(const wchar_t* filepath);
    //void InitializeWithDimensions(UINT width, UINT width);
    void BindResource(UINT resourceIndex);

    virtual void Release() override;

private:
    FIBITMAP* m_bitmap;
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_resourceView;
    
    void CreateResources();
};
