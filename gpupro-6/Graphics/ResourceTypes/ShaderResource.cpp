#include "stdafx.h"
#include "ShaderResource.h"
#include "Systems/GraphicsSystem.h"

ShaderResource::ShaderResource()
{
}


ShaderResource::~ShaderResource()
{
}

void ShaderResource::BindResource(UINT resourceIndex, UINT numberOfResources)
{
	ID3D11ShaderResourceView* resource = GetResourceView();
	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	deviceContext->VSSetShaderResources(resourceIndex, numberOfResources, &resource);
	deviceContext->HSSetShaderResources(resourceIndex, numberOfResources, &resource);
	deviceContext->DSSetShaderResources(resourceIndex, numberOfResources, &resource);
	deviceContext->GSSetShaderResources(resourceIndex, numberOfResources, &resource);
	deviceContext->PSSetShaderResources(resourceIndex, numberOfResources, &resource);

}
