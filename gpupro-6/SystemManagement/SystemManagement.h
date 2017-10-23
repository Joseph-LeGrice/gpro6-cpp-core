#pragma once

#include "SystemManagement/SystemConfiguration.hpp"

#include "SystemManagement/Systems/ConstantBufferManagementSystem.h"
#include "SystemManagement/Systems/GraphicsSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/Systems/MaterialManagementSystem.h"
#include "SystemManagement/Systems/SceneManagementSystem.h"
#include "SystemManagement/Systems/ShaderManagementSystem.h"
#include "SystemManagement/Systems/TimeSystem.h"

typedef SystemConfiguration<
    GraphicsSystem,
    MaterialManagementSystem,
    SceneManagementSystem,
    LightingSystem,
    ShaderManagementSystem,
    TimeSystem,
    ConstantBufferManagementSystem,
    InputSystem
> MainConfig;

class SystemManagement
{
public:
    static void Initialize();
    static int RunGameLoop();
    static void Deinitialize();

    template<class T>
    T* GetSystem();

private:
    static SystemManagement* s_instance;
   
    bool m_running;
    MainConfig m_config;

    SystemManagement();
    ~SystemManagement();
    SystemManagement(const SystemManagement&) = delete;

    void DoInitialize();
    int DoRunGameLoop();
    void DoDeinitialize();
};

template<class T>
T* SystemManagement::GetSystem()
{
    return GetInstance<T>(m_config);
}
