#pragma once

#include "ConstantBuffer.h"
#include "MyMath/Vector/Vector4.h"
#include "MyMath/Matrix/Matrix4x4.h"

struct PER_CAMERA_BUFFER
{
    Vector4 EyePos;
    Matrix4x4 View;
    Matrix4x4 Projection;
};

class PerCameraBuffer : public ConstantBuffer
{
public:
    PerCameraBuffer(GraphicsDevice& gfxDevice);
    void PushData(const PER_CAMERA_BUFFER& data);

protected:
    virtual UINT GetBufferSlot() override;
    virtual BindFlags GetBindFlags() override;
};