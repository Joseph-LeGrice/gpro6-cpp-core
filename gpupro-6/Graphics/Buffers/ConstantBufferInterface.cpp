#include "stdafx.h"
#include "ConstantBufferInterface.h"

ConstantBufferInterface* s_buffer;

void InitConstantBufferInterface()
{
    s_buffer = new ConstantBufferInterface();
}

ConstantBufferInterface& GetConstantBufferInterface()
{
    return *s_buffer;
}

void DestroyConstantBufferInterface()
{
    delete s_buffer;
}
