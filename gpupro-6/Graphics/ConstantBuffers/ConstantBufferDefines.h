#pragma once

#include "ConstantBuffer.h"
#include "Matrix4x4.h"

#define NUM_BUFFERS 1

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

typedef ConstantBuffer<PER_OBJECT_BUFFER, 0, NUM_BUFFERS, BIND_ALL> PerObjectBuffer;