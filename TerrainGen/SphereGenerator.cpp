#include "SphereGenerator.h"

const double pi = std::acos(-1);

struct SphereVertex {
	
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat h;

	SphereVertex(double x, double y, double z, double h) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->h = h;
	}
};

Graphic2DObject* SphereGenerator::createGraphicRepresentation() {

	std::vector<SphereVertex*>* massVertices = new std::vector<SphereVertex*>();

	std::vector<int> vertexCount = {1, 5, 10, 10, 10, 5, 1};
	double dAlpha = pi / (vertexCount.size() - 1);

	for (int i = 0; i < vertexCount.size(); i++) {
		double alpha = pi / 2 - dAlpha * i;
		double dBetta = vertexCount[i] > 1 ? pi * 2 / vertexCount[i] : 0;
		bool isMid = i == 3 ? true : false;
		for (int j = 0; j < vertexCount[i]; j++) {
			massVertices->push_back(new SphereVertex(cos(alpha) * sin(dBetta * (j - 0.5 * isMid)), sin(alpha), cos(alpha) * cos(dBetta * (j - 0.5 * isMid)), 1.0f));
		}
	}

	std::vector<int> massIndices = {
		1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 1, 0,
		1, 2, 7, 2, 3, 9, 3, 4, 11, 4, 5, 13, 5, 1, 15,
		6, 7, 1, 7, 8, 2, 8, 9, 2, 9, 10, 3, 10, 11, 3,
		11, 12, 4, 12, 13, 4, 13, 14, 5, 14, 15, 5, 15, 6, 1,		
		6, 7, 17, 7, 8, 18, 8, 9, 19, 9, 10, 20, 10, 11, 21,
		11, 12, 22, 12, 13, 23, 13, 14, 24, 14, 15, 25, 15, 6, 16,		
		16, 17, 6, 17, 18, 7, 18, 19, 8, 19, 20, 9, 20, 21, 10,
		21, 22, 11, 22, 23, 12, 23, 24, 13, 24, 25, 14, 25, 16, 15,
		16, 17, 26, 17, 18, 27, 18, 19, 28, 19, 20, 29, 20, 21, 30,
		21, 22, 31, 22, 23, 32, 23, 24, 33, 24, 25, 34, 25, 16, 35,		
		26, 27, 17, 27, 28, 18, 28, 29, 19, 29, 30, 20, 30, 31, 21,
		31, 32, 22, 32, 33, 23, 33, 34, 24, 34, 35, 25, 35, 26, 16,		
		26, 27, 36, 27, 28, 37, 28, 29, 37, 29, 30, 38, 30, 31, 38,
		31, 32, 39, 32, 33, 39, 33, 34, 40, 34, 35, 40, 35, 26, 36,
		36, 37, 27, 37, 38, 29, 38, 39, 31, 39, 40, 33, 40, 36, 35,
		36, 37, 41, 37, 38, 41, 38, 39, 41, 39, 40, 41, 40, 36, 41
	};

	std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();

	for (int i = 0; i < massVertices->size(); i++) {
		vertices->push_back(massVertices->at(i)->x);
		vertices->push_back(massVertices->at(i)->y);
		vertices->push_back(massVertices->at(i)->z);
		vertices->push_back(massVertices->at(i)->h);
	}

	for (int i = 0; i < massIndices.size(); i+=3) {
		indices->push_back(massIndices[i]);
		indices->push_back(massIndices[i + 1]);
		indices->push_back(massIndices[i + 2]);
	}

	Graphic2DObject* result = new Graphic2DObject(vertices, indices);
	return result;
}