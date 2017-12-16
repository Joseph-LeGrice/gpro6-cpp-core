#include "stdafx.h"
#include "MouseRotateSystem.h"
#include "Core/SystemManagement/SystemManager.h"
#include "Core/Input/InputSystem.h"
#include "Core/Time/Time.h"
#include "Core/SceneGraph/Components/Util/ComponentArray.hpp"
#include "Core/SceneGraph/SceneGraph.h"
#include "Core/DataStructures/Quaternion.h"
#include "Core/SceneGraph/SceneGraph.h"
#include "Core/Graphics/Components/Transform.h"

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
        TransformComponent* const allTransforms = GetSceneGraph().GetComponentArrayPointer<TransformComponent>();
        
        const MouseInput& mi = SystemManager::GetSystem<InputSystem>()->GetMouse();
		const KeyboardInput& ki = SystemManager::GetSystem<InputSystem>()->GetKeyboard();

		if (!m_toggleRotate)
		{
			if (mi.GetMouseButton(0))
			{
                TransformComponent& t = allTransforms[m_index];
				Vector2 deltaMove = mi.GetDeltaMousePosition() * c_speed * Time::DeltaTimeStep();
				t.m_data.m_position.X += deltaMove.X;
				t.m_data.m_position.Y -= deltaMove.Y;
			}
		}
		else
		{
			float angularDelta = c_angularVelocity * Time::DeltaTimeStep();
			TransformComponent& t = allTransforms[m_index];
			t.m_data.m_rotation *= Quaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, angularDelta);
			Quaternion::Normalize(t.m_data.m_rotation);
		}

		if (ki.GetKeyDownThisFrame(kInputKey_C))
		{
			m_toggleRotate = !m_toggleRotate;
		}
	}
}
