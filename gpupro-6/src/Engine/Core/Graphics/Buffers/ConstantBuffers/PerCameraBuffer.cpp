#include "stdafx.h"
#include "PerCameraBuffer.h"

UINT PerCameraBuffer::GetBufferSlot()
{
    return 0;
}

BindFlags PerCameraBuffer::GetBindFlags()
{
    return BIND_ALL;
}

PerCameraBuffer::PerCameraBuffer(GraphicsDevice& gfxDevice) :
    ConstantBuffer(gfxDevice)
{
    InitBuffer<PER_CAMERA_BUFFER>();
}

void PerCameraBuffer::PushData(const PER_CAMERA_BUFFER& data)
{
    UpdateBuffer<PER_CAMERA_BUFFER>(data);
}
