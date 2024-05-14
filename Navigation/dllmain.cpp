#include <iostream>
#include "File.h"
#include "NavigationManager.h"


NavigationManager* Instance = nullptr;

extern "C"
{
    __declspec(dllexport) Vector3* CalculatePath(unsigned int mapId, Vector3 start, Vector3 end/*, bool smoothPath*/, int* length)
    {
        return Instance->CalculatePath(mapId, start, end, length);
    }

    __declspec(dllexport) void FreePathArr(Vector3* pathArr)
    {
        return Instance->FreePathArr(pathArr);
    }

};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        FileManager::MapPath = FileManager::GetMapPath();
        Instance->GetInstance();
        Instance->Initialize();
        Instance->LoadMap();
        break;

    case DLL_THREAD_ATTACH:
        Instance->Release();
        break;
    }
    return TRUE;
}

