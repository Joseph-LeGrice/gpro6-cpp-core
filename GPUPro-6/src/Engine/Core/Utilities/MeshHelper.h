#pragma once

class Mesh;

//TODO: Create the mesh only once, then save the resource id off and reference that.
namespace MeshHelper
{
	Mesh* CreateQuad(); //FIXME: Quad broken?
	Mesh* CreateSphereICO(); //TODO: Implement SphereIco?
	Mesh* CreateSphereUV(); 
	Mesh* CreateCube();
};
