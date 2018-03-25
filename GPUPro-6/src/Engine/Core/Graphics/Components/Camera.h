#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"
#include "MyMath/Matrix/Matrix4x4.h"

struct Camera : IComponent
{
    Matrix4x4 m_projectionMatrix;
    //TODO: Add reference field for skybox?

    void SetOrthographic(float size, float depth, float aspectRatio);
	void SetPerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar);

	Camera(int componentIndex) : IComponent(componentIndex) { }

	static ComponentTypeID GetComponentType() {
		return 2;
	}
};
