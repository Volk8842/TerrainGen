#include <fstream>

#include "HeightMapSectorBase.h"

const std::string HeightMapSectorBase::MAP_SECTOR_PREFIX = "Maps/map_";
const std::string HeightMapSectorBase::MAP_SECTOR_POSTFIX = ".mf";

HeightMapSectorBase::HeightMapSectorBase(int mapX, int mapY) :
	m_mapX(mapX),
	m_mapY(mapY)
{
}

HeightMapSectorBase::~HeightMapSectorBase()
{
	if (m_array != nullptr)
		delete(m_array);
}

int HeightMapSectorBase::element(int x, int y) const
{
	return m_array->operator[](m_sideWidth * (y + m_halfSideWidth) + (x + m_halfSideWidth));
}

int HeightMapSectorBase::element(int x, int y, std::shared_ptr<std::vector<int>> array)
{
	int sideWidth = sqrt(array->size());
	return array->operator[](sideWidth * (y + (sideWidth - 1) / 2) + (x + (sideWidth - 1) / 2));
}

void HeightMapSectorBase::setElement(int x, int y, int value)
{
	m_array->operator[](m_sideWidth * (y + m_halfSideWidth) + (x + m_halfSideWidth)) = value;
}

std::string HeightMapSectorBase::getSectorFileName(int mapX, int mapY)
{
	return MAP_SECTOR_PREFIX + std::to_string(mapX) + "_" + std::to_string(mapY) + MAP_SECTOR_POSTFIX;
}

std::shared_ptr<std::vector<int>> HeightMapSectorBase::loadSector(int mapX, int mapY)
{
	std::string fileName = getSectorFileName(mapX, mapY);
	std::ifstream file;
	file.open(fileName, std::ios::binary);
	if (!file.is_open())
		return nullptr;
	int arraySize = SECTOR_SIDE_WIDTH * SECTOR_SIDE_WIDTH;
	auto data = std::make_shared<std::vector<int>> (arraySize, UNDEFINED_VALUE);
	int buffer;
	for (int i = 0; i < arraySize; i++) {
		file.read((char*)&buffer, sizeof(buffer));
		data->operator[](i) = buffer;
	}
	file.close();
	return data;
}

bool HeightMapSectorBase::loadSector()
{
	auto data = loadSector(m_mapX, m_mapY);
	if (data == nullptr)
		return false;
	for (int i = 0; i < m_arraySize; i++) {
		m_array->operator[](i) = data->operator[](i);
	}
	return true;
}
