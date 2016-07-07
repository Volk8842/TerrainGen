#include "LandscapeSector.h"

LandscapeSector::LandscapeSector(SectorCoords coords, Centered2DHeightMap* heightMap) :
	m_coords(coords),
	m_heightMap(heightMap)
{
}

LandscapeSector::~LandscapeSector()
{
	delete(m_heightMap);
}

Centered2DHeightMap* LandscapeSector::heightMap()
{
	return m_heightMap;
}
