#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include <vector>
#include <string>

struct ID3D11Texture2D;
struct FIBITMAP;


class Texture2DArray : public IResource
{
public:
    int GetMyResourceViewID();
    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    
    virtual void Release() override;

	static TypeID GetResourceType()
	{
		return 7;
	}

private:
    int m_myShaderResourceViewId;
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;

    void CreateResources(UINT pitch, UINT width, UINT height);
};

