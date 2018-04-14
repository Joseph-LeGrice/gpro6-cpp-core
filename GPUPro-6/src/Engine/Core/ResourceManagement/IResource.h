#pragma once

typedef uint16_t ResourceTypeID;

class IResource
{
	friend class ResourceManager;

public:
	IResource() { }
    
	virtual ~IResource() = default;
	virtual void Release() = 0;

	size_t GetResourceIndex();

private:
	size_t m_resourceIndex;
};
