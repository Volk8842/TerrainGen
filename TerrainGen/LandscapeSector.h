#ifndef LANDSCAPE_SECTOR_H
#define LANDSCAPE_SECTOR_H

#include <vector>
#include "opengl.h"

class LandscapeSector
{


private:
	void fill();

	int m_sectorSideWidth;

	std::vector<GLfloat>* vertices;
	std::vector<GLuint>* indices;
};

#endif //LANDSCAPE_SECTOR_H