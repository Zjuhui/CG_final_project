#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm.hpp>
#include <matrix_transform.hpp>

#include "shaders.h"


#include <string>
#include <vector>

#include "stb_image.h"
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 position;
    // normal
    glm::vec3 normal;
    // texCoords
    glm::vec2 texCoord;

};

struct Texture {
    unsigned int id;
    string type;
    string path;// 储存纹理路径以防止重复加载
};

struct Material {
    vector<Texture> textures;
    int shininess;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    Material material;
    glm::vec3 center;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material material, glm::vec3 center);
    void draw(Shader shader, bool center, glm::vec3 scale);
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

#endif

