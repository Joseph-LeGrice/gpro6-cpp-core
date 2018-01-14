#pragma once

class Application
{
public:
    static std::wstring GetResourcePath();
    Application();

private:
    static StaticPointer<Application> s_instance;
    static std::wstring s_resourceFullPath;
    
    std::wstring m_executablePath;
    std::wstring m_resourceFullPath;
    const std::wstring c_resourceRelativePath = L"Resources\\";
};
