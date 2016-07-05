#ifndef SCENE_H
#define SCENE_H

#include "Landscape.h"

class Scene
{
public:
	void draw();

private:
	void drawLandscape();

	Landscape m_landscape;
};

#endif //SCENE_H