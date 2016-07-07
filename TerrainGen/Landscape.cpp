#include "Landscape.h"

Landscape::Landscape()
{
	m_map = generateSector(SectorCoords(2, 3));
}

std::vector<GLfloat>* Landscape::generateVertices()
{
	std::vector<GLfloat>* vertices = new std::vector<GLfloat>(SECTOR_SIZE * 3);
	int i = -SECTOR_HALF_SIDE_WIDTH;
	int j = -SECTOR_HALF_SIDE_WIDTH;
	GLfloat x = -1.0f;
	GLfloat z = -1.0f;
	GLfloat step = 2.0f / SECTOR_SIDE_WIDTH;
	for (auto it = vertices->begin(); it != vertices->end(); it += 3) {
		*it = x;
		*(it + 1) = m_map->heightMap()->vertex(i, j);
		*(it + 2) = z;
		
		if (i < SECTOR_HALF_SIDE_WIDTH) {
			i++;
			x += step;
		} else {
			i = -SECTOR_HALF_SIDE_WIDTH;
			j++;
			x = -1.0f;
			z += step;
		}
	}
	return vertices;
}

std::vector<GLuint>* Landscape::generateIndices()
{
	std::vector<GLuint>* indices = new std::vector<GLuint>(SECTOR_SIZE * 6);
	int it = 0;
	for (int j = 0; j < SECTOR_SIDE_WIDTH; j++) {
		for (int i = 0; i < SECTOR_SIDE_WIDTH; i++) {
			int x = SECTOR_SIDE_WIDTH * j + i;
			indices->operator[](it) = x;
			indices->operator[](it + 1) = x + 1;
			indices->operator[](it + 2) = x + SECTOR_SIDE_WIDTH;
			indices->operator[](it + 3) = x + 1;
			indices->operator[](it + 4) = x + SECTOR_SIDE_WIDTH + 1;
			indices->operator[](it + 5) = x + SECTOR_SIDE_WIDTH;
			it += 6;
		}
	}
	return indices;
}

Graphic2DObject* Landscape::createGraphicRepresentation()
{
	std::vector<GLfloat>* vertices = generateVertices();
	std::vector<GLuint>* indices = generateIndices();

//	Graphic2DObject* newObject = Graphic2DObject
}

GLfloat Landscape::getCornerHeight(SectorCoords coords)
{
	// TODO: impl needed
	srand(coords.x * coords.y + coords.x + coords.y);
	return (rand() % 10000) / 10000;
}

void Landscape::useSquareDiamondAlgorithm(Centered2DHeightMap& generator)
{
	int side = SECTOR_SIDE_WIDTH;
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
			} while (x < SECTOR_HALF_SIDE_WIDTH);
			y += side - 1;
		} while (y < SECTOR_HALF_SIDE_WIDTH);
		y = yFirst;
		do {
			x = xFirst;
			do {
				useDiamondStep(x, y - (side - 1) / 2, side, generator);
				useDiamondStep(x, y + (side - 1) / 2, side, generator);
				useDiamondStep(x - (side - 1) / 2, y, side, generator);
				useDiamondStep(x + (side - 1) / 2, y, side, generator);
				x += side - 1;
			} while (x < SECTOR_HALF_SIDE_WIDTH);
			y += side - 1;
		} while (y < SECTOR_HALF_SIDE_WIDTH);
		side = (side - 1) / 2 + 1;
		xFirst = yFirst = -SECTOR_HALF_SIDE_WIDTH + (side - 1) / 2;
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