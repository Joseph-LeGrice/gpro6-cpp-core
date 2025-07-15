#pragma once

class WindowManager;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Debug;

class GraphicsDevice
{
public:
	GraphicsDevice(WindowManager& windowManager);
	~GraphicsDevice();

	IDXGISwapChain* GetSwapChain();
	ID3D11Device* GetGraphicsDevice();
	ID3D11DeviceContext* GetGraphicsDeviceContext();
	float GetViewportWidth();
	float GetViewportHeight();
	void Present();

private:
	WindowManager& m_windowManager;
	ManualRelease<ID3D11Device> m_device;
	ManualRelease<ID3D11DeviceContext> m_deviceContext;
	ManualRelease<IDXGISwapChain> m_swapchain;

#if defined(_DEBUG)
	ManualRelease<ID3D11Debug> m_debugInterface;
#endif

	float m_viewportWidth, m_viewportHeight;
};
