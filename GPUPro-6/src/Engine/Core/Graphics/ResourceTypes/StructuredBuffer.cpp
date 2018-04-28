#include "stdafx.h"

#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"

void StructuredBuffer::Finalize()
{
    m_buffer.ReleasePointer();
}
