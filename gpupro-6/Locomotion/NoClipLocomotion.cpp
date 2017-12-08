#include "stdafx.h"
#include "NoClipLocomotion.h"

#include "Components/Entity.h"
#include "Components/Util/EntityUtil.hpp"
#include "Components/Transform.h"
#include "DataStructures/SceneGraph.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include "Utilities/MathHelper.h"

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
    
    TimeSystem* time = SystemManager::GetSystem<TimeSystem>();
    float deltaTime = time->DeltaTimeStep();

    InputSystem* inputSys = SystemManager::GetSystem<InputSystem>();
    const MouseInput& mouseInput = inputSys->GetMouse();
    if (mouseInput.GetMouseButton(0))
    {
        Vector2 mouseDelta = mouseInput.GetDeltaMousePosition();
        Quaternion rotationDelta = Quaternion::Identity();
        rotationDelta *= Quaternion::FromAxisAngle({ 1, 0, 0 }, m_sensitivity * mouseDelta.Y * deltaTime);
        rotationDelta *= Quaternion::FromAxisAngle({ 0, 1, 0 }, m_sensitivity * mouseDelta.X * deltaTime);
        rotationDelta *= Quaternion::FromAxisAngle({ 0, 0, 1 }, 0.0f);
        playerTransform->m_data.m_rotation *= rotationDelta;
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

    moveDelta *= deltaTime;
    moveDelta *= playerTransform->m_data.m_rotation;
    
    playerTransform->m_data.m_position += moveDelta;
}
