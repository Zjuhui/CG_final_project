#ifndef PLAYER_H
#define PLAYER_H
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <glad/glad.h>
#include <glm.hpp>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

void readOBJ(const char* filename, vector<float>& vertices, vector<unsigned int>& elements);
void playerRenderInit();
void drawPlayer();
void drawParticle();

//bullet
void bulletRenderInit();
void drawBullet();


#endif