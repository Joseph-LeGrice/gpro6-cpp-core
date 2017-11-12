#pragma once

#include <type_traits>

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

// is_registered: checks if a given type is ComponentRegistrationInfo
template<class... X>
struct is_registered;

template<class X>
struct is_registered<X> : std::false_type {};

template<class X, UINT16 Y, class InitFunctor>
struct is_registered<ComponentRegistrationInfo<X, Y, InitFunctor>> : std::true_type {};

// is_registered_typelist: checks if a given list of types s ComponentRegistrationInfo
template<typename... X>
struct is_registered_typelist;

template<class X, class... T>
struct is_registered_typelist<X, T...> : std::false_type {};

template<class X, UINT16 Y, class InitFunctor>
struct is_registered_typelist<ComponentRegistrationInfo<X, Y, InitFunctor>> : std::true_type {};

template<class X, UINT16 Y, class InitFunctor, class... T>
struct is_registered_typelist<ComponentRegistrationInfo<X, Y, InitFunctor>, T...>
{
    static constexpr bool value = is_registered_typelist<T...>::value;
};


template<class T>
UINT16 GetComponentType()
{
    static_assert(is_registered<T>::value, "T is not registered component type");
    return T::sc_componentId;
}
