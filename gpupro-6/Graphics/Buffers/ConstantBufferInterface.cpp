#include "stdafx.h"
#include "ConstantBufferInterface.h"

ConstantBufferInterface& GetConstantBufferInterface()
{
    static ConstantBufferInterface* s_buffer = new ConstantBufferInterface();
    return *s_buffer;
}
