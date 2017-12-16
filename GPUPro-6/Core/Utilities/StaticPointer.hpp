#pragma once

template<class T>
class StaticPointer
{
public:
    StaticPointer()
    {
    }

    ~StaticPointer()
    {
        delete s_pointer;
    }

    T* operator->()
    {
        return s_pointer;
    }

private:
    T* const s_pointer = new T();
};
