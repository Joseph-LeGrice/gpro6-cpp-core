#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#include <vector>
#include "Systems\GameSystem.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class Material;
class VertexBuffer;
class IndexBuffer;
struct Camera;
struct SceneGraph;

struct MeshRenderHook
{
	int m_transformIndex;
	int m_meshIndex;
	int m_materialIndex;
};

class GraphicsSystem : public ISystem
{
	REGISTER_SUBSYSTEM(GraphicsSystem)

public:
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();

	virtual void VariableTick() override;

	bool InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight);
	float GetViewportWidth();
	float GetViewportHeight();

	void RegisterMeshRenderHook(MeshRenderHook& mrh);

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView * m_rtBackBuffer;

	bool m_isDirty;
	VertexBuffer* m_myVertexBuffer;
	IndexBuffer* m_myIndexBuffer;
	std::vector<MeshRenderHook> m_renderMap;

	float m_viewportWidth, m_viewportHeight;
	
	void UpdateIfDirty();
};
