#pragma once

#include <vector>
#include <type_traits>
#include "Engine/Core/Utilities/HeapAllocation.h"

namespace MaterialProperty
{
	enum ValueType
	{
		kIntegerProperty   = 0,
		kBooleanProperty   = 1,
		kFloatProperty     = 2,
		kFloat2Property    = 3,
		kFloat3Property    = 4,
		kFloat4Property    = 5,
		kMatrix3x3Property = 6,
		kMatrix4x4Property = 7
	};

	struct Initializer
	{
		std::wstring m_propertyName;
		ValueType m_valueType;

		Initializer(std::wstring propertyName, ValueType valueType) :
			m_propertyName(propertyName), m_valueType(valueType) { }
	};

	class List
	{
	public:

		void Initalize(std::vector<Initializer> initialValues);

		void SetInteger(std::wstring name, int value);
		void SetBoolean(std::wstring name, BOOL value);
		void SetFloat(std::wstring name, float value);
		void SetFloat2(std::wstring name, Vector2 value);
		void SetFloat3(std::wstring name, Vector3 value);
		void SetFloat4(std::wstring name, Vector4 value);
		void SetMatrix3x3(std::wstring name, Matrix3x3 value);
		void SetMatrix4x4(std::wstring name, Matrix4x4 value);

		void* GetData();
		size_t GetDataLength();

	private:
		union PropertyValue
		{
			int integerValue;
			BOOL booleanValue;
			float floatValue;
			Vector4 float4Value;
			Vector3 float3Value;
			Vector2 float2Value;
			Matrix3x3 matrix3x3Value;
			Matrix4x4 matrix4x4Value;
		};

		struct Property
		{
			std::wstring m_propertyName;
			PropertyValue m_value;
			ValueType m_valueType;
		};

		bool m_initialized;
		HeapAllocation m_propertyAlloc;
		std::vector<Property> m_properties;
		Property* GetProperty(std::wstring name);
		size_t GetPropertySize(Property p);
		PropertyValue GetDefaultValue(ValueType vt);
	};
}