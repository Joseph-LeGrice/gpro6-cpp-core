#pragma once
#pragma warning(push)
#pragma warning(disable:4100)

#include <map>
#include <type_traits>
#include <typeindex>

template<class... Ts>
class SystemManagerDefinition
{
public:
    template<class T>
    T* GetSystem()
    {
        return &std::get<T>(m_systems);
    }

    template<int I = 0, typename Func>
    inline typename std::enable_if<I == sizeof...(Ts), void>::type
        ForEachSystem(Func callback) { }

    template<int I = 0, typename Func>
    inline typename std::enable_if<I < sizeof...(Ts), void>::type
        ForEachSystem(Func callback)
    {
        ISystem* systemPointer = static_cast<ISystem*>(&std::get<I>(m_systems));
        callback(systemPointer);
        ForEachSystem<I + 1, Func>(callback);
    }

    SystemManagerDefinition() = default;
    ~SystemManagerDefinition() = default;
    SystemManagerDefinition(const SystemManagerDefinition&) = delete;

private:
    std::tuple<Ts...> m_systems;
};

#pragma warning(pop)
