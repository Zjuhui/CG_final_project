#ifndef SCENE_RENDER_H
#define SCENE_RENDER_H

#include "shaders.h"

void WaterRenderInit();
void floorRender();
void wallRender();
void renderScene(Shader wallShader, float clipPlane[4]);
unsigned int initializeReflectionFBO();
unsigned int initializeRefractionFBO(); 


#endif
