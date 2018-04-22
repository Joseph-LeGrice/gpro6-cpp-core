#pragma once

typedef uint32_t TypeID;
typedef int32_t InstanceID;

template<typename T>
TypeID GetTypeID() { throw "Unknown TypeID"; }

#define REGISTER_TYPE(T, typeId) \
const RegisterType<T, typeId> static_registration_##T; \
template<> inline TypeID GetTypeID<T>() { return static_registration_##T.GetTypeID(); }
