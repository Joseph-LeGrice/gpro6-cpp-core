#include "stdafx.h"
#include "PerObjectBuffer.h"

PerObjectBuffer::PerObjectBuffer(GraphicsDevice& gfxDevice) :
    ConstantBuffer(gfxDevice)
{
    InitBuffer<PER_OBJECT_BUFFER>();
}

void PerObjectBuffer::PushData(const PER_OBJECT_BUFFER& data)
{
    UpdateBuffer<PER_OBJECT_BUFFER>(data);
}

UINT PerObjectBuffer::GetBufferSlot()
{
    return 1;
}

BindFlags PerObjectBuffer::GetBindFlags()
{
    return BIND_ALL;
}

