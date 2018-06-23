using System;
using System.Collections.Generic;
using System.IO;
// using GPro;
using System.Runtime.CompilerServices;

class Program
{
   static int Main(string[] args)
    {
        //------------------------------------------------------------------------------------
        // Camera
        Entity cameraEntity = TypedObjectManager.Create<Entity>();
        Transform cameraTransform = cameraEntity.AddComponent<Transform>();
        cameraTransform.position = new Vector3(0.0f, 0.0f, -50.0f);
        Camera cameraComponent = cameraEntity.AddComponent<Camera>();
        
        float viewportWidth = 800; //m_gfxDevice.GetViewportWidth();
        float viewportHeight = 600; //m_gfxDevice.GetViewportHeight();
        float aspectRatio = viewportWidth / viewportHeight;

        float screenNear = 0.1f;
        float screenDepth = 100.0f;
        float PI = 3.1415926535897f;
        float fieldOfView = 60.0f * PI / 180.0f;

        cameraComponent.SetPerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
        // cameraComponent.SetOrthographic(2, 100, aspectRatio);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Texture2D testImageTexture = TypedObjectManager.Create<Texture2D>();
        string testImagePath = Path.Combine(Application.ResourcePath, "GameResources\\GPro_Test\\TestImage.png");
        testImageTexture.InitializeWithBitmap(testImagePath);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        TextureSampler textureSampler = TypedObjectManager.Create<TextureSampler>();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Mesh sphereMesh = MeshHelper.CreateSphereUV();
        Mesh quadMesh = MeshHelper.CreateQuad();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // Quad Object
        Shader testQuadShader = TypedObjectManager.Create<Shader>();
        string testMatShaderPath = Path.Combine(Application.ResourcePath, "Shaders/TestShader.hlsl");
        testQuadShader.InitVertexShader(testMatShaderPath, "VShader");
        testQuadShader.InitPixelShader(testMatShaderPath, "PShader");
        
        Material testQuadMat = TypedObjectManager.Create<Material>();
        testQuadMat.SetShader(testQuadShader);
        testQuadMat.SetCullState(CullState.Back);
        
		Entity quadEntity = TypedObjectManager.Create<Entity>();
        Transform quadTransform = quadEntity.AddComponent<Transform>();
        quadTransform.position = new Vector3(-10.0f, 10.0f, 30.0f);
        quadTransform.scale = new Vector3(1.0f, 1.0f, 1.0f);
        quadTransform.scale *= 10.0f;
        MeshRenderer quadRenderer = quadEntity.AddComponent<MeshRenderer>();
        quadRenderer.Mesh = quadMesh;
        quadRenderer.Material = testQuadMat;
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
        skyboxMat.SetCullState(CullState.None);
        skyboxMat.SetShader(skyboxShader);
        skyboxMat.RegisterShaderResource(testCubemap.GetResource(), 0);
        skyboxMat.AddTextureSampler(textureSampler, 0);

        // Entity skyboxEntity = TypedObjectManager.Create<Entity>();
        MeshRenderer skyboxRenderer = cameraEntity.AddComponent<MeshRenderer>();
        // skyboxRenderer.m_enabled = true;
        skyboxRenderer.Mesh = sphereMesh;
        skyboxRenderer.Material = skyboxMat;
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        StructuredBuffer lightBuffer = TypedObjectManager.GetInstance<StructuredBuffer>(0); // FIXME: Cheating here - We should access the Lighting
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        // Light
        Entity lightEntity = TypedObjectManager.Create<Entity>();
        Transform lightTransform = lightEntity.AddComponent<Transform>();
        lightTransform.position = new Vector3(50.0f, 0.0f, 0.0f);
        Light lightComponent = lightEntity.AddComponent<Light>();
        lightComponent.Range = 250.0f;
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Shader forwardRenderShader = TypedObjectManager.Create<Shader>();
        string forwardRenderShaderPath = Path.Combine(Application.ResourcePath, "Shaders/ForwardRendering.hlsl");
        forwardRenderShader.InitVertexShader(forwardRenderShaderPath, "VShader");
        forwardRenderShader.InitPixelShader(forwardRenderShaderPath, "PShader");
        //------------------------------------------------------------------------------------
        
        //------------------------------------------------------------------------------------
        // Sphere Object
        Material sphereMaterial = TypedObjectManager.Create<Material>();
        sphereMaterial.SetShader(forwardRenderShader);
        sphereMaterial.RegisterShaderResource(testImageTexture.GetResource(), 1 );
        sphereMaterial.RegisterShaderResource(lightBuffer.GetResourceView(), 0);
        sphereMaterial.AddTextureSampler(textureSampler, 0);

        List<PropertyInitializer> props = new List<PropertyInitializer>() {
            new PropertyInitializer("GlobalAmbient", PropertyValueType.Float4),
            new PropertyInitializer("AmbientColor", PropertyValueType.Float4),
            new PropertyInitializer("EmissiveColor", PropertyValueType.Float4),
            new PropertyInitializer("DiffuseColor", PropertyValueType.Float4),
            new PropertyInitializer("SpecularColor", PropertyValueType.Float4),
            new PropertyInitializer("Reflectance", PropertyValueType.Float4),

            new PropertyInitializer("Opacity", PropertyValueType.Float),
            new PropertyInitializer("SpecularPower", PropertyValueType.Float),
            new PropertyInitializer("IndexOfRefraction", PropertyValueType.Float),
            new PropertyInitializer("HasAmbientTexture", PropertyValueType.Boolean),

            new PropertyInitializer("HasEmissiveTexture", PropertyValueType.Boolean),
            new PropertyInitializer("HasDiffuseTexture", PropertyValueType.Boolean),
            new PropertyInitializer("HasSpecularTexture", PropertyValueType.Boolean),
            new PropertyInitializer("HasSpecularPowerTexture", PropertyValueType.Boolean),

            new PropertyInitializer("HasNormalTexture", PropertyValueType.Boolean),
            new PropertyInitializer("HasBumpTexture", PropertyValueType.Boolean),
            new PropertyInitializer("HasOpacityTexture", PropertyValueType.Boolean),
            new PropertyInitializer("BumpIntensity", PropertyValueType.Float),
            new PropertyInitializer("SpecularScale", PropertyValueType.Float),
            new PropertyInitializer("AlphaThreshold", PropertyValueType.Float),
            new PropertyInitializer("Padding", PropertyValueType.Float2)
        };
        sphereMaterial.InitProperties(props.ToArray());

        sphereMaterial.SetFloat4("DiffuseColor", new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        sphereMaterial.SetFloat4("SpecularColor", new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        sphereMaterial.SetFloat("SpecularPower", 10.0f);
        sphereMaterial.SetBoolean("HasDiffuseTexture", true);
        
        Entity sphereEntity = TypedObjectManager.Create<Entity>();
        Transform sphereTransform = sphereEntity.AddComponent<Transform>();
        //sphereTransform.rotation = Quaternion.FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
        sphereTransform.position = new Vector3(0.0f, 0.0f, 5.0f);
        sphereTransform.scale = new Vector3(1.0f, 1.0f, 1.0f);
        sphereTransform.scale *= 10.0f;
        MeshRenderer sphereRenderer = sphereEntity.AddComponent<MeshRenderer>();
        sphereRenderer.Mesh = sphereMesh;
        sphereRenderer.Material = sphereMaterial;
        //------------------------------------------------------------------------------------
        
        return 0;
    }
}

/*
        //------------------------------------------------------------------------------------
        // MarchingSquares Testing
        Material marchingSquaresMaterial = TypedObjectManager.Create<Material>();
        marchingSquaresMaterial.SetShaderIndex(forwardRenderShader.InstanceID);
        marchingSquaresMaterial.RegisterShaderResource(testImageTexture.GetResource(), 1);
        // marchingSquaresMaterial.RegisterShaderResource(lightBuffer.GetResource(), 0);
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