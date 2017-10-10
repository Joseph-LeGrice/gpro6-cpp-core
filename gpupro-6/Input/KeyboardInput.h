#pragma once
class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();
	KeyboardInput(const KeyboardInput&) = delete;
	void HandleInput(MSG msg);
	//bool GetKey(InputKey key);
	//bool GetKeyDownThisFrame(InputKey key);
	//bool GetKeyUpThisFrame(InputKey key);
};

