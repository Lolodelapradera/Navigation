#include "NavigationManager.h"
#include "Mapper.h"
#include "PathFinder.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include "File.h"


NavigationManager* NavigationManager::s_singletonInstance = nullptr;
NavigationManager* NavigationManager::GetInstance()
{
    if (s_singletonInstance == NULL)
        s_singletonInstance = new NavigationManager();

    return s_singletonInstance;
}
void NavigationManager::Initialize()
{
    dtAllocSetCustom(dtCustomAlloc, dtCustomFree);
}


void NavigationManager::Release()
{

    MapperHandle::MapHandle()->~Mapper();
}

void NavigationManager::FreePathArr(Vector3* pathArr)
{
    delete[] pathArr;
}

void NavigationManager::InitializeMaps(Mapper* manager, unsigned int mapId)
{
    if (!manager->zoneMap.contains(mapId))
    {
        for (auto& p : std::filesystem::directory_iterator(FileManager::MapPath))
        {
            std::string path = p.path().string();
            std::string extension = path.substr(path.find_last_of(".") + 1);
            if (extension == "mmtile")
            {
                std::string filename = path.substr(path.find_last_of("\\") + 1);

                int xTens = filename[3] - '0';
                int xOnes = filename[4] - '0';
                int yTens = filename[5] - '0';
                int yOnes = filename[6] - '0';

                int x = (xTens * 10) + xOnes;
                int y = (yTens * 10) + yOnes;

               
                std::string mapIdString;
                if (mapId < 10)
                    mapIdString = "00" + std::to_string(mapId);
                else if (mapId < 100)
                    mapIdString = "0" + std::to_string(mapId);
                else
                    mapIdString = std::to_string(mapId);

                if (filename[0] == mapIdString[0] && filename[1] == mapIdString[1] && filename[2] == mapIdString[2])
                    manager->loadMap(mapId, x, y);
            }
        }

        manager->zoneMap.insert(std::pair<unsigned int, bool>(mapId, true));
    }
}

void NavigationManager::LoadMap()
{
    Mapper* maphandler = MapperHandle::MapHandle();
    InitializeMaps(maphandler, 0);
    /*InitializeMaps(maphandler, 1);
    InitializeMaps(maphandler, 530);
    InitializeMaps(maphandler, 571);*/
}

Vector3* NavigationManager::CalculatePath(unsigned int mapId, Vector3 start, Vector3 end /*,int* length*/)
{
    PathFinder pathFinder(mapId, 1);

    pathFinder.calculate(start.X, start.Y, start.Z, end.X, end.Y, end.Z);


    return NULL;
}
