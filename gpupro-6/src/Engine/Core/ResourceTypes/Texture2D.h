#pragma once

#include "Engine/Core/RTTI/ITypedObject.h"
#include "d3d11.h"

#include <string>

struct Color;
struct FIBITMAP;


class Texture2D : public ITypedObject
{
public:
	REGISTER_TYPE(Texture2D);

    unsigned int Width();
    unsigned int Height();

    int GetInstanceViewID();
    void InitializeWithBitmap(const wchar_t* filepath);
    void InitializeWithDimensions(UINT width, UINT height);
    void SetPixels(Color cArray[], size_t arraySize);
    
	virtual void Finalize() override;
	

private:
    int m_myShaderResourceViewIndex = -1;
    FIBITMAP* m_bitmap = nullptr;
	ManualRelease<ID3D11Texture2D> m_pTexture;
	
    void Creates();
};
