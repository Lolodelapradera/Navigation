#pragma once
#include "Vector3.h"
#include "AreaEnums.h"
#include <vector>


class Marker
{
public:
    unsigned int Mapid;
    const char* Name;
    Vector3 position;
    float radius;
    Area Type;

    Marker(unsigned int mapid, const char* name, Vector3 position, float radius, Area type)
        : Mapid(mapid), Name(name), position(position), radius(radius), Type(type) {}

};

class MarkerCreator
{
public:

    static void AddMarker(unsigned int mapid, const char* name, Vector3 position, float radius, Area type);
    static void RemoveMarker(unsigned int mapid);
    static void RemoveMarker(const char* name);

    static std::vector<Marker> Marks;

//private:
//    static std::vector<Marker> Marks;
};