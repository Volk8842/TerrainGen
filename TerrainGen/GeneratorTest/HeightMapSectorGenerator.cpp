#include "HeightMapSectorGenerator.h"

#include <iostream>

HeightMapSectorGenerator::HeightMapSectorGenerator(int mapX, int mapY) :
	HeightMapSectorBase(mapX, mapY)
{
	m_sideWidth = (2 * SECTOR_SIDE_WIDTH - 1);
	m_arraySize = m_sideWidth * m_sideWidth;
	m_halfSideWidth = (m_sideWidth - 1) / 2;
	m_array = new std::vector<int>(m_arraySize, UNDEFINED_VALUE);
}

void HeightMapSectorGenerator::useSquareDiamondAlgorithm() 
{
	int side = SECTOR_SIDE_WIDTH;
	int halfSide = (SECTOR_SIDE_WIDTH - 1) / 2;
	int x = 0;
	int y = 0;
	int xFirst = 0;
	int yFirst = 0;
	do {	
		y = yFirst;
		do {
			x = xFirst;
			do {
				useSquareStep(x, y, side);
				x += side - 1;
			} while (x < halfSide);
			y += side - 1;
		} while (y < halfSide);
		y = yFirst;
		do {
			x = xFirst;
			do {
				useDiamondStep(x, y - (side - 1) / 2, side);
				useDiamondStep(x, y + (side - 1) / 2, side);
				useDiamondStep(x - (side - 1) / 2, y, side);
				useDiamondStep(x + (side - 1) / 2, y, side);
				x += side - 1;
			} while (x < halfSide);
			y += side - 1;
		} while (y < halfSide);
		side = (side - 1) / 2 + 1;
		xFirst = yFirst = -halfSide + (side - 1) / 2;
	} while (side >= 3);
}

void HeightMapSectorGenerator::useSquareStep(int x, int y, int side)
{
	if (element(x, y) != UNDEFINED_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	setElement(x, y, (element(x - offset, y - offset) + element(x + offset, y - offset) +
					  element(x - offset, y + offset) + element(x + offset, y + offset)) / 4);
}

void HeightMapSectorGenerator::useDiamondStep(int x, int y, int side)
{
	if (element(x, y) != UNDEFINED_VALUE)
		return;
	int offset = (side - 1) / 2.0;
	if (element(x - offset, y) < 0 || element(x + offset, y) < 0 ||
		element(x, y - offset) < 0 || element(x, y + offset) < 0) {
		setElement(x, y, (element(x - offset, y) + element(x + offset, y) +
						  element(x, y - offset) + element(x, y + offset) + 1) / 3);
	} else {
		setElement(x, y, (element(x - offset, y) + element(x + offset, y) +
						  element(x, y - offset) + element(x, y + offset)) / 4);
	}
}

int HeightMapSectorGenerator::averageHeight(int posX, int posY)
{
	// TODO: get height from global map
	// int height = UNDEFINED_VALUE;
	//if (m_globalHeightMap != nullptr && (height = m_globalHeightMap->averageHeight(posX, posY)) != UNDEFINED)
	//	return height;
	return (rand() % (MAX_AVERAGE_HEIGHT - MIN_AVERAGE_HEIGHT)) + MIN_AVERAGE_HEIGHT; 
}

void HeightMapSectorGenerator::loadExistingPoints()
{
	int sectorHalfSideWidth = (SECTOR_SIDE_WIDTH - 1) / 2;
	setElement(-sectorHalfSideWidth, -sectorHalfSideWidth, averageHeight(m_mapX, m_mapY));
	setElement(sectorHalfSideWidth, -sectorHalfSideWidth, averageHeight(m_mapX + 1, m_mapY));
	setElement(-sectorHalfSideWidth, sectorHalfSideWidth, averageHeight(m_mapX, m_mapY + 1));
	setElement(sectorHalfSideWidth, sectorHalfSideWidth, averageHeight(m_mapX + 1, m_mapY + 1));
	int genStartY = -m_halfSideWidth;
	for (int j = -1; j < 2; j++) {
		int genStartX = -m_halfSideWidth;
		for (int i = -1; i < 2; i++) {
			auto loadedSector = loadSector(m_mapX + i, m_mapY + j);
			if (loadedSector != nullptr) {
				int sectorStartX = (i == -1 ? 0 : -sectorHalfSideWidth);
				int sectorEndX = (i == 1 ? 0 : sectorHalfSideWidth);
				int sectorStartY = (j == -1 ? 0 : -sectorHalfSideWidth);
				int sectorEndY = (j == 1 ? 0 : sectorHalfSideWidth);
				int genY = genStartY;
				for (int sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
					int genX = genStartX;
					for (int sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
						setElement(genX, genY, element(sectorX, sectorY, loadedSector));
						genX++;	
					}	
					genY++;
				}
			}
			genStartX += (i == -1 ? (sectorHalfSideWidth) : (SECTOR_SIDE_WIDTH - 1));	
		}
		genStartY += (j == -1 ? (sectorHalfSideWidth) : (SECTOR_SIDE_WIDTH - 1));
	}
}

std::vector<int> HeightMapSectorGenerator::generate()
{
	loadExistingPoints();
	useSquareDiamondAlgorithm();

	int sectorHalfSideWidth = (SECTOR_SIDE_WIDTH - 1) / 2;
	std::vector<int> data(SECTOR_SIDE_WIDTH * SECTOR_SIDE_WIDTH, UNDEFINED_VALUE);
	int k = 0;
	for (int j = -sectorHalfSideWidth; j <= sectorHalfSideWidth; j++) {
		for (int i = -sectorHalfSideWidth; i <= sectorHalfSideWidth; i++) {
			data[k] = element(i, j);
			k++;
		}
	}
	return data;
}