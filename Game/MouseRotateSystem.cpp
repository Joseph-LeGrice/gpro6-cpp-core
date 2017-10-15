#include "stdafx.h"
#include "MouseRotateSystem.h"
#include "Systems\InputSystem.h"
#include "Systems\TimeSystem.h"
#include "Systems\SceneManagementSystem.h"
#include "DataStructures\Quaternion.h"

MouseRotateSystem::MouseRotateSystem() : m_velocity(0.0f),
	m_index(-1), m_hasIndex(false), m_toggleRotate(false)
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
		const KeyboardInput& ki = InputSystem::Instance()->GetKeyboard();

		if (!m_toggleRotate)
		{
			if (mi.GetMouseButton(0))
			{
				Transform& t = allTransforms[m_index];
				Vector2 deltaMove = mi.GetDeltaMousePosition() * c_speed * TimeSystem::Instance()->DeltaTimeStep();
				t.m_position.X += deltaMove.X;
				t.m_position.Y -= deltaMove.Y;
			}
		}
		else
		{
			float angularDelta = c_angularVelocity * TimeSystem::Instance()->DeltaTimeStep();
			Transform& t = allTransforms[m_index];
			t.m_rotation *= QuaternionFromAxisAngle(VectorUp(), angularDelta);
			QuaternionNormalize(t.m_rotation);
		}

		if (ki.GetKeyDownThisFrame(kInputKey_C))
		{
			m_toggleRotate = !m_toggleRotate;
		}
	}
}
