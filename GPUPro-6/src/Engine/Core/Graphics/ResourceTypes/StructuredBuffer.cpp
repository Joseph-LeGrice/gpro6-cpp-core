#include "stdafx.h"

#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"

void StructuredBuffer::Release()
{
    m_buffer.ReleasePointer();
}
