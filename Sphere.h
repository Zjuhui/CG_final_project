#ifndef SPHERE_H
#define SPHERE_H

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cmath>
#include <glm.hpp>
#include <iostream>

using namespace std;

class Sphere_A {
public:
	Sphere_A(int precision);
	int GetNumVertices() { return mNumVertices; };
	int GetNumIndices() { return mNumIndices; };
	vector<int> GetIndices() { return mIndices; };
	vector<glm::vec2> GetTexCoords() { return mTexCoords; };
	vector<glm::vec3> GetVertices() { return mVertices; };
	vector<glm::vec3> GetNormals() { return mNormals; };
private:
	void init(int precision);
	float toRadians(float degrees);

	int mNumVertices;
	int mNumIndices;
	vector<int> mIndices;
	vector<glm::vec2> mTexCoords;
	vector<glm::vec3> mVertices;
	vector<glm::vec3> mNormals;
};

#endif