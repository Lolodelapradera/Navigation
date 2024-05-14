#include <windows.h>
#include "File.h"
#include "NavigationManager.h"


extern "C"
{
    __declspec(dllexport) Vector3* CalculatePath(unsigned int mapId, Vector3 start, Vector3 end/*, bool smoothPath*/, int* length)
    {

        return NavigationManager::GetInstance()->CalculatePath(mapId, start, end, length);
    }

    __declspec(dllexport) void FreePathArr(Vector3* pathArr)
    {
        return NavigationManager::GetInstance()->FreePathArr(pathArr);
    }
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    NavigationManager* navigation = NavigationManager::GetInstance();
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        FileManager::MapPath = FileManager::GetMapPath();
        navigation->Initialize();
        //navigation->LoadMap();
        break;

    case DLL_PROCESS_DETACH:
        navigation->Release();
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}

