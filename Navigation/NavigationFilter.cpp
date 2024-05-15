#include "NavigationFilter.h"
#include "Marker.h"
#include <iostream>


bool NavivationFilter::passFilter(const dtPolyRef polyRef, const dtMeshTile* tile, const dtPoly* poly) const
{
    for (const Marker& Entry : MarkerCreator::Marks)
    {
        std::array<float, 3> entry = Entry.position.ToRecast().ToFloatArray();

        const float* VertsPoints = &tile->verts[0];
        for (int i = 0; i < tile->header->polyCount; ++i)
        {
            dtPoly* poly = &tile->polys[i];
            for (int j = 0; j < poly->vertCount; ++j)
            {
                const float* vertex = &VertsPoints[poly->verts[j] * 3];
                float rcDist = dtVdist2D(entry.data(), vertex);
                if (rcDist <= Entry.radius)
                {
                    poly->setArea(55);
                }
            }
        }


       /* if (IsTileInBlacklistArea(tile, entry, Entry.radius))
        {
            const float* VertsPoints = &tile->verts[0]; 
            for (int i = 0; i < tile->header->polyCount; ++i) 
            {
                dtPoly* poly = &tile->polys[i];
                for (int j = 0; j < poly->vertCount; ++j) 
                {
                    const float* vertex = &VertsPoints[poly->verts[j] * 3]; 
                    float rcDist = dtVdist2D(entry.data(), vertex);
                    if (rcDist <= Entry.radius) 
                    {
                        poly->setArea(55);
                    }
                }
            }
        }*/
    }
    return dtQueryFilter::passFilter(polyRef, tile, poly);
}

bool NavivationFilter::IsTileInBlacklistArea(const dtMeshTile* tile, const std::array<float, 3> &blacklistPosition, float blacklistRadius)
{
    const float* tileVerts = &tile->verts[0];


    float tileMin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
    float tileMax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

    for (int i = 0; i < tile->header->vertCount; ++i)
    {
        const float* vertex = &tileVerts[i * 3];

        for (int j = 0; j < 3; ++j)
        {
            tileMin[j] = MY_MIN(tileMin[j], vertex[j]);
            tileMax[j] = MY_MAX(tileMax[j], vertex[j]);
        }
    }

    // Check if the bounding box of the tile intersects with the blacklisted area
    bool intersectX = !(blacklistPosition[0] + blacklistRadius < tileMin[0] || blacklistPosition[0] - blacklistRadius > tileMax[0]);
    bool intersectZ = !(blacklistPosition[2] + blacklistRadius < tileMin[2] || blacklistPosition[2] - blacklistRadius > tileMax[2]);

    return intersectX && intersectZ;
}