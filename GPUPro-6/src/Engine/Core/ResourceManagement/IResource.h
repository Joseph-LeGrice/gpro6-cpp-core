#pragma once

class IResource
{
public:
    IResource() : m_resourceId(-1) { }
    IResource(UINT ai) : m_resourceId(ai) { }
    
    virtual void Release() = 0;

    int GetResourceID()
    {
        return m_resourceId;
    }

private:
    int m_resourceId;
};
