#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include "D3D11.h"
#include "FreeImage.h"
#include <vector>
#include <string>

class Texture2DArray : public IResource
{
public:
    Texture2DArray(UINT resourceId);
    ~Texture2DArray();

    UINT GetMyResourceViewID();
    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    
    virtual void Release() override;

private:
    UINT m_myShaderResourceViewId;
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;

    void CreateResources(UINT pitch, UINT width, UINT height);
};

