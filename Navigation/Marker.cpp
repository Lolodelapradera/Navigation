#include "Marker.h"
#include <iostream>
#include "NavigationManager.h"


std::vector<Marker> MarkerCreator::Marks;
void MarkerCreator::AddMarker(unsigned int mapid, const char* name, Vector3 position, float radius, Area type)
{
    if (NavigationManager::DEBUGMOD)
    {
        std::cout << "[Marker] Adding " << name << " MapID " << mapid << " x: " << position.X << " y: " << position.Y << " z: " << position.Z << " radius: " 
            << radius << " Type: " << type << std::endl;
    }
    Marks.emplace_back(Marker(mapid, name, position, radius, type));
}

void MarkerCreator::RemoveMarker(unsigned int mapid)
{
    auto it = std::remove_if(Marks.begin(), Marks.end(), [mapid](const Marker& marker) {
        return marker.Mapid == mapid;
        });
    Marks.erase(it, Marks.end());
}

void MarkerCreator::RemoveMarker(const char* name)
{
    auto it = std::remove_if(Marks.begin(), Marks.end(), [name](const Marker& marker) {
        return std::strcmp(marker.Name, name) == 0;
        });
    Marks.erase(it, Marks.end());
}