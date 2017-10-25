#pragma once

#include <typeinfo>

class ISystem;

template<class S, class... L> struct SystemConfiguration;

template<class S>
struct SystemConfiguration<S>
{
    static_assert(std::is_base_of<ISystem, S>::value, "Must inherit from ISystem");
public:
    S m_systemInstance;
};

template<class S, class... L>
struct SystemConfiguration
{
    static_assert(std::is_base_of<ISystem, S>::value, "Must inherit from ISystem");
public:
    S m_systemInstance;
    SystemConfiguration<L...> m_nextSystem;
};

//------------------------------------------------------------------------------------
// Get Instance of System, registered under SystemConfiguration
//------------------------------------------------------------------------------------
template<class T, class S, class... L>
T* GetInstance(SystemConfiguration<S, L...>& systemConfig);

template<class T, template<class S> class SC, class S>
T* GetInstance(SystemConfiguration<S>& systemConfig)
{
    static_assert(std::is_base_of<ISystem, T>::value, "Must inherit from ISystem");
    if (std::is_same<S, T>::value)
    {
        return (T*)&systemConfig.m_systemInstance;
    }
    else
    {
        return nullptr;
    }
}

template<class T, class S, class... L>
T* GetInstance(SystemConfiguration<S, L...>& systemConfig)
{
    static_assert(std::is_base_of<ISystem, T>::value, "Must inherit from ISystem");
    if (std::is_same<S, T>::value)
    {
        return (T*)&systemConfig.m_systemInstance;
    }
    else
    {
        return nullptr;
    }
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Size (number of systems in a given SystemConfiguration
//------------------------------------------------------------------------------------
template<class S, class... L>
size_t Size(SystemConfiguration<S, L...>& systemConfig)
{
    return sizeof...(L)+1;
}
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Iterate through SystemConfiguration
//------------------------------------------------------------------------------------
//template<int i, class S, class... L>
//template<int i, template<class, class...> class sc>
//template<int i, SystemConfiguration<class, class...> sc, class S, class... L>
//struct SystemConfigurationIndexer;

//template<int i, class S, class... L>
//struct SystemConfigurationIndexer<i, SystemConfiguration<S, L...>>
//{
//    //using value_at = i == 0 ? sc.m_systemInstance : SystemConfigurationIndexer<i, 1, sc.m_nextSystem>::value_at;
//};

//template<int i, int thisI, class S, class...L>
//struct SystemConfigurationIndexer<i, SystemConfiguration<S, L...>>
//{
//    using value_at = i == thisI ? sc.m_systemInstance : SystemConfigurationIndexer<i, thisI + 1, sc.m_nextSystem>::value_at;
//};

/*
template<class S, class... L>
struct SystemConfigurationIterator;

template<class S>
struct SystemConfigurationIterator<SystemConfiguration<S>>
{
    SystemConfigurationIterator(SystemConfiguration<S> initialConfig)
    {
        m_currentSystemConfig = initialConfig;
    }

    ISystem* Current()
    {
        return m_currentSystemConfig.m_systemInstance;
    }

    SystemConfigurationIterator<S>* MoveNext()
    {
        return nullptr;
    }

    SystemConfiguration<S> m_currentSystemConfig;
};

template<class S, class... L>
struct SystemConfigurationIterator<SystemConfiguration<S, L...>>
{
    SystemConfigurationIterator(SystemConfiguration<S, L...> initialConfig)
    {
        m_currentSystemConfig = initialConfig;
    }

    ISystem* Current()
    {
        return m_currentSystemConfig.m_systemInstance;
    }

    SystemConfigurationIterator<L...>* MoveNext()
    {
        return &m_currentSystemConfig.m_nextSystem;
    }

    SystemConfiguration<S, L...> m_currentSystemConfig;
};


template<class S, class... L>
SystemConfiguration<L...>* GetNextConfiguration(SystemConfiguration<S, L...>& sc);

template<class S>
SystemConfiguration<S>* GetNextConfiguration(SystemConfiguration<S>& sc)
{
    return nullptr;
}

template<class S, class... L>
SystemConfiguration<L...>* GetNextConfiguration(SystemConfiguration<S, L...>& sc)
{
    return &sc.m_nextSystem;
}
*/
//------------------------------------------------------------------------------------