#pragma once

class Mesh;
class Texture2D;
class ResourceManager;

class MarchingSquares2D
{
public:
	static Mesh* CreateMesh(ResourceManager& resourceManager, float gridSize, unsigned int resolution);
    static Texture2D* CreateTexture(ResourceManager& resourceManager, unsigned int size);

private:
	static float GetValue(unsigned int x, unsigned int y, unsigned int size);
};