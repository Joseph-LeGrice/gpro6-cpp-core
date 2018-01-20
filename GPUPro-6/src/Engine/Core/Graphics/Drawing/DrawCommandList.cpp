#include "stdafx.h"
#include "DrawCommandList.h"

static CommandList* g_commandList = nullptr;

void InitializeCommandList()
{
    g_commandList = new CommandList();
}

CommandList& GetCommandList()
{
    return *g_commandList;
}

void DestroyCommandList()
{
    delete g_commandList;
}
