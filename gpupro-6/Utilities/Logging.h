#pragma once
#include <iostream>
#include <string>
#include <sstream>

inline void Log(std::string msg)
{
    OutputDebugStringA(msg.c_str());
}

inline void LogError(std::string msg)
{
    OutputDebugStringA(msg.c_str());
}