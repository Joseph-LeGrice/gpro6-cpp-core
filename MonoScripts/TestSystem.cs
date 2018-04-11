using System;

class TestSystem : ISystem
{
    public override void Initialize()
    {
        Console.WriteLine("Initialize");

        /*
        //------------------------------------------------------------------------------------
        Texture2D* testImageTexture = m_resourceManager.Instantiate<Texture2D>();
        std::wstring testImagePath = Application::GetResourcePath(L"GameResources/GPro_Test/TestImage.png");
        testImageTexture->InitializeWithBitmap(testImagePath.c_str());
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        int lightBufferIndex = GetSystemManager().GetSystem<LightingSystem>()->GetBufferResourceIndex();
        StructuredBuffer* lightBuffer = m_resourceManager.GetAsset<StructuredBuffer>(lightBufferIndex);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        TextureSampler* textureSampler = m_resourceManager.Instantiate<TextureSampler>();
        textureSampler->Initialize();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Shader* materialShader = m_resourceManager.Instantiate<Shader>();
        std::wstring forwardRenderShaderPath = Application::GetResourcePath(L"Shaders/ForwardRendering.hlsl");
        materialShader->InitVertexShader(forwardRenderShaderPath, "VShader");
        materialShader->InitPixelShader(forwardRenderShaderPath, "PShader");
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        StandardMaterial* simpleTestMaterial = m_resourceManager.Instantiate<StandardMaterial>();
        UINT simpleTestMaterialID = simpleTestMaterial->GetResourceID();
        simpleTestMaterial->SetShaderIndex(materialShader->GetResourceID());
        simpleTestMaterial->RegisterShaderResource({ testImageTexture->GetResourceViewID(), 1 });
        simpleTestMaterial->RegisterShaderResource({ lightBuffer->GetMyResourceViewID(), 0});
        simpleTestMaterial->AddTextureSampler({ textureSampler->GetResourceID(), 0 });

        MATERIAL_BUFFER mat;
        ZeroMemory(&mat, sizeof(MATERIAL_BUFFER));
        mat.DiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        mat.SpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        mat.SpecularPower = 10.0f;
        mat.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER buf = { mat };
        simpleTestMaterial->SetData(buf);
        //------------------------------------------------------------------------------------
		
        //------------------------------------------------------------------------------------
        // Ball Object
        Mesh* sphereMesh = MeshHelper::CreateSphereUV();
        UINT sphereMeshID = sphereMesh->GetResourceID();

		Entity& sphereEntity = GetSceneGraph().CreateComponent<Entity>();
        Transform& sphereTransform = Entity::AddComponent<Transform>(sphereEntity);
        int sphereTransformIndex = sphereTransform.m_componentIndex;
        //sphereTransform.m_data.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
        sphereTransform.m_data.m_position = { 50.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale *= 10.0f;
        MeshRenderer& sphereRenderer = Entity::AddComponent<MeshRenderer>(sphereEntity);
        sphereRenderer.m_data.m_meshIndex = sphereMeshID;
        sphereRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>()->ID();
        sphereRenderer.m_data.m_materialIndex = simpleTestMaterialID;
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        // Light
        Entity& lightEntity = GetSceneGraph().CreateComponent<Entity>();
        Transform& lightTransform = Entity::AddComponent<Transform>(lightEntity);
        lightTransform.m_data.m_position = { 50.0f, 0.0f, 0.0f };
        LightComponent& lightComponent = Entity::AddComponent<LightComponent>(lightEntity);
        lightComponent.m_data.m_range = 250.0f;
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // MarchingSquares Testing
        StandardMaterial* marchingSquaresMaterial = m_resourceManager.Instantiate<StandardMaterial>();
        marchingSquaresMaterial->SetShaderIndex(materialShader->GetResourceID());
        marchingSquaresMaterial->RegisterShaderResource({ testImageTexture->GetResourceViewID(), 1 });
        marchingSquaresMaterial->RegisterShaderResource({ lightBuffer->GetMyResourceViewID(), 0 });
        marchingSquaresMaterial->AddTextureSampler({ textureSampler->GetResourceID(), 0 });

        MATERIAL_BUFFER marchinSquaresMatBuf;
        ZeroMemory(&marchinSquaresMatBuf, sizeof(MATERIAL_BUFFER));
        marchinSquaresMatBuf.DiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        marchinSquaresMatBuf.SpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        marchinSquaresMatBuf.SpecularPower = 10.0f;
        marchinSquaresMatBuf.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER marchinSquaresMatBufBuf = { marchinSquaresMatBuf };
        marchingSquaresMaterial->SetData(marchinSquaresMatBufBuf);

		VoxelTerrain* vt = new VoxelTerrain();
		
        Mesh* marching_mesh = MarchingSquares2D::CreateMesh(2.5f, 64);

        Entity& quadEntity = GetSceneGraph().CreateComponent<Entity>();
        Transform& quadTransform = Entity::AddComponent<Transform>(quadEntity);
        quadTransform.m_data.m_scale = 5 * Vector3::One();
        MeshRenderer& quadRenderer = Entity::AddComponent<MeshRenderer>(quadEntity);
        quadRenderer.m_data.m_meshIndex = vt->GetMeshID(); //marching_mesh->GetResourceID();
        quadRenderer.m_data.m_materialIndex = marchingSquaresMaterial->GetResourceID();
        quadRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>()->ID();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // Camera
        Entity& cameraEntity = GetSceneGraph().CreateComponent<Entity>();
        int cameraEntityId = cameraEntity.m_componentIndex;
        Transform& cameraTransform = Entity::AddComponent<Transform>(cameraEntity);
        UINT cameraTransformId = cameraTransform.m_componentIndex;
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -15.0f };
        CameraComponent& cameraComponent = Entity::AddComponent<CameraComponent>(cameraEntity);
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        //Skybox
        Shader* skyboxShader = m_resourceManager.Instantiate<Shader>();
        std::wstring envMapShaderPath = Application::GetResourcePath(L"Shaders/EnvironmentMap.hlsl");
        skyboxShader->InitVertexShader(envMapShaderPath, "VShader");
        skyboxShader->InitPixelShader(envMapShaderPath, "PShader");

        Texture2DArray* testCubemap = m_resourceManager.Instantiate<Texture2DArray>();
        testCubemap->InitializeWithBitmaps({
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Right.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Left.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Bottom.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Top.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Front.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Back.bmp")
        });
        
        SimpleMaterial* skyboxMat = m_resourceManager.Instantiate<SimpleMaterial>();
        UINT skyboxMatID = skyboxMat->GetResourceID();
        skyboxMat->SetShaderIndex(skyboxShader->GetResourceID());
        skyboxMat->RegisterShaderResource({ testCubemap->GetMyResourceViewID(), 0 });

        Entity& skyboxEntity = GetSceneGraph().CreateComponent<Entity>();
        MeshRenderer& skyboxRenderer = Entity::AddComponent<MeshRenderer>(skyboxEntity);
        skyboxRenderer.m_enabled = true;
        skyboxRenderer.m_data.m_meshIndex = sphereMeshID;
        skyboxRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<SkyboxDrawCommand>()->ID();
        skyboxRenderer.m_data.m_materialIndex = skyboxMatID;
        //------------------------------------------------------------------------------------
        */
    }

    public override void EarlyTick()
    {
        Console.WriteLine("EarlyTick");
    }

    public override void Tick()
    {
        Console.WriteLine("Tick");
    }

    public override void LateTick()
    {
        Console.WriteLine("LateTick");
    }

    public override void Deinitialize()
    {
        Console.WriteLine("Deinitialize");
    }
}