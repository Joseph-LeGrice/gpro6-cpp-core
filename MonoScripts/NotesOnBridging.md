# Notes on C# Bridging

## List of Systems to Bridge:
- SceneGraph -> CreateComponent
- ResourceManager -> CreateResource
- VoxelTerrain -> CreateTerrain

## List of Resources to Bridge:
- Mesh
- Shader
- Texture2D
- Texture2DArray
- StructuredBuffer
- TextureSampler
- SimpleMaterial
- StandardMaterial

## List of Components to Bridge:
- Entity
- Light
- Camera
- Transform
- MeshRenderer

## Utilities
- Application::GetResourcePath
- DrawCommands?