#include "stdafx.h"
#include "ShaderResource.h"
#include "Systems/GraphicsSystem.h"

ShaderResource::ShaderResource()
{
}


ShaderResource::~ShaderResource()
{
}

void ShaderResource::BindResource(UINT resourceIndex)
{
	ID3D11ShaderResourceView* resource = GetResourceView();
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->VSSetShaderResources(resourceIndex, 1, &resource);
	deviceContext->HSSetShaderResources(resourceIndex, 1, &resource);
	deviceContext->DSSetShaderResources(resourceIndex, 1, &resource);
	deviceContext->GSSetShaderResources(resourceIndex, 1, &resource);
	deviceContext->PSSetShaderResources(resourceIndex, 1, &resource);

}
