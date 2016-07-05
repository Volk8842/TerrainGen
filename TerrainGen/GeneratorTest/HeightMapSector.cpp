#include <fstream>

#include "HeightMapSector.h"
#include "HeightMapSectorGenerator.h"

HeightMapSector::HeightMapSector(int mapX, int mapY) :
	HeightMapSectorBase(mapX, mapY)
{
	m_sideWidth = SECTOR_SIDE_WIDTH;
	m_arraySize = m_sideWidth * m_sideWidth;
	m_halfSideWidth = (m_sideWidth - 1) / 2;
	m_array = new std::vector<int>(m_arraySize, UNDEFINED_VALUE);
	fillArrayWithData();
}

void HeightMapSector::saveSector()
{
	std::string fileName = getSectorFileName(m_mapX, m_mapY);
	std::ofstream file;
	file.open(fileName, std::ios::binary);
	if (!file.is_open())
		return;
	for (int i = 0; i < m_arraySize; i++) {
		int buffer = m_array->operator[](i);
		file.write((char*)&buffer, sizeof(buffer));
	}
	file.close();
}
	
void HeightMapSector::fillArrayWithData()
{
	if (!loadSector()) {
		generate();
		saveSector();
	}
}

void HeightMapSector::generate()
{
	HeightMapSectorGenerator generator(m_mapX, m_mapY);
	std::vector<int> data = generator.generate();
	for (int i = 0; i < m_arraySize; i++) {
		m_array->operator[](i) = data[i];
	}
}
