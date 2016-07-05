#ifndef HEIGHT_MAP_SECTOR_BASE_H
#define HEIGHT_MAP_SECTOR_BASE_H

#include <vector>
#include <string>
#include <memory>

class HeightMapSectorBase
{
public:
	static const int UNDEFINED_VALUE = -1;
	static const int SECTOR_SIDE_WIDTH = 65;
	static const std::string MAP_SECTOR_PREFIX;
	static const std::string MAP_SECTOR_POSTFIX;

	HeightMapSectorBase(int mapX, int mapY);
	virtual ~HeightMapSectorBase();

	int element(int x, int y) const;
	static int element(int x, int y, std::shared_ptr<std::vector<int>> m_array);
	void setElement(int x, int y, int value);


protected:
	static std::string getSectorFileName(int mapX, int mapY);
	static std::shared_ptr<std::vector<int>> loadSector(int mapX, int mapY);
	bool loadSector();

	int m_mapX;
	int m_mapY;
	int m_arraySize;
	int m_sideWidth;
	int m_halfSideWidth;
	std::vector<int>* m_array;
};

#endif //HEIGHT_MAP_SECTOR_BASE_H
