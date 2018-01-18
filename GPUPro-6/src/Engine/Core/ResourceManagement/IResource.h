#pragma once

class IResource
{
public:
    IResource() { m_resourceId = 999999; }
    IResource(UINT id) : m_resourceId(id) { }
    
    virtual void Release() = 0;

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
