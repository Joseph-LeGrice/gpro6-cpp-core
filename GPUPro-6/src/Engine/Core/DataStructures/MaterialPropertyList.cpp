#include "stdafx.h"
#include "MaterialPropertyList.h"

using namespace MaterialProperty;

void List::Initalize(std::vector<Initializer> initialValues)
{
	m_initialized = true;
	m_properties.resize(initialValues.size());
	for (int i = 0; i < initialValues.size(); i++)
	{
		m_properties[i].m_propertyName = initialValues[i].m_propertyName;
		m_properties[i].m_valueType = initialValues[i].m_valueType;
		m_properties[i].m_value = GetDefaultValue(initialValues[i].m_valueType);
	}

	size_t storageSize = GetDataLength();
	if (storageSize > 0)
	{
		m_propertyAlloc.Allocate(storageSize);
	}
}

void* List::GetData()
{
	unsigned char* data = static_cast<unsigned char*>(m_propertyAlloc.GetPointer());
	
	size_t currentPosition = 0;
	for (int i = 0; i < m_properties.size(); i++)
	{
		Property& p = m_properties[i];
		size_t propSize = GetPropertySize(p);
		auto v = p.m_value;
		memcpy(&data[currentPosition], &v, propSize);
		currentPosition += propSize;
	}

	return data;
}

size_t List::GetDataLength()
{
	size_t size = 0;
	for (int i = 0; i < m_properties.size(); i++)
	{
		Property& p = m_properties[i];
		size += GetPropertySize(p);
	}
	return size;
}

List::Property* List::GetProperty(std::wstring name)
{
	custom_assert::is_true(m_initialized, "List has not been initialized!");
	for (int i = 0; i < m_properties.size(); i++)
	{
		if (m_properties[i].m_propertyName == name)
		{
			return &m_properties[i];
		}
	}
	return nullptr;
}

size_t List::GetPropertySize(Property p)
{
	switch (p.m_valueType)
	{
	case kIntegerProperty:
		return sizeof(int);
	case kBooleanProperty:
		return sizeof(BOOL);
	case kFloatProperty:
		return sizeof(float);
	case kFloat2Property:
		return sizeof(Vector2);
	case kFloat3Property:
		return sizeof(Vector3);
	case kFloat4Property:
		return sizeof(Vector4);
	case kMatrix3x3Property:
		return sizeof(Matrix3x3);
	case kMatrix4x4Property:
		return sizeof(Matrix4x4);
	}
	throw "Could not get property size";
}

void List::SetInteger(std::wstring name, int value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kIntegerProperty)
	{
		p->m_value.integerValue = value;
	}
}


void List::SetBoolean(std::wstring name, BOOL value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kBooleanProperty)
	{
		p->m_value.booleanValue = value;
	}
}

void List::SetFloat(std::wstring name, float value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloatProperty)
	{
		p->m_value.floatValue = value;
	}
}

void List::SetFloat2(std::wstring name, Vector2 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat2Property)
	{
		p->m_value.float2Value = value;
	}
}

void List::SetFloat3(std::wstring name, Vector3 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat3Property)
	{
		p->m_value.float3Value = value;
	}
}

void List::SetFloat4(std::wstring name, Vector4 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat4Property)
	{
		p->m_value.float4Value = value;
	}
}

void List::SetMatrix3x3(std::wstring name, Matrix3x3 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kMatrix3x3Property)
	{
		p->m_value.matrix3x3Value = value;
	}
}

void List::SetMatrix4x4(std::wstring name, Matrix4x4 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kMatrix4x4Property)
	{
		p->m_value.matrix4x4Value = value;
	}
}

MaterialProperty::List::PropertyValue MaterialProperty::List::GetDefaultValue(ValueType vt)
{
	PropertyValue pt;
	switch (vt)
	{
	case kIntegerProperty:
		pt.integerValue = 0;
		break;
	case kBooleanProperty:
		pt.booleanValue = FALSE;
		break;
	case kFloatProperty:
		pt.floatValue = 0.0f;
		break;
	case kFloat2Property:
		pt.float2Value = { 0, 0 };
		break;
	case kFloat3Property:
		pt.float3Value = { 0, 0, 0 };
		break;
	case kFloat4Property:
		pt.float4Value = { 0, 0, 0, 0 };
		break;
	case kMatrix3x3Property:
		Matrix3x3 m33;
		Matrix3x3::Identity(m33);
		pt.matrix3x3Value = m33;
		break;
	case kMatrix4x4Property:
		Matrix4x4 m44;
		Matrix4x4::Identity(m44);
		pt.matrix4x4Value = m44;
		break;
	default:
		throw "Could not get property size";
	}
	return pt;
}
