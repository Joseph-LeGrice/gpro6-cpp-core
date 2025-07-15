#include "stdafx.h"

#include "Engine/Core/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"


void StructuredBuffer::Finalize()
{
    m_buffer.ReleasePointer();
}
