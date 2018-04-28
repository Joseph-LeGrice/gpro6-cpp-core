#pragma once

#include <string>

typedef std::string TypeID;
typedef std::string ManagedTypeID;
typedef int32_t InstanceID;

#define REGISTER_TYPE(T) \
public: \
virtual const char* GetTypeName() override \
{ \
	return TO_STRING(T); \
}
