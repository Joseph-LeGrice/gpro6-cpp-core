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
	Entity& GetEntity();

protected:
	Component();
	virtual ~Component();

private:
	Entity* m_entity;

	Component(const Component&) = delete;
};

