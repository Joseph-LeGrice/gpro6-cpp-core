#include "stdafx.h"
#include "Application.h"

StaticPointer<Application> Application::s_instance;
std::wstring Application::s_resourceFullPath;

std::wstring Application::GetResourcePath(std::wstring relativePath)
{
    std::wstringstream ss;
    ss << s_instance->m_resourceFullPath << relativePath;
    return ss.str();
}

Application::Application()
{
    wchar_t result[MAX_PATH];
    std::wstring exePath = std::wstring(result, GetModuleFileNameW(NULL, result, MAX_PATH));
    size_t index = exePath.find_last_of('\\');
    m_executablePath = exePath.substr(0, index);

    std::wstringstream ss; 
    ss << m_executablePath << "\\" << c_resourceRelativePath;
    m_resourceFullPath = ss.str();
}
