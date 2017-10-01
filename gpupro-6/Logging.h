#pragma once
#include <iostream>

inline void Log(const char* msg)
{
	std::cout << "LOG: " << msg << std::endl;
}

inline void LogError(const char* msg)
{
	std::cout << "ERROR: " << msg << std::endl;
}