using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;

class Program
{
   static int Main(string[] args)
    {
        TestSystem test = new TestSystem();

        //------------------------------------------------------------------------------------
        Texture2D testImageTexture = TypedObjectManager.Create<Texture2D>();
        string testImagePath = Path.Combine(Application.ResourcePath, "GameResources\\GPro_Test\\TestImage.png");
        testImageTexture.InitializeWithBitmap(testImagePath);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // int lightBufferIndex = GetSystemManager().GetSystem<LightingSystem>().GetBufferResourceIndex();
        // StructuredBuffer lightBuffer = TypedObjectManager.GetInstance<StructuredBuffer>(lightBufferIndex);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        TextureSampler textureSampler = TypedObjectManager.Create<TextureSampler>();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Shader materialShader = TypedObjectManager.Create<Shader>();
        string forwardRenderShaderPath = Path.Combine(Application.ResourcePath, "Shaders/ForwardRendering.hlsl");
        materialShader.InitVertexShader(forwardRenderShaderPath, "VShader");
        materialShader.InitPixelShader(forwardRenderShaderPath, "PShader");
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Material simpleTestMaterial = TypedObjectManager.Create<Material>();
        int simpleTestMaterialID = simpleTestMaterial.InstanceID;
        simpleTestMaterial.SetShaderIndex(materialShader.InstanceID);
        simpleTestMaterial.RegisterShaderResource(testImageTexture.GetResourceViewID(), 1 );
        // simpleTestMaterial.RegisterShaderResource(lightBuffer.GetMyResourceViewID(), 0);
        simpleTestMaterial.AddTextureSampler(textureSampler.InstanceID, 0);

        MATERIAL_BUFFER mat;
        ZeroMemory(mat, sizeof(MATERIAL_BUFFER));
        mat.DiffuseColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        mat.SpecularColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        mat.SpecularPower = 10.0f;
        mat.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER buf = new MATERIAL_BUFFER(mat);
        simpleTestMaterial.SetData(buf);
        //------------------------------------------------------------------------------------
		
        //------------------------------------------------------------------------------------
        // Ball Object
        Mesh sphereMesh = MeshHelper::CreateSphereUV();
        int sphereMeshID = sphereMesh.InstanceID;

		Entity sphereEntity = TypedObjectManager.Create<Entity>();
        Transform sphereTransform = Entity::AddComponent<Transform>(sphereEntity);
        // int sphereTransformIndex = sphereTransform.m_componentIndex;
        //sphereTransform.rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
        sphereTransform.position = new Vector3(50.0f, 1.0f, 1.0f);
        sphereTransform.scale = new Vector3(1.0f, 1.0f, 1.0f);
        sphereTransform.scale *= 10.0f;
        MeshRenderer sphereRenderer = Entity::AddComponent<MeshRenderer>(sphereEntity);
        sphereRenderer.MeshIndex = sphereMeshID;
        sphereRenderer.DrawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>().ID();
        sphereRenderer.MaterialIndex = simpleTestMaterialID;
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        // Light
        Entity lightEntity = TypedObjectManager.Create<Entity>();
        Transform lightTransform = Entity::AddComponent<Transform>(lightEntity);
        lightTransform.position = new Vector3(50.0f, 0.0f, 0.0f);
        Light lightComponent = Entity::AddComponent<LightComponent>(lightEntity);
        lightComponent.Range = 250.0f;
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // MarchingSquares Testing
        Material marchingSquaresMaterial = TypedObjectManager.Create<Material>();
        marchingSquaresMaterial.SetShaderIndex(materialShader.InstanceID);
        marchingSquaresMaterial.RegisterShaderResource(testImageTexture.GetResourceViewID(), 1);
        // marchingSquaresMaterial.RegisterShaderResource(lightBuffer.GetMyResourceViewID(), 0);
        marchingSquaresMaterial.AddTextureSampler(textureSampler.InstanceID, 0);

        MATERIAL_BUFFER marchinSquaresMatBuf;
        ZeroMemory(marchinSquaresMatBuf, sizeof(MATERIAL_BUFFER));
        marchinSquaresMatBuf.DiffuseColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        marchinSquaresMatBuf.SpecularColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        marchinSquaresMatBuf.SpecularPower = 10.0f;
        marchinSquaresMatBuf.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER marchinSquaresMatBufBuf = { marchinSquaresMatBuf };
        marchingSquaresMaterial.SetData(marchinSquaresMatBufBuf);

		VoxelTerrain vt = new VoxelTerrain();
		
        Mesh marching_mesh = MarchingSquares2D::CreateMesh(2.5f, 64);

        Entity quadEntity = TypedObjectManager.Create<Entity>();
        Transform quadTransform = Entity::AddComponent<Transform>(quadEntity);
        quadTransform.scale = 5 * Vector3::One();
        MeshRenderer quadRenderer = Entity::AddComponent<MeshRenderer>(quadEntity);
        quadRenderer.MeshIndex = vt.GetMeshID(); //marching_mesh.InstanceID;
        quadRenderer.MaterialIndex = marchingSquaresMaterial.InstanceID;
        quadRenderer.DrawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>().ID();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // Camera
        Entity cameraEntity = TypedObjectManager.Create<Entity>();
        // int cameraEntityId = cameraEntity.m_componentIndex;
        Transform cameraTransform = Entity::AddComponent<Transform>(cameraEntity);
        // int cameraTransformId = cameraTransform.m_componentIndex;
        cameraTransform.position = new Vector3(0.0f, 0.0f, -15.0f);
        Camera cameraComponent = Entity::AddComponent<CameraComponent>(cameraEntity);
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        //Skybox
        Shader skyboxShader = TypedObjectManager.Create<Shader>();
        string envMapShaderPath = Path.Combine(Application.ResourcePath, "Shaders/EnvironmentMap.hlsl");
        skyboxShader.InitVertexShader(envMapShaderPath, "VShader");
        skyboxShader.InitPixelShader(envMapShaderPath, "PShader");

        Texture2DArray testCubemap = TypedObjectManager.Create<Texture2DArray>();
        List<string> bitmapPaths = new List<string>() {
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Right.bmp"),
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Left.bmp"),
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Bottom.bmp"),
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Top.bmp"),
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Front.bmp"),
            Path.Combine(Application.ResourcePath, "GameResources/GPro_Test/TheSaMonstaSkyBox1_Back.bmp")
        };
        testCubemap.InitializeWithBitmaps(bitmapPaths);
        
        Material skyboxMat = TypedObjectManager.Create<Material>();
        skyboxMat.SetShaderIndex(skyboxShader.InstanceID);
        skyboxMat.RegisterShaderResource(testCubemap.GetMyResourceViewID(), 0);

        Entity skyboxEntity = TypedObjectManager.Create<Entity>();
        MeshRenderer skyboxRenderer = Entity::AddComponent<MeshRenderer>(skyboxEntity);
        // skyboxRenderer.m_enabled = true;
        skyboxRenderer.MeshIndex = sphereMeshID;
        skyboxRenderer.DrawCommandIndex = GetCommandList().GetCommand<SkyboxDrawCommand>().ID();
        skyboxRenderer.MaterialIndex = skyboxMat.InstanceID;
        //------------------------------------------------------------------------------------
        
        return 0;
    }
}