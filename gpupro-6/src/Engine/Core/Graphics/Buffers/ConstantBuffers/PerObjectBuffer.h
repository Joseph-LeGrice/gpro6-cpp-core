#pragma once

#include "ConstantBuffer.h"
#include "MyMath/Matrix/Matrix4x4.h"

struct PER_OBJECT_BUFFER
{
    Matrix4x4 ModelViewProjection;
    Matrix4x4 ModelView;
};

class PerObjectBuffer : public ConstantBuffer
{
public:
    PerObjectBuffer(GraphicsDevice& gfxDevice);
    void PushData(const PER_OBJECT_BUFFER& data);

protected:
    virtual UINT GetBufferSlot() override;
    virtual BindFlags GetBindFlags() override;
};