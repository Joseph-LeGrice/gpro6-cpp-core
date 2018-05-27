#pragma once

#include "TypeNameMapping.h"
#include "RTTI.h"

class ITypedObject
{
friend class TypedObjectManager;
public:
	virtual void Establish() { }
	virtual void Finalize() { }

	virtual TypeID GetTypeID() = 0;
	InstanceID GetInstanceID()
	{
		return m_instanceId;
	}

private:
	InstanceID m_instanceId = InvalidInstanceID;
};