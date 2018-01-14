#pragma once

template<class T>
class AutoPointer
{
public:
    AutoPointer()
    {
        m_pointer = nullptr;
    }

    ~AutoPointer()
    {
        DeletePointer();
    }

    void DeletePointer()
    {
        if (m_pointer != nullptr)
        {
            delete m_pointer;
            m_pointer = nullptr;
        }
    }

    bool operator ==(void* p) { return m_pointer == p; }
    bool operator !=(void* p) { return m_pointer != p; }
    void operator =(T& r) { m_pointer = &r; }
    void operator =(T* pointer) { m_pointer = pointer; }
    T* operator ->() { return m_pointer; }

    operator T*() { return m_pointer; }
    operator T**() { return &m_pointer; }

private:
    T* m_pointer;
};
