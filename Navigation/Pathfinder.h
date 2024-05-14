#pragma once
#include <vector>
#include <DetourNavMeshQuery.h>
#include "NavigationManager.h"
#include "Defines.h"



class PathFinder
{
public:

	PathFinder(unsigned int mapId, unsigned int instanceId);
	bool calculate(float originX, float originY, float originZ, float destX, float destY, float destZ);

	bool BuildPath(Vector3 Start, Vector3 End);





private:


	void SetFilters();

	bool inRangeYZX(const float* v1, const float* v2, float r, float h) const;
	bool inRange(const Vector3& p1, const Vector3& p2, float r, float h) const;



	void clear()
	{
		polyLength = 0;
		pathPoints.clear();
	}
	/**
	 * @brief Query filter used for navigation queries.
	 */
	dtQueryFilter Queryfilter;

	/**
	 * @brief Array to store maximum polygon counts.
	 *
	 * @param MAX_PATH_LENGTH The maximum length of the path.
	 */
	dtPolyRef pathPolyRefs[MAX_PATH_LENGTH];


	std::vector<Vector3>  pathPoints;

	/**
	 * @brief Length of the polygon array.
	 */
	unsigned int polyLength;

	/**
	 * @brief Checks if a tile is present at the specified position.
	 *
	 * @param p The position to check.
	 * @return True if a tile is present at the specified position, false otherwise.
	 */
	bool HaveTile(const Vector3& p) const;

	/**
	 * @brief Pointer to the navigation mesh.
	 */
	const dtNavMesh* navMesh;

	/**
	 * @brief Pointer to the navigation mesh query.
	 */
	const dtNavMeshQuery* navMeshQuery;

	bool useStraightPath;  // type of path will be generated
	bool forceDestination; // when set, we will always arrive at given point
	unsigned int pointPathLimit;   // limit point path size; min(this, MAX_POINT_PATH_LENGTH)

	Vector3 startPosition;    // {x, y, z} of current location
	Vector3 endPosition;      // {x, y, z} of the destination
	Vector3 actualEndPosition;// {x, y, z} of the closest possible point to given destination

	const unsigned int  mapId;       // map id
	const unsigned int  InstanceId;       // instance id



};


