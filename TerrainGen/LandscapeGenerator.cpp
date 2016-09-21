#include "LandscapeGenerator.h"

CenteredHeightMap* LandscapeGenerator::createHeightMap(int detailRate) {
	int sectorWidth = 1;
	for (int i = 0; i < detailRate; i++) sectorWidth *= 2;
	int sectorHalfWidth = sectorWidth / 2;
	sectorWidth++;
	int sectorSize = sectorWidth * sectorWidth;
	int generatorWidth = 2 * sectorWidth - 1;
	int generatorSize = generatorWidth * generatorWidth;
	
	CenteredHeightMap generator(generatorSize);
	// Set corners of generated sector
	generator.setVertex(-sectorHalfWidth, -sectorHalfWidth, (rand() % 100) / 100.0);
	generator.setVertex(sectorHalfWidth, -sectorHalfWidth, (rand() % 100) / 100.0);
	generator.setVertex(-sectorHalfWidth, sectorHalfWidth, (rand() % 100) / 100.0);
	generator.setVertex(sectorHalfWidth, sectorHalfWidth, (rand() % 100) / 100.0);
	// Load data from other sectors
	// TODO: --||--
	useSquareDiamondAlgorithm(generator, sectorWidth);
	// Create sector with generated data
	CenteredHeightMap* newHeightMap = new CenteredHeightMap(sectorSize);
	for (int j = -sectorHalfWidth; j <= sectorHalfWidth; j++) {
		for (int i = -sectorHalfWidth; i <= sectorHalfWidth; i++) {
			newHeightMap->setVertex(i, j, generator.vertex(i, j));
		}
	}
	return newHeightMap;
}

void LandscapeGenerator::useSquareDiamondAlgorithm(CenteredHeightMap& generator, int sectorWidth) {
	int side = sectorWidth;
	int sectorHalfWidth = (sectorWidth - 1) / 2;
	int x = 0;
	int y = 0;
	int xFirst = 0;
	int yFirst = 0;
	do {
		y = yFirst;
		do {
			x = xFirst;
			do {
				useSquareStep(generator, x, y, side, sectorWidth);
				x += side - 1;
			} while (x < sectorHalfWidth);
			y += side - 1;
		} while (y < sectorHalfWidth);
		y = yFirst;
		do {
			x = xFirst;
			do {
				useDiamondStep(generator, x, y - (side - 1) / 2, side, sectorWidth);
				useDiamondStep(generator, x, y + (side - 1) / 2, side, sectorWidth);
				useDiamondStep(generator, x - (side - 1) / 2, y, side, sectorWidth);
				useDiamondStep(generator, x + (side - 1) / 2, y, side, sectorWidth);
				x += side - 1;
			} while (x < sectorHalfWidth);
			y += side - 1;
		} while (y < sectorHalfWidth);
		side = (side - 1) / 2 + 1;
		xFirst = yFirst = -sectorHalfWidth + (side - 1) / 2;
	} while (side >= 3);
}

