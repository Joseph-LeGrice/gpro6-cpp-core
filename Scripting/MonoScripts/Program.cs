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
        simpleTestMaterial.SetShaderIndex(materialShader.InstanceID);
        simpleTestMaterial.RegisterShaderResource(testImageTexture.GetResourceViewID(), 1 );
        // simpleTestMaterial.RegisterShaderResource(lightBuffer.GetMyResourceViewID(), 0);
        simpleTestMaterial.AddTextureSampler(textureSampler.InstanceID, 0);

        simpleTestMaterial.SetFloat4("DiffuseColor", new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        simpleTestMaterial.SetFloat4("SpecularColor", new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        simpleTestMaterial.SetFloat("SpecularPower", 10.0f);
        simpleTestMaterial.SetBoolean("HasDiffuseTexture", true);
        //------------------------------------------------------------------------------------
		
        //------------------------------------------------------------------------------------
        // Ball Object
        Mesh sphereMesh = MeshHelper.CreateSphereUV();
        int sphereMeshID = sphereMesh.InstanceID;

		Entity sphereEntity = TypedObjectManager.Create<Entity>();
        Transform sphereTransform = sphereEntity.AddComponent<Transform>();
        //sphereTransform.rotation = Quaternion.FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
        sphereTransform.position = new Vector3(50.0f, 1.0f, 1.0f);
        sphereTransform.scale = new Vector3(1.0f, 1.0f, 1.0f);
        sphereTransform.scale *= 10.0f;
        MeshRenderer sphereRenderer = sphereEntity.AddComponent<MeshRenderer>();
        sphereRenderer.MeshIndex = sphereMeshID;
        sphereRenderer.DrawCommandIndex = 1;
        sphereRenderer.MaterialIndex = simpleTestMaterial.InstanceID;
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        // Light
        Entity lightEntity = TypedObjectManager.Create<Entity>();
        Transform lightTransform = lightEntity.AddComponent<Transform>();
        lightTransform.position = new Vector3(50.0f, 0.0f, 0.0f);
        Light lightComponent = lightEntity.AddComponent<Light>();
        lightComponent.Range = 250.0f;
        //------------------------------------------------------------------------------------
/*
        //------------------------------------------------------------------------------------
        // MarchingSquares Testing
        Material marchingSquaresMaterial = TypedObjectManager.Create<Material>();
        marchingSquaresMaterial.SetShaderIndex(materialShader.InstanceID);
        marchingSquaresMaterial.RegisterShaderResource(testImageTexture.GetResourceViewID(), 1);
        // marchingSquaresMaterial.RegisterShaderResource(lightBuffer.GetMyResourceViewID(), 0);
        marchingSquaresMaterial.AddTextureSampler(textureSampler.InstanceID, 0);

        MATERIAL_BUFFER marchinSquaresMatBuf;
        marchinSquaresMatBuf.DiffuseColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        marchinSquaresMatBuf.SpecularColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        marchinSquaresMatBuf.SpecularPower = 10.0f;
        marchinSquaresMatBuf.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER marchinSquaresMatBufBuf = { marchinSquaresMatBuf };
        marchingSquaresMaterial.SetData(marchinSquaresMatBufBuf);

		VoxelTerrain vt = new VoxelTerrain();
		
        Mesh marching_mesh = MarchingSquares2D.CreateMesh(2.5f, 64);

        Entity quadEntity = TypedObjectManager.Create<Entity>();
        Transform quadTransform = Entity.AddComponent<Transform>(quadEntity);
        quadTransform.scale = 5 * Vector3.One();
        MeshRenderer quadRenderer = Entity.AddComponent<MeshRenderer>(quadEntity);
        quadRenderer.MeshIndex = vt.GetMeshID(); //marching_mesh.InstanceID;
        quadRenderer.MaterialIndex = marchingSquaresMaterial.InstanceID;
        quadRenderer.DrawCommandIndex = 1;
        //------------------------------------------------------------------------------------
*/
        //------------------------------------------------------------------------------------
        // Camera
        Entity cameraEntity = TypedObjectManager.Create<Entity>();
        Transform cameraTransform = cameraEntity.AddComponent<Transform>();
        cameraTransform.position = new Vector3(0.0f, 0.0f, -15.0f);
        Camera cameraComponent = cameraEntity.AddComponent<Camera>();
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
        testCubemap.InitializeWithBitmaps(bitmapPaths.ToArray());
        
        Material skyboxMat = TypedObjectManager.Create<Material>();
        skyboxMat.SetShaderIndex(skyboxShader.InstanceID);
        skyboxMat.RegisterShaderResource(testCubemap.GetResourceViewID(), 0);

        Entity skyboxEntity = TypedObjectManager.Create<Entity>();
        MeshRenderer skyboxRenderer = skyboxEntity.AddComponent<MeshRenderer>();
        // skyboxRenderer.m_enabled = true;
        skyboxRenderer.MeshIndex = sphereMeshID;
        skyboxRenderer.DrawCommandIndex = 0;
        skyboxRenderer.MaterialIndex = skyboxMat.InstanceID;
        //------------------------------------------------------------------------------------
        
        return 0;
    }
}