#ifndef HEIGHT_MAP_SECTOR_GENERATOR_H
#define HEIGHT_MAP_SECTOR_GENERATOR_H

#include "HeightMapSectorBase.h"

class HeightMapSectorGenerator : public HeightMapSectorBase
{
public:
	HeightMapSectorGenerator(int mapX, int mapY);

	std::vector<int> generate();

private:
	void useSquareDiamondAlgorithm(); 
	void useSquareStep(int x, int y, int stepSideWidth);
	void useDiamondStep(int x, int y, int stepSideWidth);
	int averageHeight(int mapX, int mapY);

	void loadExistingPoints();

	static const int MIN_AVERAGE_HEIGHT = 10;
    static const int MAX_AVERAGE_HEIGHT = 99;

};

#endif //HEIGHT_MAP_SECTOR_GENERATOR_H
