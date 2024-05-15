#include "Pathfinder.h"
#include "Marker.h"
#include "AreaEnums.h"


bool PathFinder::ApplyCircleBlacklistToPolys(dtNavMeshQuery* meshQuery, const dtNavMesh* navmesh, dtQueryFilter query, Marker Options)
{
    if (!meshQuery || !navmesh)
    {
        std::cerr << "MeshQuery or NavMesh is null." << std::endl;
        return false;
    }
    float searchBoxSize[VERTEX_SIZE] = { 3.0f, 5.0f, 3.0f };
    float* searchPoint = Options.position.ToRecast().ToFloatArray().data();

    dtPolyRef CenterPoly;
    float CenterPolyPoint[3];
    dtStatus startResult = meshQuery->findNearestPoly(searchPoint, searchBoxSize, &query, &CenterPoly, CenterPolyPoint);
    if (dtStatusFailed(startResult)) {
        std::cerr << "Failed to find nearest poly." << std::endl;
        return false;
    }

    const int POLY_ARRAY_MAX = 1000;
    dtPolyRef polyRefsInCircle[POLY_ARRAY_MAX];
    int polyRefInCircleCount = 0;

    dtStatus circleResult = meshQuery->findPolysAroundCircle(CenterPoly, searchPoint, Options.radius, &query, polyRefsInCircle, nullptr, nullptr, &polyRefInCircleCount, POLY_ARRAY_MAX);
    if (dtStatusFailed(circleResult)) {
        std::cerr << "Failed to find polys around circle." << std::endl;
        return false;
    }

    for (int i = 0; i < polyRefInCircleCount; ++i) {
        dtPolyRef polyRef = polyRefsInCircle[i];

        const dtMeshTile* tile = nullptr;
        const dtPoly* poly = nullptr;

        dtStatus tileAndPolyStatus = navmesh->getTileAndPolyByRef(polyRef, &tile, &poly);
        if (dtStatusFailed(tileAndPolyStatus) || !poly)
        {
            std::cerr << "Error retrieving tile and polygon by ref." << std::endl;
            continue;
        }

        // Modify the polygon area directly by using mutablePoly
        dtPoly* mutablePoly = const_cast<dtPoly*>(poly);

        if (NavigationManager::DEBUGMOD)
        {
            std::cout << "Polygon area: " << static_cast<int>(mutablePoly->getArea()) << std::endl;
        }

        // Example: Set area ID to 35 (or any specific value you want)
        mutablePoly->setArea(Options.Type);

        if (NavigationManager::DEBUGMOD)
        {
            // Debug output: Print the updated area of the mutablePoly
            std::cout << "Polygon area after setting: " << static_cast<int>(mutablePoly->getArea()) << std::endl;
        }

        //// If flags need to be set directly to 35
        //dtStatus setFlagsStatus = navMesh->setPolyFlags(polyRef, 35);
        //if (dtStatusFailed(setFlagsStatus)) {
        //    std::cerr << "Error setting polygon flags." << std::endl;
        //    continue;
        //}

        //// Verify the flags were set correctly
        //unsigned short verifyFlags;
        //dtStatus verifyStatus = navMesh->getPolyFlags(polyRef, &verifyFlags);
        //if (dtStatusFailed(verifyStatus)) {
        //    std::cerr << "Error verifying polygon flags." << std::endl;
        //    continue;
        //}

        // Debug output: Print the verified flags
        /*std::cout << "Polygon flags set to: " << verifyFlags << std::endl;*/
    }

    return true;
}









void PathFinder::SetFilters()
{
	//Queryfilter.setAreaCost(Area::Walkable, 1);
	Queryfilter.setAreaCost(Area::LowThread, 100);
	Queryfilter.setAreaCost(Area::HighThread, 150);
	Queryfilter.setAreaCost(Area::Blacklisted, 1000);

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
	auto r = navMesh->getTileAt(tx, ty, 0);
	

	if (r == NULL)
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

dtPolyRef PathFinder::GetNearestPoly(const float* startPoint) const
{
	dtPolyRef startPoly;
	float startPolyPoint[3];
	dtStatus results =  navMeshQuery->findNearestPoly(startPoint, PathFinder::searchBoxSize, &Queryfilter, &startPoly, startPolyPoint);
	if (dtStatusFailed(results))
	{
		std::cout << "Failed to GetNearestPoly" << std::endl;
		return NULL;
	}
	return startPoly;
}
