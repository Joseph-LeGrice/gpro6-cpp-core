#pragma once
#pragma warning(push)
#pragma warning(disable: 4100)

#include <tuple>
#include "SkyboxDrawCommand.h"
#include "StandardOpaqueMaterialDrawCommand.h"
#include "StandardTransparentMaterialDrawCommand.h"

template<class... Commands>
class DrawCommandListImpl
{
public:
    template<class T>
    T* GetCommand() //FIXME
    {
        //return &std::get<T>(m_commands);
		return nullptr;
    }

    template <int I> inline
    typename std::enable_if<I == sizeof...(Commands), void>::type
    ExecuteAllCommands(Matrix4x4& view, Matrix4x4& proj) { }

    template <int I = 0> inline
    typename std::enable_if<I < sizeof...(Commands), void>::type
    ExecuteAllCommands(Matrix4x4& view, Matrix4x4& proj) //FIXME
    {
        //std::get<I>(m_commands).Draw(view, proj);
        //ExecuteAllCommands<I + 1>(view, proj);
    }

private:
    //std::tuple<Commands...> m_commands;
};

typedef DrawCommandListImpl<
    SkyboxDrawCommand,
    StandardOpaqueMaterialDrawCommand,
    StandardTransparentMaterialDrawCommand
> CommandList;

void InitializeCommandList();
CommandList& GetCommandList();
void DestroyCommandList();

#pragma warning(pop)