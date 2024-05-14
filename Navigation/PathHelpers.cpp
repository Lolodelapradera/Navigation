#include "Pathfinder.h"
#include "AreaEnums.h"



bool PathFinder::ApplyCircleBlacklistToPolys(dtNavMeshQuery* meshQuery, Vector3 blacklistPoint, float radius)
{
	float* searchPoint = blacklistPoint.ToRecast().ToFloatArray().data();
	Mapper* Map = MapperHandle::MapHandle();
	auto NavMesh = Map->loadedMMaps[0]->navMesh;


	dtPolyRef CenterPoly;
	float CenterPolyPoint[3];
	dtStatus startResult = meshQuery->findNearestPoly(searchPoint, PathFinder::searchBoxSize, &Queryfilter, &CenterPoly, CenterPolyPoint);

	const int POLY_ARRAY_MAX = 50;
	dtPolyRef polyRefsInCircle[POLY_ARRAY_MAX];
	int polyRefInCircleCount;

	meshQuery->findPolysAroundCircle(CenterPoly, searchPoint, radius, &Queryfilter, polyRefsInCircle, nullptr, nullptr, &polyRefInCircleCount, POLY_ARRAY_MAX);

	for (int i = 0; i < polyRefInCircleCount; i++)
	{
		dtPolyRef polyRef = polyRefsInCircle[i];

		const dtMeshTile* tile;
		const dtPoly* poly;

		// Get the tile and polygon reference safely
	
		NavMesh->getTileAndPolyByRef(polyRef, &tile, &poly);




		//dtStatus status = navMesh->getTileAndPolyByRef(polyRef, &tile, &poly);


		if (poly)
		{
			std::cout << "settings 55" << std::endl;
			// Cast away const to modify the area type

			dtPoly* mutablePoly = const_cast<dtPoly*>(poly);

			mutablePoly->setArea(Area::Blacklisted);
		}
	}

	return false;
}




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
