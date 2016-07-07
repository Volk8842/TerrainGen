#include "Landscape.h"

GLfloat Landscape::getCornerHeight(SectorCoords coords)
{
	// TODO: impl needed
	srand(coords.x * coords.y + coords.x + coords.y);
	return (rand() % 10000) / 10000;
}

void Landscape::useSquareDiamondAlgorithm(Centered2DHeightMap& generator)
{
	int side = SECTOR_SIDE_WIDTH;
	int halfSide = (SECTOR_SIDE_WIDTH - 1) / 2;
	int x = 0;
	int y = 0;
	int xFirst = 0;
	int yFirst = 0;
	do {
		y = yFirst;
		do {
			x = xFirst;
			do {
				useSquareStep(x, y, side, generator);
				x += side - 1;
			} while (x < halfSide);
			y += side - 1;
		} while (y < halfSide);
		y = yFirst;
		do {
			x = xFirst;
			do {
				useDiamondStep(x, y - (side - 1) / 2, side, generator);
				useDiamondStep(x, y + (side - 1) / 2, side, generator);
				useDiamondStep(x - (side - 1) / 2, y, side, generator);
				useDiamondStep(x + (side - 1) / 2, y, side, generator);
				x += side - 1;
			} while (x < halfSide);
			y += side - 1;
		} while (y < halfSide);
		side = (side - 1) / 2 + 1;
		xFirst = yFirst = -halfSide + (side - 1) / 2;
	} while (side >= 3);
}

void Landscape::useSquareStep(int x, int y, int side, Centered2DHeightMap& generator)
{
	if (generator.vertex(x, y) != UNDEFINED_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	generator.setVertex(x, y, (generator.vertex(x - offset, y - offset) + 
							   generator.vertex(x + offset, y - offset) +
		                       generator.vertex(x - offset, y + offset) + 
							   generator.vertex(x + offset, y + offset)) / 4);
}

void Landscape::useDiamondStep(int x, int y, int side, Centered2DHeightMap& generator)
{
	if (generator.vertex(x, y) != UNDEFINED_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	if (generator.vertex(x - offset, y) < 0 || generator.vertex(x + offset, y) < 0 ||
		generator.vertex(x, y - offset) < 0 || generator.vertex(x, y + offset) < 0) {
		generator.setVertex(x, y, (generator.vertex(x - offset, y) + 
							       generator.vertex(x + offset, y) +
								   generator.vertex(x, y - offset) + 
								   generator.vertex(x, y + offset) + 1) / 3);
	} else {
		generator.setVertex(x, y, (generator.vertex(x - offset, y) + 
								   generator.vertex(x + offset, y) +
								   generator.vertex(x, y - offset) + 
								   generator.vertex(x, y + offset)) / 4);
	}
}

LandscapeSector* Landscape::generateSector(SectorCoords coords)
{
	Centered2DHeightMap generator(GENERATOR_SIZE);
	// Set corners of generated sector
	generator.setVertex(-SECTOR_HALF_SIDE_WIDTH, -SECTOR_HALF_SIDE_WIDTH, getCornerHeight(SectorCoords(coords.x, coords.y)));
	generator.setVertex(SECTOR_HALF_SIDE_WIDTH, -SECTOR_HALF_SIDE_WIDTH, getCornerHeight(SectorCoords(coords.x + 1, coords.y)));
	generator.setVertex(-SECTOR_HALF_SIDE_WIDTH, SECTOR_HALF_SIDE_WIDTH, getCornerHeight(SectorCoords(coords.x, coords.y + 1)));
	generator.setVertex(SECTOR_HALF_SIDE_WIDTH, SECTOR_HALF_SIDE_WIDTH, getCornerHeight(SectorCoords(coords.x + 1, coords.y + 1)));
	// Load data from other sectors
	// TODO: --||--
	useSquareDiamondAlgorithm(generator);
	// Create sector with generated data
	Centered2DHeightMap* newHeightMap = new Centered2DHeightMap(SECTOR_SIZE);
	for (int j = -SECTOR_HALF_SIDE_WIDTH; j <= SECTOR_HALF_SIDE_WIDTH; j++) {
		for (int i = -SECTOR_HALF_SIDE_WIDTH; i <= SECTOR_HALF_SIDE_WIDTH; i++) {
			newHeightMap->setVertex(i, j, generator.vertex(i, j));
		}
	}
	return new LandscapeSector(coords, newHeightMap);
}