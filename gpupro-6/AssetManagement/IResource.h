#pragma once

class IResource
{
public:
    IResource(UINT id) : m_resourceId(id) { }
    
    UINT GetResourceID()
    {
        return m_resourceId;
    }

protected:
    ~IResource()
    {

    }

private:
    UINT m_resourceId;
};