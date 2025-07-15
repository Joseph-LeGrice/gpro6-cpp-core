#include "stdafx.h"
#include "NoClipLocomotion.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Components/Transform.h"

#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Time/Time.h"

void NoClipLocomotion::SetPlayer(int entityId)
{
    m_playerEntityId = entityId;
}

void NoClipLocomotion::VariableTick()
{
    if (m_playerEntityId < 0)
    {
        return;
    }

    Entity* player = m_typedObjectManager.GetInstance<Entity>(m_playerEntityId);
    if (player == nullptr)
    {
        return;
    }

    Transform* playerTransform = player->GetComponent<Transform>();
    if (playerTransform == nullptr)
    {
        return;
    }
    
    const MouseInput& mouseInput = m_inputSystem.GetMouse();
    if (mouseInput.GetMouseButton(0))
    {
        Vector2 mouseDelta = mouseInput.GetDeltaMousePosition();
#if 1
        Vector3 currentUp = playerTransform->WorldUp();
        Vector3 currentRight = playerTransform->WorldRight();
        Vector3 currentForward = playerTransform->WorldForward();

        Vector3 upComponent = currentUp * m_sensitivity * -mouseDelta.Y * Time::DeltaTimeStep();
        Vector3 rightComponent = currentRight * m_sensitivity * mouseDelta.X * Time::DeltaTimeStep();
        Vector3 newForward = currentForward + upComponent + rightComponent;

        playerTransform->SetRotation(Quaternion::FromLookRotation(newForward));
#else
        Vector3 eulerAngle = Quaternion::ToEuler(playerTransform->m_rotation);
        eulerAngle.X += m_sensitivity * mouseDelta.Y * Time::DeltaTimeStep();
        eulerAngle.Y += m_sensitivity * mouseDelta.X * Time::DeltaTimeStep();
        eulerAngle.Z = 0;
        
        playerTransform->m_rotation = Quaternion::FromEuler(eulerAngle);
#endif
    }

    const KeyboardInput& keyboardInput = m_inputSystem.GetKeyboard();
    Vector3 moveDelta = { 0, 0, 0 };
    if (keyboardInput.GetKey(kInputKey_W))
    {
        moveDelta.Z = 1.0f;
    }
    else if (keyboardInput.GetKey(kInputKey_S))
    {
        moveDelta.Z = -1.0f;
    }

    if (keyboardInput.GetKey(kInputKey_D))
    {
        moveDelta.X = 1.0f;
    }
    else if (keyboardInput.GetKey(kInputKey_A))
    {
        moveDelta.X = -1.0f;
    }

    if (keyboardInput.GetKey(kInputKey_SPACE))
    {
        moveDelta.Y = 1.0f;
    }
    else if (keyboardInput.GetKey(kInputKey_CONTROL))
    {
        moveDelta.Y = -1.0f;
    }

    moveDelta.Normalize();

    if (keyboardInput.GetKey(kInputKey_SHIFT))
    {
        moveDelta *= m_moveBoostSpeed;
    }
    else
    {
        moveDelta *= m_moveSpeed;
    }

    if (keyboardInput.GetKey(kInputKey_R))
    {
        playerTransform->m_position = { 0,0,0 };
    }

    moveDelta *= Time::DeltaTimeStep();
    moveDelta *= playerTransform->m_rotation;
    
    playerTransform->m_position += moveDelta;
}
