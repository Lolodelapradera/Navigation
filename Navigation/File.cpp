#include "File.h"

std::string FileManager::GetModulePath()
{
    HMODULE hModule = GetModuleHandle(NULL);
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(hModule, szPath, MAX_PATH);
    std::string modulePath = std::string(szPath);

    size_t lastBackslashPos = modulePath.find_last_of("\\");
    if (lastBackslashPos != std::string::npos) {
        modulePath = modulePath.substr(0, lastBackslashPos);
    }
    modulePath += "\\"; // Corrected this line

    return modulePath;
}

std::string FileManager::GetMapPath()
{
    std::string ModulePath = GetModulePath();
    ModulePath += "mmaps\\";

    // Check if the directory exists
    if (!std::filesystem::exists(ModulePath)) {
        return ""; // Return empty string if the directory doesn't exist
    }

    return ModulePath;
}

std::string FileManager::MapPath = "";
