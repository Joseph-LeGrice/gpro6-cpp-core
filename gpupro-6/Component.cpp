#include "stdafx.h"
#include "Component.h"

#include <iostream>

Component::Component()
{
}


Component::~Component()
{
}

void Component::Init()
{
	std::cout << "Component Init" << std::endl;
}

void Component::Tick()
{
	std::cout << "Component Tick" << std::endl;
}

void Component::DeInit()
{
	std::cout << "Component Deinit" << std::endl;
}
