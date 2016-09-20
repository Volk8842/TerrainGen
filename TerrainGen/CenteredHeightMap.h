#ifndef CENTERED_HEIGHT_MAP_H
#define CENTERED_HEIGHT_MAP_H

#include <vector>
#include <opengl.h>

const float UNDEFINED_HEIGHT_VALUE = -1.0f;

class CenteredHeightMap {
public:
	CenteredHeightMap(int size);
	~CenteredHeightMap();
	void setVertex(int x, int y, GLfloat value);
	GLfloat vertex(int x, int y);
	int sideWidth();
	int halfSideWidth();

private:
	std::vector<GLfloat>* m_vector;
	int m_sideWidth;
	int m_halfSideWidth;
};

#endif //CENTERED_HEIGHT_MAP_H
