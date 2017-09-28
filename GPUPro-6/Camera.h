#pragma once

#include "GraphicsSystem.h"
#include "Matrix4x4.h"

struct Camera
{
	size_t m_transformIndex; //TODO: Turn into Entity index and have this set automatically when you call AddComponent on an entity!
	Matrix4x4 m_projectionMatrix;

	static Camera New(bool isOrtho = false)
	{
		float viewportWidth = GraphicsSystem::Instance()->GetViewportWidth();
		float viewportHeight = GraphicsSystem::Instance()->GetViewportHeight();
		float aspectRatio = viewportWidth / viewportHeight; 
		
		Camera c;
		if (isOrtho)
		{
			c.m_projectionMatrix = OrthoProject(0.1f, 50.0f, aspectRatio);
		}
		else
		{
			float screenNear = 0.1f;
			float screenDepth = 100.0f;
			float fieldOfView = (float)D3DX_PI / 2.0f;

			c.m_projectionMatrix = PerspProject(fieldOfView, aspectRatio, screenNear, screenDepth);
		}

		return c;
	}

	static void Free(Camera& c) { }

	static Matrix4x4 Camera::OrthoProject(float size, float depth, float aspectRatio)
	{
		float halfSize = 0.5f * size;

		Matrix4x4 result;
		Matrix4x4::Identity(result);

		result.M11 = 2 / size;
		result.M22 = aspectRatio * 2 / size;
		result.M33 = 2 / (2 * depth);

		// For lower-left Camera Anchor:
		//result.M41 = -1;
		//result.M42 = -1;

		return result;
	}

	static Matrix4x4 Camera::PerspProject(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
	{
		Matrix4x4 result;
		Matrix4x4::Identity(result);

		float t = tan(fieldOfViewRadians / 2) * screenNear;
		float b = -t;
		float r = t * aspectRatio;
		float l = -t * aspectRatio;

		result.M11 = (2 * screenNear) / (r - l);
		result.M22 = (2 * screenNear) / (t - b);
		result.M31 = -(l + r) / (r - l);
		result.M32 = -(b + t) / (t - b);
		result.M33 = (screenFar + screenNear) / (screenFar - screenNear);
		result.M34 = 1;
		result.M43 = -(2 * screenFar * screenNear) / (screenFar - screenNear);
		result.M44 = 0;

		return result;
	}
};

