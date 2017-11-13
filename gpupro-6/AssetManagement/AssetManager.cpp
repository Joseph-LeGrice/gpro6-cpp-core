#include "stdafx.h"
#include "AssetManagement/AssetManager.h"

AssetManager* s_instance = new AssetManager();

AssetManager& GetAssetManager()
{
    return *s_instance;
}

void DestroyAssetManager()
{
    delete s_instance;
}
