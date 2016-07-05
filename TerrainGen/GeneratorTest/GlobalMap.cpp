#include "GlobalMap.h"

GlobalMap::GlobalMap()
{
	m_sectors = new std::map<std::pair<int, int>, HeightMapSector*>();
}

void GlobalMap::changeCurrentSector(int x, int y)
{
	m_currentSectorX = x;
	m_currentSectorY = y;
	std::map<std::pair<int, int>, HeightMapSector*>* newSectors = new std::map<std::pair<int, int>, HeightMapSector*>();
	for (int j = -HALF_WIDTH_IN_SECTORS; j <= HALF_WIDTH_IN_SECTORS; j++) {
		for (int i = -HALF_WIDTH_IN_SECTORS; i <= HALF_WIDTH_IN_SECTORS; i++) {
			std::pair<int, int> coords(x + i, y + j); 
			if (!m_sectors->count(coords)) {
				newSectors->operator[](coords) = new HeightMapSector(x + i, y + j);
			} else {
				newSectors->operator[](coords) = m_sectors->operator[](coords);
				m_sectors->erase(coords); 
			}
		}
	}
	for (auto i = m_sectors->begin(); i != m_sectors->end(); i++) {
		delete(i->second);
	}
	delete(m_sectors);
	m_sectors = newSectors;
}