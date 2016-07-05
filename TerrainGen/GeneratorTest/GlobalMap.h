#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include "HeightMapSector.h"

#include <map>

class GlobalMap
{
public:
	GlobalMap();
	void changeCurrentSector(int x, int y);

private:
	static const int HALF_WIDTH_IN_SECTORS = 2;

	int m_currentSectorX;
	int m_currentSectorY;
	std::map<std::pair<int, int>, HeightMapSector*>* m_sectors;
};

#endif //GLOBAL_MAP_H