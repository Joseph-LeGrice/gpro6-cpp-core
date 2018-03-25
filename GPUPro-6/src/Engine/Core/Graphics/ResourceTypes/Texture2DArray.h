#pragma once

#include "Engine/Core/ResourceManagement/IResource.h"
#include <vector>
#include <string>

struct ID3D11Texture2D;
struct FIBITMAP;
class ResourceReferences;

class Texture2DArray : public IResource
{
public:
	Texture2DArray::Texture2DArray(size_t resourceIndex, ResourceReferences& resourceReferences) :
		IResource(resourceIndex, resourceReferences) { }

    int GetMyResourceViewID();
    void InitializeWithBitmaps(std::vector<std::wstring> filepaths);
    
    virtual void Release() override;

	static ResourceTypeID GetResourceType()
	{
		return 7;
	}

private:
    int m_myShaderResourceViewId;
    std::vector<FIBITMAP*> m_bitmaps;
    ManualRelease<ID3D11Texture2D> m_pTextureArray;

    void CreateResources(UINT pitch, UINT width, UINT height);
};

