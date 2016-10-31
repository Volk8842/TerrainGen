#include "SphereGenerator.h"

const double pi = std::acos(-1);

struct SphereVertex {
	
	GLfloat x;
	GLfloat y;
	GLfloat z;

	SphereVertex(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct SphereTriangle {

	GLuint a;
	GLuint b;
	GLuint c;

	SphereTriangle(GLuint a, GLuint b, GLuint c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

Graphic2DObject* SphereGenerator::createGraphicRepresentation() {

	std::vector<SphereVertex*>* massVertices = new std::vector<SphereVertex*>();

	std::vector<int> vertexCount = {1, 5, 10, 10, 10, 5, 1};
	double dAlpha = pi / (vertexCount.size() - 1);
	int isOdd = 1;

	for (int i = 0; i < vertexCount.size(); i++) {
		double alpha = pi / 2 - dAlpha * i;
		double dBetta = vertexCount[i] > 1 ? pi * 2 / vertexCount[i] : 0;
		for (int j = 0; j < vertexCount[i]; j++) {
			massVertices->push_back(new SphereVertex(cos(alpha) * sin(dBetta * (j + (isOdd * 0.5))), sin(alpha), cos(alpha) * cos(dBetta * (j + (isOdd * 0.5)))));
		}
		isOdd = isOdd == 1 ? 0 : 1;
	}

	std::vector<SphereTriangle*>* massIndices = new std::vector<SphereTriangle*>();

	int vertexId = vertexCount[0];
	for (int i = 1; i < vertexCount.size(); i++) {
		int j = 0;
		for (; j < vertexCount[i] - 1; j++) {
			massIndices->push_back(new SphereTriangle(vertexId + j, vertexId + j + 1, 0));
		}
		massIndices->push_back(new SphereTriangle(vertexId + j, vertexId, 0));
		vertexId += vertexCount[i];
	}

	std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();

	for (int i = 0; i < massVertices->size(); i++) {
		vertices->push_back(massVertices->at(i)->x);
		vertices->push_back(massVertices->at(i)->y);
		vertices->push_back(massVertices->at(i)->z);
	}

	for (int i = 0; i < massIndices->size(); i++) {
		indices->push_back(massIndices->at(i)->a);
		indices->push_back(massIndices->at(i)->b);
		indices->push_back(massIndices->at(i)->c);
	}

	Graphic2DObject* result = new Graphic2DObject(vertices, indices);
	return result;
}