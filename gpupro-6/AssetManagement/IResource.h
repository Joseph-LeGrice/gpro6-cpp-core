#pragma once

class IResource
{
public:
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