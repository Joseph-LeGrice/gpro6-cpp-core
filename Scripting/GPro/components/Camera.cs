using System.Runtime.CompilerServices;

public class Camera : IComponent
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Camera";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetOrthographic(int instanceid, float arg0, float arg1, float arg2);

	public void SetOrthographic(float arg0, float arg1, float arg2)
	{
		SetOrthographic(InstanceID, arg0, arg1, arg2);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetPerspective(int instanceid, float arg0, float arg1, float arg2, float arg3);

	public void SetPerspective(float arg0, float arg1, float arg2, float arg3)
	{
		SetPerspective(InstanceID, arg0, arg1, arg2, arg3);
	}

// ## Generated Code ##
}