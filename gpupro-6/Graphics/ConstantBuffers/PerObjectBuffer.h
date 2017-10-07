#pragma once

#include "ConstantBuffer.h"
#include "Matrix4x4.h"

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

typedef ConstantBuffer<PER_OBJECT_BUFFER> PerObjectBuffer;