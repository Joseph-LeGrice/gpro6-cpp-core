using System.Runtime.CompilerServices;

public enum PropertyValueType
{
	Integer   = 0,
	Boolean   = 1,
	Float     = 2,
	Float2    = 3,
	Float3    = 4,
	Float4    = 5,
	Matrix3x3 = 6,
	Matrix4x4 = 7
};

public struct PropertyInitializer
{
	string m_propertyName;
	PropertyValueType m_valueType;

	public PropertyInitializer(string name, PropertyValueType value)
	{
		m_propertyName = name;
		m_valueType = value;
	}
};

public enum BlendFactor
{
    Zero = 0,
    One = 1,
    Src = 2,
    SrcInverse = 3,
    Dest = 4,
    DestInverse = 5
};

public enum BlendOperation
{
    Add = 0,
    Subtract = 1,
    SubtractReverse = 2,
    Min = 3,
    Max = 4
};

public enum CullState
{
    None = 0,
    Front = 1,
    Back = 2
};

public enum FillMode
{
    Solid = 0,
    Wireframe = 1
};

public class Material : ITypedObject
{
// ## Generated Code ##
	public static string GetTypeID()
	{
		return "Material";
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetShader(int instanceid, ITypedObject arg0);

	public void SetShader(ITypedObject arg0)
	{
		SetShader(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void RegisterShaderResource(int instanceid, ITypedObject arg0, int arg1);

	public void RegisterShaderResource(ITypedObject arg0, int arg1)
	{
		RegisterShaderResource(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void AddTextureSampler(int instanceid, ITypedObject arg0, int arg1);

	public void AddTextureSampler(ITypedObject arg0, int arg1)
	{
		AddTextureSampler(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void InitProperties(int instanceid, PropertyInitializer[] arg0);

	public void InitProperties(PropertyInitializer[] arg0)
	{
		InitProperties(InstanceID, arg0);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetInteger(int instanceid, string arg0, int arg1);

	public void SetInteger(string arg0, int arg1)
	{
		SetInteger(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetBoolean(int instanceid, string arg0, bool arg1);

	public void SetBoolean(string arg0, bool arg1)
	{
		SetBoolean(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetFloat(int instanceid, string arg0, float arg1);

	public void SetFloat(string arg0, float arg1)
	{
		SetFloat(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetFloat2(int instanceid, string arg0, Vector2 arg1);

	public void SetFloat2(string arg0, Vector2 arg1)
	{
		SetFloat2(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetFloat3(int instanceid, string arg0, Vector3 arg1);

	public void SetFloat3(string arg0, Vector3 arg1)
	{
		SetFloat3(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetFloat4(int instanceid, string arg0, Vector4 arg1);

	public void SetFloat4(string arg0, Vector4 arg1)
	{
		SetFloat4(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetMatrix3x3(int instanceid, string arg0, Matrix3x3 arg1);

	public void SetMatrix3x3(string arg0, Matrix3x3 arg1)
	{
		SetMatrix3x3(InstanceID, arg0, arg1);
	}


	[MethodImpl(MethodImplOptions.InternalCall)]
	private extern static void SetMatrix4x4(int instanceid, string arg0, Matrix4x4 arg1);

	public void SetMatrix4x4(string arg0, Matrix4x4 arg1)
	{
		SetMatrix4x4(InstanceID, arg0, arg1);
	}


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void SetCullState_Internal(int arg0, int arg1);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void SetFillMode_Internal(int arg0, int arg1);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void SetColorBlending_Internal(int arg0, int arg1, int arg2, int arg3);


	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	public extern static void SetAlphaBlending_Internal(int arg0, int arg1, int arg2, int arg3);

// ## Generated Code ##

	public void SetCullState(CullState state)
	{
		SetCullState_Internal(InstanceID, (int)state);
	}

	public void SetFillMode(FillMode mode)
	{
		SetFillMode_Internal(InstanceID, (int)mode);
	}

	public void SetColorBlending(BlendFactor src, BlendFactor dest, BlendOperation op)
	{
		SetColorBlending_Internal(InstanceID, (int)src, (int)dest, (int)op);
	}

	public void SetAlphaBlending(BlendFactor src, BlendFactor dest, BlendOperation op)
	{
		SetAlphaBlending_Internal(InstanceID, (int)src, (int)dest, (int)op);
	}
}