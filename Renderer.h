#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "shaders.h"
#include "defineList.h"
#include "Player.h"
#include "Floor.h"
#include "GameLogic.h"
#include "Shadow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include "stb_image.h"
#include "SkyBox.h"


void ShaderInit();
bool getTextureID(unsigned int& ID, char* s);
bool getTextureID_a(unsigned int& ID, const char* s);
void renderSkybox();
void renderFloor();
void renderBullet(Bullet* bullet, float time);
void renderPlayer(Player* player, float time);
void renderParticle(Particle* particle, float time);
//void renderShadowDepth(vector<Player*> playerList, vector<Bullet*> bulletList);
//void renderShadowDepth(vector<Player*> playerList, vector<Bullet*> bulletList);
//void renderBullet(Bullet* bullet, float time);
void renderShadowDepth(vector<Player*> playerList, vector<Bullet*> bulletList);


void renderWater();
void WaterRenderInit();

void floorRender();
void wallRender();
void renderScene(Shader wallShader,  float clipPlane[4]); 

//void renderWater();

//void renderWall();


#endif