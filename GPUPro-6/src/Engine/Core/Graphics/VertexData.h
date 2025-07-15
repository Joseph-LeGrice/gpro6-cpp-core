#pragma once

#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "MyMath/Vector/Vector3.h"
#include "MyMath/Vector/Vector2.h"

struct VertexData
{
	Vector3 vertexPosition;
	Vector3 tangent;
	Vector3 binormal;
	Vector3 normal;
	Vector2 uv;
};