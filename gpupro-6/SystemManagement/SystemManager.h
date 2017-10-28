#pragma once

#include "SystemManagement/ISystem.h"

#include <map>
#include <type_traits>
#include <typeindex>

class SystemManager
{
public:
    template<class... Ts>
    static void Initialize()
    {
        s_instance->DoInitialize<Ts...>();
    }

    static int RunGameLoop()
    {
        return s_instance->DoRunGameLoop();
    }

    static void Deinitialize()
    {
        s_instance->DoDeinitialize();
        delete s_instance;
    }

    template<class T>
    static T* GetSystem()
    {
        if (s_instance->m_map.count(typeid(T)))
        {
            return static_cast<T*>(s_instance->m_map[typeid(T)]);
        }
        else
        {
            return nullptr;
        }
    }

    static void Quit()
    {
        s_instance->m_running = false;
    }

private:
    static SystemManager* s_instance;

    std::map<std::type_index, ISystem*> m_map;

    bool m_running;

    SystemManager();
    ~SystemManager();
    SystemManager(const SystemManager&) = delete;

    template<class T>
    void DoInitialize()
    {
        static_assert(std::is_base_of<ISystem, T>::value, "Not a system.");
        if (!m_map.count(typeid(T)))
        {
            T* newInstance = new T();
            m_map[typeid(T)] = newInstance;
            newInstance->Initialize();
        }
    }

    template<class T, class U, class... Ts>
    void DoInitialize()
    {
        static_assert(std::is_base_of<ISystem, T>::value, "Not a system.");
        if (!m_map.count(typeid(T)))
        {
            T* newInstance = new T();
            m_map[typeid(T)] = newInstance;
            newInstance->Initialize();
        }

        DoInitialize<U, Ts...>();
    }

    int DoRunGameLoop();
    void DoDeinitialize();
};

