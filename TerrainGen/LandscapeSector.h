#ifndef LANDSCAPE_SECTOR_H
#define LANDSCAPE_SECTOR_H

#include <vector>
#include "opengl.h"
#include "Centered2DHeightMap.h"
#include "Graphic2DObject.h"

class LandscapeSector : 
	public Graphic2DObject
{
public:
	LandscapeSector(Scene* scene);

private:
	// Generated height map
	Centered2DHeightMap m_heightMap;
};

#endif //LANDSCAPE_SECTOR_H