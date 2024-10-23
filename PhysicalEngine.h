#pragma once
#ifndef PHYSICAL_ENGINE_H
#define PHYSICAL_ENGINE_H

#include <glad.h>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <vector>
#include <iostream>

using namespace std;

class object {
public:
	glm::vec3 getPos();
	glm::vec3 getColor();
	unsigned int getID();
	bool isAlive() const;

protected:
	glm::vec3 position;
	glm::vec3 color;
	unsigned int id, teamid;
	float speed;
	float g;   //gravity
	bool alive = true;


};

class Cube : public object {
public:
	float rotateAngle() const;
	float getHalfLength() const;
	float getFateY() const;

protected:
	float yaw = 0.0f, pitch = 30.0f, zoom = 50.f, halfLength = 1.0f, fateY = 1.0f;
	glm::vec3 V = glm::vec3(0.0f, 0.0f, 0.0f);	
};

class Sphere : public object {
public:
	float getRadius() const;

protected:
	float radius = 0.1f;
};

class PhysicalEngine {
public:
	static glm::vec3 rotate(glm::vec3 pos, glm::vec3 rotatePoint, float angle);
	static bool inBox(glm::vec3 pos, glm::vec3 boxPoint, float halfLength, float fateY, float angle, float r);
	static bool intersect(Cube a, Cube b);
	static bool intersect(Cube a, Sphere b);
	static bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 boxPoint, float halfLength);
};



#endif
