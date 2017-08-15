#pragma once

#define SAFE_DELETE(obj) { if (obj) delete (obj); (obj) = nullptr; }
#define SAFE_RELEASE(obj) { if (obj) { obj->Release(); (obj) = nullptr; } }