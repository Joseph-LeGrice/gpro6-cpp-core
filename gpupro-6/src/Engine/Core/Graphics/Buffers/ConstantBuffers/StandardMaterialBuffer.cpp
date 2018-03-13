#include "stdafx.h"
#include "StandardMaterialBuffer.h"


StandardMaterialBuffer::StandardMaterialBuffer(GraphicsDevice& gfxDevice) :
    ConstantBuffer(gfxDevice)
{
    InitBuffer<MATERIAL_BUFFER_CONTAINER>();
}

void StandardMaterialBuffer::PushData(const MATERIAL_BUFFER_CONTAINER& data)
{
    UpdateBuffer<MATERIAL_BUFFER_CONTAINER>(data);
}

UINT StandardMaterialBuffer::GetBufferSlot()
{
    return 2;
}

BindFlags StandardMaterialBuffer::GetBindFlags()
{
    return BIND_ALL;
}
