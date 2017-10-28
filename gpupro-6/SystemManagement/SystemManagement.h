#pragma once

#include "SystemManagement/SystemConfiguration.hpp"

#include "SystemManagement/Systems/GraphicsSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/Systems/TimeSystem.h"

#include <map>
#include <type_traits>
#include <typeindex>

//typedef SystemConfiguration<
//    GraphicsSystem,
//    LightingSystem,
//    TimeSystem,
//    InputSystem
//> MainConfig;


//TODO: Make SystemManagement more easily extensible with code generation,
//      or some other way of registering systems as modules that can be retrieved
//      Bear in mind need for concurrency in the future.
class SystemManagement
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
    static SystemManagement* s_instance;

    std::map<std::type_index, ISystem*> m_map;

    bool m_running;

    SystemManagement();
    ~SystemManagement();
    SystemManagement(const SystemManagement&) = delete;

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

