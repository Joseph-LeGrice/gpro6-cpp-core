#pragma once

#include "Engine/Core/RTTI/ITypedObject.h"
#include <vector>
#include <string>

struct ID3D11Texture2D;
struct FIBITMAP;


class Texture2DArray : public ITypedObject
{
REGISTER_TYPE(Texture2DArray)
public:
    int GetMyResourceViewID();
    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    
    virtual void Finalize() override;

private:
    int m_myShaderResourceViewId;
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;

    void Creates(UINT pitch, UINT width, UINT height);
};

