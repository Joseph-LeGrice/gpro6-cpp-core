#pragma once

class Mesh;
class TypedObjectManager;

namespace MeshHelper
{
	Mesh* Quad(TypedObjectManager& resourceManager);
	Mesh* SphereUV(TypedObjectManager& resourceManager);
	Mesh* Cube(TypedObjectManager& resourceManager);
};
