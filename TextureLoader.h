
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <iostream>
//#include <GL/glew.h>

using namespace std;

GLuint loadTexture_a(const char* texImagePath)
{
    GLuint textureRef;
    textureRef = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureRef == 0) cout << "didnt find texture file " << texImagePath << endl;
    // ----- mipmap/anisotropic section
    glBindTexture(GL_TEXTURE_2D, textureRef);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    //if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
    //    GLfloat anisoset = 0.0f;
    //    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
    //    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
   // }

    // ----- end of mipmap/anisotropic section
    return textureRef;
}

#endif


