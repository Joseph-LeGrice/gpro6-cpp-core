#pragma once

class Mesh;
class ResourceManager;

namespace MeshHelper
{
	Mesh* Quad(ResourceManager& resourceManager);
	Mesh* SphereUV(ResourceManager& resourceManager);
	Mesh* Cube(ResourceManager& resourceManager);
};
