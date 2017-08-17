#pragma once
class Component
{
public:
	Component();
	~Component();

	virtual void Init();
	virtual void Tick();
	virtual void DeInit();
};

