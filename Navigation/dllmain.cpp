#include <iostream>
#include "File.h"
#include "NavigationManager.h"


NavigationManager* Instance = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        FileManager::MapPath = FileManager::GetMapPath();
        Instance->GetInstance();
        Instance->LoadMap();

        

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

