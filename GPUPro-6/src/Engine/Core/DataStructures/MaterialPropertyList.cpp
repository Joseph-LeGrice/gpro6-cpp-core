#include "stdafx.h"
#include "MaterialPropertyList.h"

void MaterialPropertyList::Initalize(std::vector<PropertyInitializer> initialValues)
{
	m_properties.resize(initialValues.size());
	for (int i = 0; i < initialValues.size(); i++)
	{
		m_properties[i].m_propertyName = initialValues[i].m_propertyName;
		m_properties[i].m_valueType = initialValues[i].m_valueType;
	}

	size_t storageSize = GetDataLength();
	m_propertyAlloc.Allocate(storageSize);
}

void* MaterialPropertyList::GetData()
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

size_t MaterialPropertyList::GetDataLength()
{
	size_t size = 0;
	for (int i = 0; i < m_properties.size(); i++)
	{
		Property& p = m_properties[i];
		size += GetPropertySize(p);
	}
	return size;
}

MaterialPropertyList::Property* MaterialPropertyList::GetProperty(std::wstring name)
{
	for (int i = 0; i < m_properties.size(); i++)
	{
		if (m_properties[i].m_propertyName == name)
		{
			return &m_properties[i];
		}
	}
	return nullptr;
}

size_t MaterialPropertyList::GetPropertySize(Property p)
{
	switch (p.m_valueType)
	{
	case kIntegerProperty:
		return sizeof(int);
	case kBooleanProperty:
		return sizeof(bool);
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

void MaterialPropertyList::SetInteger(std::wstring name, int value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kIntegerProperty)
	{
		p->m_value.integerValue = value;
	}
}


void MaterialPropertyList::SetBoolean(std::wstring name, bool value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kBooleanProperty)
	{
		p->m_value.booleanValue = value;
	}
}

void MaterialPropertyList::SetFloat(std::wstring name, float value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloatProperty)
	{
		p->m_value.floatValue = value;
	}
}

void MaterialPropertyList::SetFloat2(std::wstring name, Vector2 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat2Property)
	{
		p->m_value.float2Value = value;
	}
}

void MaterialPropertyList::SetFloat3(std::wstring name, Vector3 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat3Property)
	{
		p->m_value.float3Value = value;
	}
}

void MaterialPropertyList::SetFloat4(std::wstring name, Vector4 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kFloat4Property)
	{
		p->m_value.float4Value = value;
	}
}

void MaterialPropertyList::SetMatrix3x3(std::wstring name, Matrix3x3 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kMatrix3x3Property)
	{
		p->m_value.matrix3x3Value = value;
	}
}

void MaterialPropertyList::SetMatrix4x4(std::wstring name, Matrix4x4 value)
{
	Property* p = GetProperty(name);
	if (p != nullptr && p->m_valueType == kMatrix4x4Property)
	{
		p->m_value.matrix4x4Value = value;
	}
}