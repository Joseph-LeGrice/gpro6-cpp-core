#pragma once

#include "TypeNameMapping.h"
#include "RTTI.h"

struct ICreationAction
{
	virtual void DoAction(ITypedObject* obj) = 0;
};

class ITypedObject
{
friend class TypedObjectManager;
public:
	virtual const char* GetTypeName() = 0;
	
	InstanceID GetInstanceID()
	{
		return m_instanceId;
	}

	virtual void DoCreationActions() { };

private:
	InstanceID m_instanceId;

};