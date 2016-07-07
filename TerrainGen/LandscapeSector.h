#ifndef LANDSCAPE_SECTOR_H
#define LANDSCAPE_SECTOR_H

#include <vector>
#include "opengl.h"
#include "Centered2DHeightMap.h"
#include "Landscape.h"

class LandscapeSector 
{
public:
	LandscapeSector(SectorCoords coords, Centered2DHeightMap* heightMap);
	~LandscapeSector();
private:
	SectorCoords m_coords;
	Centered2DHeightMap* m_heightMap;
};

#endif //LANDSCAPE_SECTOR_H