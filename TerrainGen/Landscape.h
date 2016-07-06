#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <vector>
#include "LandscapeSector.h"

struct IntCoords
{
	IntCoords(int _x, int _y) : x(_x), y(_y) {};
	int x;
	int y;
};

class Landscape
{
public:
	IntCoords centralSectorCoords();

private:
	IntCoords m_centralSectorCoords;
	std::vector<LandscapeSector*>
};

#endif //LANDSCAPE_H