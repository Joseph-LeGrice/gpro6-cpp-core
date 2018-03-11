#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include <string>

struct Color;
struct FIBITMAP;
struct ID3D11Texture2D;
class GraphicsDevice;

class Texture2D : public IResource
{
public:
    Texture2D(UINT ai, GraphicsDevice* gfxDevice);
    Texture2D();
    ~Texture2D();

    unsigned int Width();
    unsigned int Height();

    int GetResourceViewID();
    void InitializeWithBitmap(const wchar_t* filepath);
    void InitializeWithDimensions(UINT width, UINT height);
    void SetPixels(Color cArray[], size_t arraySize);
    virtual void Release() override;

private:
	GraphicsDevice* m_gfxDevice;
    int m_myShaderResourceViewId = -1;
    FIBITMAP* m_bitmap = nullptr;
	ManualRelease<ID3D11Texture2D> m_pTexture;
	
    void CreateResources();
};
