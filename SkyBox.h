#ifndef SKYBOX_H
#define SKYBOX_H


#include <glad/glad.h>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include "camera.h"

void skyBoxInit(string imgPath);
void drawSkyBox(glm::mat4 projection, Camera camera);
bool getSkyBoxID(unsigned int& ID, string path);

#endif
