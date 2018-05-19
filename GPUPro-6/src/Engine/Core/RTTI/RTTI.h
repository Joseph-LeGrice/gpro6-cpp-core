#pragma once

#include <string>

typedef std::string TypeID;
typedef std::string ManagedTypeID;
typedef int32_t InstanceID;
#define InvalidInstanceID -1

#define REGISTER_TYPE(T) \
public: \
static TypeID GetTypeID() \
{ \
	return std::string(TO_STRING(T)); \
}
