#ifndef LANDSCAPE_GENERATOR_H
#define LANDSCAPE_GENERATOR_H

#include <vector>
#include <opengl.h>
#include <CenteredHeightMap.h>
#include <Graphic2DObject.h>

class LandscapeGenerator
{
public:
	static CenteredHeightMap* createHeightMap(int detailRate);
	static Graphic2DObject* createGraphicRepresentation(CenteredHeightMap& heightMap);

	static void useThermalErrosion(CenteredHeightMap& heightMap, float dTalus);

private:
	static void useSquareDiamondAlgorithm(CenteredHeightMap& generator, int sectorWidth);
	static void useSquareStep(CenteredHeightMap& generator, int x, int y, int side, int sectorWidth);
	static void useDiamondStep(CenteredHeightMap& generator, int x, int y, int side, int sectorWidth);
	static GLfloat addVertexDisplacement(GLfloat value, int side, int sectorWidth);

	static std::vector<GLfloat>* generateVertices(CenteredHeightMap& heightMap);
	static std::vector<GLuint>* generateIndices(CenteredHeightMap& heightMap);
};

#endif //LANDSCAPE_GENERATOR_H
