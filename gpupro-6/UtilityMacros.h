#pragma once

#define SAFE_DELETE_VECTOR_STACK(obj)\
{\
	for (size_t i=0; i<obj.size(); ++i)\
	{\
		SAFE_DELETE(obj[i]);\
	}\
}\

#define SAFE_DELETE_VECTOR_HEAP(obj)\
{\
	for (size_t i=0; i<obj->size(); ++i)\
	{\
		SAFE_DELETE(obj->at(i));\
	}\
	SAFE_DELETE(obj);\
}\

#define SAFE_DELETE(obj) { if (obj) delete (obj); (obj) = nullptr; }
#define SAFE_RELEASE(obj) { if (obj) { obj->Release(); (obj) = nullptr; } }