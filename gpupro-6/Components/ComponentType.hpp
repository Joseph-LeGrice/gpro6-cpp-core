#pragma once


typedef UINT16 ComponentType;

template<class T, UINT16 id, class InitFunctor>
struct ComponentRegistrationInfo
{
    static const UINT16 sc_componentId = id;
    InitFunctor s_initFunctor;
    int m_componentIndex;
    int m_entityIndex;
    T m_data;
};

template<class T, UINT16 id, class InitFunctor>
void InitializeComponentRegistrationInfo(ComponentRegistrationInfo<T, id, InitFunctor>& cri)
{
    cri.m_componentIndex = -1;
    cri.m_entityIndex = -1;
}

template<typename>
struct is_registered : std::false_type {};

template<class X, UINT16 Y, class InitFunctor>
struct is_registered<ComponentRegistrationInfo<X, Y, InitFunctor>> : std::true_type {};

template<class T>
UINT16 GetComponentType()
{
    static_assert(is_registered<T>::value, "T is not registered component type");
    return T::sc_componentId;
}
