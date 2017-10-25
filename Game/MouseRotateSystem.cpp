#include "stdafx.h"
#include "MouseRotateSystem.h"
#include "SystemManagement/SystemManagement.h"
#include "DataStructures/Quaternion.h"
#include "DataStructures/ComponentArray.h"
#include "DataStructures/SceneGraph.h"
#include "Components/Transform.h"

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
		ComponentArray<Transform>& tca = SystemManagement::GetGraphicsSystem()->GetSceneGraph().m_transforms;
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
			t.m_rotation *= QuaternionFromAxisAngle({ 0.0f, 1.0f, 0.0f }, angularDelta);
			QuaternionNormalize(t.m_rotation);
		}

		if (ki.GetKeyDownThisFrame(kInputKey_C))
		{
			m_toggleRotate = !m_toggleRotate;
		}
	}
}
