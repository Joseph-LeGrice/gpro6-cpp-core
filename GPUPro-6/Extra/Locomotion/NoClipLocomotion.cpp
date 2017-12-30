#include "stdafx.h"
#include "NoClipLocomotion.h"

#include "Core/SceneGraph/Components/Entity.h"
#include "Core/SceneGraph/Components/Util/EntityUtil.hpp"
#include "Core/Graphics/Components/Transform.h"
#include "Core/SceneGraph/SceneGraph.h"
#include "Core/SystemManagement/SystemManager.h"
#include "Core/Input/InputSystem.h"
#include "Core/Time/Time.h"
#include "Core/Utilities/MathHelper.h"

NoClipLocomotion::NoClipLocomotion()
{
}


NoClipLocomotion::~NoClipLocomotion()
{
}

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

    EntityComponent* player = GetSceneGraph().GetComponent<EntityComponent>(m_playerEntityId);
    if (player == nullptr)
    {
        return;
    }

    TransformComponent* playerTransform = EntityUtil::GetComponent<TransformComponent>(*player);
    if (playerTransform == nullptr)
    {
        return;
    }
    
    InputSystem* inputSys = GetSystemManager().GetSystem<InputSystem>();
    const MouseInput& mouseInput = inputSys->GetMouse();
    if (mouseInput.GetMouseButton(0))
    {
        Vector3 eulerAngle = Quaternion::ToEuler(playerTransform->m_data.m_rotation);
        Vector2 mouseDelta = mouseInput.GetDeltaMousePosition();
        eulerAngle.X += m_sensitivity * mouseDelta.Y * Time::DeltaTimeStep();
        eulerAngle.Y += m_sensitivity * mouseDelta.X * Time::DeltaTimeStep();
        eulerAngle.Z = 0;
        
        playerTransform->m_data.m_rotation = Quaternion::FromEuler(eulerAngle);
    }
    const KeyboardInput& keyboardInput = inputSys->GetKeyboard();
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

    if (keyboardInput.GetKey(kInputKey_R)) //kInputKey_Space))
    {
        moveDelta.Y = 1.0f;
    }
    else if (keyboardInput.GetKey(kInputKey_F)) //kInputKey_LeftCtrl))
    {
        moveDelta.Y = -1.0f;
    }

    Vector3::Normalize(moveDelta);

    if (keyboardInput.GetKey(kInputKey_X)) //kInputKey_LeftShift))
    {
        moveDelta *= m_moveBoostSpeed;
    }
    else
    {
        moveDelta *= m_moveSpeed;
    }

    if (keyboardInput.GetKey(kInputKey_Q)) //kInputKey_LeftShift))
    {
        playerTransform->m_data.m_position = { 0,0,0 };
    }

    moveDelta *= Time::DeltaTimeStep();
    moveDelta *= playerTransform->m_data.m_rotation;
    
    playerTransform->m_data.m_position += moveDelta;
}
