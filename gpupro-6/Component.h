#pragma once

class Entity;
class SceneGraph;

class Component
{
	friend SceneGraph;
	friend Entity;

public:
	virtual void Init();
	virtual void Tick();
	virtual void DeInit();

protected:
	Component();
	virtual ~Component();

private:
	Component(const Component&) = delete;
};

