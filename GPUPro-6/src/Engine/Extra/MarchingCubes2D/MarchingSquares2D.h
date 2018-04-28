#pragma once

class Mesh;
class Texture2D;
class TypedObjectManager;

class MarchingSquares2D
{
public:
	static Mesh* CreateMesh(TypedObjectManager& resourceManager, float gridSize, unsigned int resolution);
    static Texture2D* CreateTexture(TypedObjectManager& resourceManager, unsigned int size);

private:
	static float GetValue(unsigned int x, unsigned int y, unsigned int size);
};