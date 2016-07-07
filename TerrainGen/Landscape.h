#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <vector>

#include "opengl.h"
#include "SectorCoords.h"
#include "LandscapeSector.h"
#include "Centered2DHeightMap.h"
#include "Graphic2DObject.h"

// because there is no const float shit
#define UNDEFINED_VALUE -1.0f

static const int SECTOR_SIDE_WIDTH = 9;
static const int SECTOR_HALF_SIDE_WIDTH = (SECTOR_SIDE_WIDTH - 1) / 2;
static const int SECTOR_SIZE = SECTOR_SIDE_WIDTH * SECTOR_SIDE_WIDTH;

static const int GENERATOR_SIDE_WIDTH = 2 * SECTOR_SIDE_WIDTH - 1;
static const int GENERATOR_HALF_SIDE_WIDTH = (GENERATOR_SIDE_WIDTH - 1) / 2;
static const int GENERATOR_SIZE = GENERATOR_SIDE_WIDTH * GENERATOR_SIDE_WIDTH;

class Landscape
{
public:
	Landscape();
	Graphic2DObject* createGraphicRepresentation();

private:
	// Generate sector
	void useSquareDiamondAlgorithm(Centered2DHeightMap& generator);
	void useSquareStep(int x, int y, int side, Centered2DHeightMap& generator);
	void useDiamondStep(int x, int y, int side, Centered2DHeightMap& generator);
	GLfloat getCornerHeight(SectorCoords coords);
	LandscapeSector* generateSector(SectorCoords coords);

	// Generate graphics
	std::vector<GLfloat>* generateVertices();
	std::vector<GLuint>* generateIndices();

	// TODO: not only one 
	LandscapeSector* m_map;
};

#endif //LANDSCAPE_H
