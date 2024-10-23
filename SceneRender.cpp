#include "SceneRender.h"
#include "stb_image.h"
#include "Renderer.h"
#include "TextureLoader.h"

void WaterRenderInit();
void floorRender();
void wallRender();
void renderScene(Shader wallShader, float clipPlane[4]);
unsigned int initializeReflectionFBO();
unsigned int initializeRefractionFBO();

