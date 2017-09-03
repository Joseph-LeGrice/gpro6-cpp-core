#pragma once

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init();
	virtual void Tick();
	virtual void DeInit();

private:
	Component(const Component&) = delete;
};

