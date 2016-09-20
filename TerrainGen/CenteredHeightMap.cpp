#include <CenteredHeightMap.h>

CenteredHeightMap::CenteredHeightMap(int size) {
	m_sideWidth = sqrt(size);
	m_halfSideWidth = (m_sideWidth - 1) / 2;
	m_vector = new std::vector<GLfloat>(size);
	for (auto i = m_vector->begin(); i != m_vector->end(); i++) {
		*i = UNDEFINED_HEIGHT_VALUE;
	}
}

CenteredHeightMap::~CenteredHeightMap() {
	delete(m_vector);
}

void CenteredHeightMap::setVertex(int x, int y, GLfloat value) {
	m_vector->operator[]((m_sideWidth * (y + m_halfSideWidth)) + (x + m_halfSideWidth)) = value;
}

GLfloat CenteredHeightMap::vertex(int x, int y) {
	return m_vector->operator[]((m_sideWidth * (y + m_halfSideWidth)) + (x + m_halfSideWidth));
}

int CenteredHeightMap::sideWidth() {
	return m_sideWidth;
}

int CenteredHeightMap::halfSideWidth() {
	return m_halfSideWidth;
}