#pragma once

class GraphicsSystem;
class MaterialManagementSystem;

class GameSystem
{
public:
	static GraphicsSystem* Graphics();
	static MaterialManagementSystem* Materials();

private:
	static GameSystem* s_instance;
	static GameSystem Instance();

	GameSystem();
	~GameSystem();
	void Initialize(HWND g_hwnd, int screenWidth, int screenHeight);
	GraphicsSystem* m_graphicsSystem;
	MaterialManagementSystem* m_materialManagementSystem;
};

