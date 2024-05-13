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
        Instance->Initialize();
        Instance->LoadMap();
        

        Instance->CalculatePath(0, Vector3(-8949.95f, -132.493f, 83.5312f), Vector3(-8831.653f, -97.78971f, 84.78954f));
       
        

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

