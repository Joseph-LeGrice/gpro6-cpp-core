#pragma once
#include "Engine/Core/Scripting/ManagedObject.h"
#include "Engine/Core/RTTI/ITypedObject.h"

class IResource : public ITypedObject
{
public:
	IResource();
	virtual ~IResource();

	virtual void Initialize();
	virtual void Release();
};
