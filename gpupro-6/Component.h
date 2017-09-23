#pragma once

class Entity;
class SceneGraph;

class Component
{
	friend SceneGraph;
	friend Entity;

public:
	Component();
	virtual ~Component();

	virtual void Init();
	virtual void Tick();
	virtual void DeInit();
};

