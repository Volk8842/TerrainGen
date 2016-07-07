#include "Centered2DHeightMap.h"
#include "Landscape.h"

Centered2DHeightMap::Centered2DHeightMap(int size)
{
	m_vector = new std::vector<GLfloat>(size);
	for (auto i = m_vector->begin(); i != m_vector->end(); i++) {
		*i = UNDEFINED_VALUE;
	}
}

Centered2DHeightMap::~Centered2DHeightMap()
{
	delete(m_vector);
}

void Centered2DHeightMap::setVertex(int x, int y, GLfloat value)
{
	m_vector->operator[]((SECTOR_SIDE_WIDTH * (y + SECTOR_HALF_SIDE_WIDTH)) + (x + SECTOR_HALF_SIDE_WIDTH)) = value;
}

GLfloat Centered2DHeightMap::vertex(int x, int y)
{
	return m_vector->operator[]((SECTOR_SIDE_WIDTH * (y + SECTOR_HALF_SIDE_WIDTH)) + (x + SECTOR_HALF_SIDE_WIDTH));
}
