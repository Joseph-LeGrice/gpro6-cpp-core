#pragma once
#include "Utilities/Logging.h"

template<class T>
class AutoRelease
{
public:
    AutoRelease()
    {
        m_pointer = nullptr;
    }

    ~AutoRelease()
    {
        ReleasePointer();
    }

    void ReleasePointer()
    {
        if (m_pointer != nullptr)
        {
            m_pointer->Release();
            m_pointer = nullptr;
        }
    }

    bool operator ==(void* p) { return m_pointer == p; }
    bool operator !=(void* p) { return m_pointer != p; }
    void operator =(T& r) { m_pointer = &r; }
    void operator =(T* pointer) { m_pointer = pointer; }
    T* operator ->() { return m_pointer; }

    operator T**() { return &m_pointer; }
    operator T*() { return m_pointer; }

private:
    T* m_pointer;
};

template<class T>
class ManualRelease
{
public:
    ManualRelease()
    {
        m_pointer = nullptr;
    }

    ~ManualRelease()
    {
        if (m_pointer != nullptr)
        {
            LogError("ManualRelease pointer was not manually released!");
        }
    }

    void ReleasePointer()
    {
        if (m_pointer != nullptr)
        {
            m_pointer->Release();
            m_pointer = nullptr;
        }
    }

    bool operator ==(void* p) { return m_pointer == p; }
    bool operator !=(void* p) { return m_pointer != p; }
    void operator =(T& r) { m_pointer = &r; }
    void operator =(T* p) { m_pointer = p; }
    T* operator ->() { return m_pointer; }

    operator T**() { return &m_pointer; }
    operator T*() { return m_pointer; }

private:
    T* m_pointer;
};
