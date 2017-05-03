#include "stdafx.h"
#include "ResourceViews.h"


ResourceViews::ResourceViews()
{
}


ResourceViews::~ResourceViews()
{
}

std::vector<ID3D11ShaderResourceView*>* ResourceViews::GetVSResources() { return nullptr; }
std::vector<ID3D11ShaderResourceView*>* ResourceViews::GetHSResources() { return nullptr; }
std::vector<ID3D11ShaderResourceView*>* ResourceViews::GetDSResources() { return nullptr; }
std::vector<ID3D11ShaderResourceView*>* ResourceViews::GetGSResources() { return nullptr; }
std::vector<ID3D11ShaderResourceView*>* ResourceViews::GetPSResources() { return nullptr; }
