#include "stdafx.h"
#include "MouseRotateSystem.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "SceneManagementSystem.h"

MouseRotateSystem::MouseRotateSystem() : m_velocity(0.0f), m_index(-1), m_hasIndex(false)
{
}


MouseRotateSystem::~MouseRotateSystem()
{
}

void MouseRotateSystem::SetTransformIndexToRotate(size_t index)
{
	m_hasIndex = true;
	m_index = index;
}

void MouseRotateSystem::VariableTick()
{
	if (m_hasIndex)
	{
		ComponentArray<Transform>& tca = SceneManagementSystem::Instance()->GetSceneGraph()->m_transforms;
		Transform* const allTransforms = tca.GetArrayPointer();
		const MouseInput& mi = InputSystem::Instance()->GetMouse();

		if (mi.GetMouseButton(0))
		{
			Transform& t = allTransforms[m_index];
			Vector2 deltaMove = mi.GetDeltaMousePosition() * m_speed * TimeSystem::Instance()->DeltaTimeStep();
			t.m_position.X += deltaMove.X;
			t.m_position.Y -= deltaMove.Y;
		}
	}
}
