#ifndef LANDSCAPE_SECTOR_H
#define LANDSCAPE_SECTOR_H

#include <vector>
#include "opengl.h"
#include "Centered2DHeightMap.h"

class LandscapeSector
{


private:
	// Generated height map
	Centered2DHeightMap m_heightMap;

	// Data for visualization
	std::vector<GLfloat>* m_vertices;
	std::vector<GLuint>* m_indices;
};

#endif //LANDSCAPE_SECTOR_H