#pragma once

#include "D3D11.h"
#include "D3DX11.h"
#include "D3DX10.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <vector>
#include "SystemManagement/ISystem.h"

class Material;
class VertexBuffer;
class IndexBuffer;
class ConstantBufferInterface;
struct Camera;

struct MeshRenderHook
{
	int m_transformIndex;
	int m_meshIndex;
	int m_materialIndex;
};

class GraphicsSystem : public ISystem
{
public:
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();
    ConstantBufferInterface& GetConstantBufferInterface();

    GraphicsSystem();
    GraphicsSystem(const GraphicsSystem&) = delete;
    virtual ~GraphicsSystem();

    virtual bool Initialize() override;
    virtual void VariableTick() override;

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
    ConstantBufferInterface* m_constantBuffers;
    std::vector<MeshRenderHook> m_renderMap;

	float m_viewportWidth, m_viewportHeight;
	
	void UpdateIfDirty();
};
