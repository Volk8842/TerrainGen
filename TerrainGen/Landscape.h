#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <map>
#include "LandscapeSector.h"

class Landscape
{

private:
	std::map<std::pair<int, int>, LandscapeSector*>* m_SectorsMap;
};

#endif //LANDSCAPE_H