void LandscapeGenerator::useSquareStep(CenteredHeightMap& generator, int x, int y, int side, int sectorWidth) {
	if (generator.vertex(x, y) != UNDEFINED_HEIGHT_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	GLfloat value = (generator.vertex(x - offset, y - offset) +
		generator.vertex(x + offset, y - offset) +
		generator.vertex(x - offset, y + offset) +
		generator.vertex(x + offset, y + offset)) / 4;
	generator.setVertex(x, y, addVertexDisplacement(value, side, sectorWidth));
}

void LandscapeGenerator::useDiamondStep(CenteredHeightMap& generator, int x, int y, int side, int sectorWidth) {
	if (generator.vertex(x, y) != UNDEFINED_HEIGHT_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	GLfloat value;
	if (generator.vertex(x - offset, y) < 0 || generator.vertex(x + offset, y) < 0 ||
		generator.vertex(x, y - offset) < 0 || generator.vertex(x, y + offset) < 0) {
		value = (generator.vertex(x - offset, y) +
			generator.vertex(x + offset, y) +
			generator.vertex(x, y - offset) +
			generator.vertex(x, y + offset) + 1) / 3;
	}
	else {
		value = (generator.vertex(x - offset, y) +
			generator.vertex(x + offset, y) +
			generator.vertex(x, y - offset) +
			generator.vertex(x, y + offset)) / 4;
	}
	generator.setVertex(x, y, addVertexDisplacement(value, side, sectorWidth));
}

GLfloat LandscapeGenerator::addVertexDisplacement(GLfloat value, int side, int sectorWidth) {
	GLfloat length = (side * 1.0f) / sectorWidth;
	GLfloat roughness = 0.8f;
	GLfloat topD = length * roughness / 2.0f;
	GLfloat botD = length * roughness / 2.0f;
	if (value + topD > 1.0f) {
		topD = 1.0f - value;
		return 1.0f - (rand() % (int)((topD + botD) * 10000)) / 10000.0f;
	}
	else if (value - botD < 0.0f) {
		botD = value;
		return (rand() % (int)((topD + botD) * 10000)) / 10000.0f;
	}
	else
		return value + (rand() % (int)((topD + botD) * 10000)) / 10000.0f - (topD + botD) / 2.0;
}

void LandscapeGenerator::useThermalErrosion(CenteredHeightMap& heightMap, float dTalus) {
	int width = heightMap.sideWidth();
	for (int y = -heightMap.halfSideWidth(); y <= heightMap.halfSideWidth(); y++) {
		for (int x = -heightMap.halfSideWidth(); x <= heightMap.halfSideWidth(); x++) {
			for (int j = -1; j <= 1; j += 2) {
				if (y + j >= -heightMap.halfSideWidth() && y + j <= heightMap.halfSideWidth()) {
					for (int i = -1; i <= 1; i += 2) {
						if (x + i >= -heightMap.halfSideWidth() && x + i <= heightMap.halfSideWidth()) {
							float dHeight = heightMap.vertex(x, y) - heightMap.vertex(x + i, y + j);
							if (dHeight > dTalus) {
								float d = (dHeight - dTalus) / 2.0f;
								float o1 = heightMap.vertex(x, y);
								float o2 = heightMap.vertex(x + i, y + j);
								heightMap.setVertex(x, y, heightMap.vertex(x, y) - d);
								heightMap.setVertex(x + i, y + j, heightMap.vertex(x + i, y + j) + d);
								o1 = heightMap.vertex(x, y);
								o2 = heightMap.vertex(x + i, y + j);
								bool tr = true;
							}
						}
					}
				}
			}
		}
	}
}


std::vector<GLfloat>* LandscapeGenerator::generateVertices(CenteredHeightMap& heightMap) {
	int heightMapSize = heightMap.sideWidth() * heightMap.sideWidth();
	std::vector<GLfloat>* vertices = new std::vector<GLfloat>(heightMapSize * 3);
	int i = -heightMap.halfSideWidth();
	int j = -heightMap.halfSideWidth();
	GLfloat x = -1.0f;
	GLfloat z = -1.0f;
	GLfloat step = 2.0f / heightMap.sideWidth();
	for (auto it = vertices->begin(); it != vertices->end(); it += 3) {
		*it = x;
		*(it + 1) = heightMap.vertex(i, j);
		*(it + 2) = z;

		if (i < heightMap.halfSideWidth()) {
			i++;
			x += step;
		}
		else {
			i = -heightMap.halfSideWidth();
			j++;
			x = -1.0f;
			z += step;
		}
	}
	return vertices;
}

std::vector<GLuint>* LandscapeGenerator::generateIndices(CenteredHeightMap& heightMap) {
	int heightMapSize = heightMap.sideWidth() * heightMap.sideWidth();
	std::vector<GLuint>* indices = new std::vector<GLuint>(heightMapSize * 6);
	int it = 0;
	for (int j = 0; j < heightMap.sideWidth() - 1; j++) {
		for (int i = 0; i < heightMap.sideWidth() - 1; i++) {
			int x = heightMap.sideWidth() * j + i;
			indices->operator[](it) = x;
			indices->operator[](it + 1) = x + 1;
			indices->operator[](it + 2) = x + heightMap.sideWidth();
			indices->operator[](it + 3) = x + 1;
			indices->operator[](it + 4) = x + heightMap.sideWidth() + 1;
			indices->operator[](it + 5) = x + heightMap.sideWidth();
			it += 6;
		}
	}
	return indices;
}

Graphic2DObject* LandscapeGenerator::createGraphicRepresentation(CenteredHeightMap& heightMap) {
	std::vector<GLfloat>* vertices = generateVertices(heightMap);
	std::vector<GLuint>* indices = generateIndices(heightMap);
	Graphic2DObject* result = new Graphic2DObject(vertices, indices);
	return result;
}