#include <windows.h>
#include "File.h"
#include "NavigationManager.h"
#include "Marker.h"


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

    __declspec(dllexport) void Blacklist(unsigned int mapid, const char* Name, Vector3 spot, float r, unsigned int Type)
    {
        return MarkerCreator::AddMarker(mapid, Name, spot, r, Area::Blacklisted);
    }

    __declspec(dllexport) void Debugger(bool CanDebug)
    {
        NavigationManager::DEBUGMOD = CanDebug;
    }


};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    //MarkerCreator::AddMarker(0, "TestBlackListing", Vector3(-8898.23f, -119.838f, 81.83264f), 25.0f, Area::Blacklisted);

    NavigationManager* navigation = NavigationManager::GetInstance();
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        FileManager::MapPath = FileManager::GetMapPath();
        navigation->Initialize();
        navigation->LoadMap(0);
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

