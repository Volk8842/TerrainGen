#include "Centered2DHeightMap.h"

Centered2DHeightMap::Centered2DHeightMap()
{
	m_array = new std::array<GLfloat, SECTOR_SIZE>();
	for (auto i = m_array->begin(); i != m_array->end(); i++) {
		*i = UNDEFINED_VALUE;
	}
}

Centered2DHeightMap::~Centered2DHeightMap()
{
	delete(m_array);
}

void Centered2DHeightMap::setVertex(int x, int y, GLfloat value)
{
	m_array->operator[]((SECTOR_SIDE_WIDTH * (y + SECTOR_HALF_SIDE_WIDTH)) + (x + SECTOR_HALF_SIDE_WIDTH)) = value;
}

GLfloat Centered2DHeightMap::vertex(int x, int y)
{
	return m_array->operator[]((SECTOR_SIDE_WIDTH * (y + SECTOR_HALF_SIDE_WIDTH)) + (x + SECTOR_HALF_SIDE_WIDTH));
}
