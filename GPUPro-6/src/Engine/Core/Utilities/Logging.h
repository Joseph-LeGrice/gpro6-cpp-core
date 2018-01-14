#pragma once
#include <iostream>
#include <string>
#include <sstream>

inline void Log(std::wstring msg)
{
    OutputDebugStringW(msg.append(L"\n").c_str());
}

inline void Log(std::string msg)
{
    OutputDebugStringA(msg.append("\n").c_str());
}

inline void LogError(std::string msg)
{
    OutputDebugStringA(msg.append("\n").c_str());
}
