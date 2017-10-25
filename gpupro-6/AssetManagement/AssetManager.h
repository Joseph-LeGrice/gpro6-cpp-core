#pragma once

#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/ResourceTypes/ShaderResource.h"
#include "Graphics/TextureSampler.h"
#include "DataStructures/Mesh.h"

#include "SystemManagement/GameSystem.h"


class AssetManager
{
public:
    static void Create()
    {
        s_instance = new AssetManager();
    }

    static AssetManager* Instance()
    {
        return s_instance;
    }

    static void Destroy()
    {
        SAFE_DELETE(s_instance);
    }

private:
    static AssetManager* s_instance;

    AssetManager(const AssetManager&) = delete;
    AssetManager();
    ~AssetManager();

public:
	const std::vector<Material*>* GetAllMaterials();
	const int RegisterInstancedMaterial(Material& m);
	Material* GetMaterial(int index);

	const int RegisterShaderResource(ShaderResource& sr);
	ShaderResource* GetShaderResource(int index);

	const int RegisterTextureSampler(TextureSampler& ts);
	TextureSampler* GetTextureSampler(int index);

	const std::vector<Mesh*>* GetAllMeshes();
	const int RegisterMesh(Mesh& m);
	Mesh* GetMesh(int meshIndex);

    void RegisterShader(Shader* s);

private:
	std::vector<Material*> m_instancedMaterials;
	std::vector<ShaderResource*> m_shaderResources;
	std::vector<TextureSampler*> m_textureSamplers;
	std::vector<Mesh*> m_meshes;
    std::vector<Shader*> m_shaders;
};

