#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include <vector>
#include <string>

struct ID3D11Texture2D;
struct FIBITMAP;
class GraphicsDevice;

class Texture2DArray : public IResource
{
public:
    Texture2DArray(UINT ai, GraphicsDevice* gfxDevice);
    Texture2DArray();
    ~Texture2DArray();

    int GetMyResourceViewID();
    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    
    virtual void Release() override;

private:
	GraphicsDevice* m_gfxDevice;
    int m_myShaderResourceViewId;
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;

    void CreateResources(UINT pitch, UINT width, UINT height);
};

