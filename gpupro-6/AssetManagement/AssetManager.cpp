#include "stdafx.h"
#include "AssetManagement/AssetManager.h"


AssetManager& GetAssetManager()
{
    static AssetManager* s_instance = new AssetManager();
    return *s_instance;
}
