#pragma once

#include <tuple>
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"

#include "MyMath/Matrix/Matrix4x4.h"
#include "MyMath/Vector/Vector2.h"
#include "MyMath/Vector/Vector4.h"

struct PER_CAMERA_BUFFER
{
    Vector4 EyePos;
    Matrix4x4 View;
    Matrix4x4 Projection;
};

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

const int MATERIAL_BUFFER_SLOT = 2;

typedef ConstantBuffer<PER_CAMERA_BUFFER, 0, BIND_ALL> PerCameraBuffer;
typedef ConstantBuffer<PER_OBJECT_BUFFER, 1, BIND_ALL> PerObjectBuffer;

typedef ConstantBufferInterfaceImpl<
    PerCameraBuffer,
    PerObjectBuffer
> ConstantBufferInterface;

extern ConstantBufferInterface* s_buffer;

void InitConstantBufferInterface();
ConstantBufferInterface& GetConstantBufferInterface();
void DestroyConstantBufferInterface();