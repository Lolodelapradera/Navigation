#include "Pathfinder.h"
#include "AreaEnums.h"
#include "Defines.h"


PathFinder::PathFinder(unsigned int mapId, unsigned int instanceId) :
	polyLength(0), pointPathLimit(MAX_POINT_PATH_LENGTH),
	mapId(mapId), InstanceId(instanceId), navMesh(NULL), navMeshQuery(NULL)
{

	Mapper* Map = MapperHandle::MapHandle();
    std::cout << InstanceId << std::endl;
	navMesh = Map->GetNavMesh(mapId);
	navMeshQuery = Map->GetNavMeshQuery(mapId, InstanceId);
  
	SetFilters();


}

#pragma region PathfinderHelpers

void PathFinder::SetFilters()
{
	//Queryfilter.setAreaCost(Area::Walkable, 1);
	Queryfilter.setAreaCost(Area::LowThread, 100);
	Queryfilter.setAreaCost(Area::HighThread, 150);
	Queryfilter.setAreaCost(Area::Blacklisted, 1500);

    unsigned short includeFlags = 0;
    unsigned short excludeFlags = 0;
    includeFlags |= (0x01);

    Queryfilter.setIncludeFlags(includeFlags);
    Queryfilter.setExcludeFlags(excludeFlags);

}

bool PathFinder::HaveTile(const Vector3& p) const
{
	int tx, ty;
	float point[3] = { p.Y, p.Z, p.X };

	navMesh->calcTileLoc(point, &tx, &ty);

	if (navMesh->getTileAt(tx, ty, 0) == NULL)
	{
		std::cout << "Tile Failed" << std::endl;
	}

	return (navMesh->getTileAt(tx, ty, 0) != NULL);
}



bool PathFinder::inRangeYZX(const float* v1, const float* v2, float r, float h) const
{
    const float dx = v2[0] - v1[0];
    const float dy = v2[1] - v1[1]; // elevation
    const float dz = v2[2] - v1[2];
    return (dx * dx + dz * dz) < r * r && fabsf(dy) < h;
}

bool PathFinder::inRange(const Vector3& p1, const Vector3& p2, float r, float h) const
{
    Vector3 d = p1 - p2;
    return (d.X * d.X + d.Y * d.Y) < r * r && fabsf(d.Z) < h;
}
//
float PathFinder::dist3DSqr(const Vector3& p1, const Vector3& p2) const
{
    return (p1 - p2).squaredLength();
}

#pragma endregion


bool PathFinder::calculate(float originX, float originY, float originZ, float destX, float destY, float destZ)
{
	startPosition = Vector3(originX, originY, originZ);
	endPosition = Vector3(destX, destY, destZ);


	if (!navMesh || !navMeshQuery || !HaveTile(startPosition) || !HaveTile(endPosition))
	{
        std::cout << "error > PathFinder::calculate" << std::endl;
		clear();
		return false;
	}
	BuildPath(startPosition, endPosition);

}

bool PathFinder::BuildPath(Vector3 Start, Vector3 End)
{
    float* startPoint = Start.ToRecast().ToFloatArray().data();
    std::cout << startPoint[0] << " " << startPoint[1] << " " << startPoint[2] << std::endl;
    float* endPoint = End.ToRecast().ToFloatArray().data();
    std::cout << endPoint[0] << " " << endPoint[1] << " " << endPoint[2] << std::endl;

    float extents[VERTEX_SIZE] = { 3.0f, 5.0f, 3.0f };

    
    dtPolyRef startPoly;
    dtPolyRef endPoly;

    dtStatus startResult = navMeshQuery->findNearestPoly(startPoint, extents, &Queryfilter, &startPoly, startPoint);
    if (dtStatusFailed(startResult))
    {
        std::cout << "Error finding nearest poly for start point" << std::endl;
        return false;
    }

    dtStatus endResult = navMeshQuery->findNearestPoly(endPoint, extents, &Queryfilter, &endPoly, endPoint);
    if (dtStatusFailed(endResult))
    {
        std::cout << "Error finding nearest poly for end point" << std::endl;
        return false;
    }

    dtStatus dtResult = DT_FAILURE;
    int pathPointCount = 0; // Renamed from polyPathCount
    dtResult = navMeshQuery->findPath(
        startPoly,          // start polygon
        endPoly,            // end polygon
        startPoint,         // start position
        endPoint,           // end position
        &Queryfilter,       // polygon search filter
        pathPolyRefs,       // [out] path
        (int*)&pathPointCount,
        MAX_PATH_LENGTH);   // max number of polygons in output path.

    if (!pathPointCount || dtStatusFailed(dtResult))
    {
        std::cout << "Error finding path" << std::endl;
        return false;
    }

    // Make sure we don't exceed the maximum path point length
    pathPointCount = std::min(pathPointCount, MAX_POINT_PATH_LENGTH);

    pathPoints.resize(pathPointCount);
    for (int i = 0; i < pathPointCount; ++i)
    {
        std::cout << pathPolyRefs[i * VERTEX_SIZE] << " " << pathPolyRefs[i * VERTEX_SIZE + 1] 
            << " " << pathPolyRefs[i * VERTEX_SIZE + 2] << std::endl;
        pathPoints[i] = Vector3(pathPolyRefs[i * VERTEX_SIZE], pathPolyRefs[i * VERTEX_SIZE + 1], pathPolyRefs[i * VERTEX_SIZE + 2]);
    }

    return true;
}

