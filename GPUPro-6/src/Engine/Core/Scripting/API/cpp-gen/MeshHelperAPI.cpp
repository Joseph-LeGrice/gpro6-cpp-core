#include "stdafx.h"
#include "MeshHelperAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"
#include "Engine/Core/Scripting/MonoMarshallHelpers.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Utilities/MeshHelper.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/ResourceTypes/Mesh.h"

// ## Generated Code ##
extern void GPro::MeshHelperAPI::RegisterCalls()
{
	mono_add_internal_call("MeshHelper::CreateSphereUV_Internal", GPro::MeshHelperAPI::CreateSphereUV_Internal);
	mono_add_internal_call("MeshHelper::CreateQuad_Internal", GPro::MeshHelperAPI::CreateQuad_Internal);
}


// ## Generated Code ##

extern MonoObject* GPro::MeshHelperAPI::CreateSphereUV_Internal()
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Mesh* sphereMesh = MeshHelper::SphereUV(*tom);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* sphereMeshManaged = ntmip->GetManagedObject(sphereMesh->GetTypeID(), sphereMesh->GetInstanceID());
	return sphereMeshManaged->GetManagedObject();
}

extern MonoObject* GPro::MeshHelperAPI::CreateQuad_Internal()
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	Mesh* sphereMesh = MeshHelper::Quad(*tom);
	NativeToManagedInstanceMap* ntmip = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* sphereMeshManaged = ntmip->GetManagedObject(sphereMesh->GetTypeID(), sphereMesh->GetInstanceID());
	return sphereMeshManaged->GetManagedObject();
}
