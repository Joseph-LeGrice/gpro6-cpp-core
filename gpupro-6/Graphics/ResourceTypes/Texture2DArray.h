#pragma once

#include "AssetManagement/IResource.h"
#include "D3D11.h"
#include "FreeImage.h"
#include <vector>
#include <string>

class Texture2DArray : public IResource
{
public:
    Texture2DArray(UINT resourceId);
    ~Texture2DArray();

    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    void BindResource(UINT resourceIndex);

    virtual void Release() override;

private:
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;
    ManualRelease<ID3D11ShaderResourceView> m_resourceView;

    void CreateResources(UINT pitch, UINT width, UINT height);
};

