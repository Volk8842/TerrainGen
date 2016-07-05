#ifndef HEIGHT_MAP_SECTOR_H
#define HEIGHT_MAP_SECTOR_H

#include "HeightMapSectorBase.h"

class HeightMapSector : public HeightMapSectorBase
{
public:
	HeightMapSector(int mapX, int mapY);

private:
	void saveSector();
	void fillArrayWithData();
	void generate();
};

#endif //HEIGHT_MAP_SECTOR_H