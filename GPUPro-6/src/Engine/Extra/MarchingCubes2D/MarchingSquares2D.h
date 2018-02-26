#pragma once

class Mesh;
class Texture2D;

class MarchingSquares2D
{
public:
	static Mesh* CreateMesh(float gridSize, unsigned int resolution);
    static Texture2D* CreateTexture(unsigned int size);

private:
	static float GetValue(unsigned int x, unsigned int y, unsigned int size);
};