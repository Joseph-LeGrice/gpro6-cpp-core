#pragma once

#include "Material.hpp"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/StandardMaterialBuffer.h"


class StandardMaterial : public Material<MATERIAL_BUFFER_CONTAINER>
{
REGISTER_TYPE(StandardMaterial);
};
