#include "stdafx.h"
#include "ResourceManager.h"

IResource* ResourceManager::CreateResource(TypeID typeId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	IResource* newResource = static_cast<IResource*>(tom->Create(typeId));
	newResource->Initialize();
	return newResource;
}


void ResourceManager::DestroyResource(TypeID typeId, InstanceID objId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	IResource* resource = static_cast<IResource*>(tom->GetInstance(typeId, objId));
	resource->Release();
	tom->Delete(typeId, objId);
}
