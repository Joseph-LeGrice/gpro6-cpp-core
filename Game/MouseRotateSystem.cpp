#include "stdafx.h"
#include "MouseRotateSystem.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include "DataStructures/ComponentArray.hpp"
#include "DataStructures/SceneGraph.h"
#include "DataStructures/Quaternion.h"
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
		ComponentArray<TransformComponent>& tca = GetSceneGraph().GetComponentArray<TransformComponent>();
        TransformComponent* const allTransforms = tca.GetArrayPointer();
		const MouseInput& mi = SystemManager::GetSystem<InputSystem>()->GetMouse();
		const KeyboardInput& ki = SystemManager::GetSystem<InputSystem>()->GetKeyboard();

		if (!m_toggleRotate)
		{
			if (mi.GetMouseButton(0))
			{
                TransformComponent& t = allTransforms[m_index];
				Vector2 deltaMove = mi.GetDeltaMousePosition() * c_speed * SystemManager::GetSystem<TimeSystem>()->DeltaTimeStep();
				t.m_data.m_position.X += deltaMove.X;
				t.m_data.m_position.Y -= deltaMove.Y;
			}
		}
		else
		{
			float angularDelta = c_angularVelocity * SystemManager::GetSystem<TimeSystem>()->DeltaTimeStep();
			TransformComponent& t = allTransforms[m_index];
			t.m_data.m_rotation *= QuaternionFromAxisAngle({ 0.0f, 1.0f, 0.0f }, angularDelta);
			QuaternionNormalize(t.m_data.m_rotation);
		}

		if (ki.GetKeyDownThisFrame(kInputKey_C))
		{
			m_toggleRotate = !m_toggleRotate;
		}
	}
}
