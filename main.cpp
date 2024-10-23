#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
//#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
//#include "shaders.h"
//#include "shader_m.h"
#include "camera.h"
//#include "model.h"
#include <math.h>
#include "Sphere.h"
#include <iostream>
#include "ImportedModel.h"


#include "defineList.h"
#include "Renderer.h"
#include "GameWindow.h"
#include "GameLogic.h"
//#include "WaterShader.h"
//#include "Program.h"


//#include <Windows.h>
//#include <mmsystem.h>
//#pragma comment (lib, "winmm.lib")

GameWindow window;

#define PI = 3.1415926
float theta = 3.1415926 / 18000;


//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path);
unsigned int loadCubemap(vector<std::string> faces);
// lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

// camera
extern Camera camera;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;

//GLuint diffuseMap = loadTexture("C:\\Users\\75247\\Desktop\\learncg\\wall.jpg");

//const int winWidth = 1024, winHeight = 768;

//sun
Sphere_A sphere(48);
GLuint VAO, VBO[3];
//planets
Sphere_A sphere1(48);
GLuint VAO1, VBO1[3];

Sphere_A sphere2(48);
GLuint VAO2, VBO2[3];

Sphere_A sphere3(48);
GLuint VAO3, VBO3[3];

Sphere_A sphere4(48);
GLuint VAO4, VBO4[3];
//moon
Sphere_A sphere5(48);
GLuint VAO5, VBO5[3];



void setupModel(Sphere_A sphere, GLuint& VAO, GLuint* VBO) {
    auto sphereIndices = sphere.GetIndices();
    auto sphereVertices = sphere.GetVertices();
    auto sphereTexCoords = sphere.GetTexCoords();
    auto sphereNormals = sphere.GetNormals();

    vector<float> vertices, normals, texCoords;
    for (int i = 0; i < sphere.GetNumIndices(); i++) {
        vertices.push_back(sphereVertices[sphereIndices[i]].x);
        vertices.push_back(sphereVertices[sphereIndices[i]].y);
        vertices.push_back(sphereVertices[sphereIndices[i]].z);

        normals.push_back(sphereNormals[sphereIndices[i]].x);
        normals.push_back(sphereNormals[sphereIndices[i]].y);
        normals.push_back(sphereNormals[sphereIndices[i]].z);

        texCoords.push_back(sphereTexCoords[sphereIndices[i]].s);
        texCoords.push_back(sphereTexCoords[sphereIndices[i]].t);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
        &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        &normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float),
        &texCoords[0], GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



int main() {
    //Overall Initialization
    ShaderInit();

    //musicInit("../resource/mp3/bgm.wav",
    //    "../resource/mp3/shoot.wav",
     //   "../resource/mp3/boom.wav");
    GameLogic::init(2, 5);

    //mciSendString("open D:\\CloudMusic\\kk(V0).mp3 alias music", 0, 0, 0);//alias是别名的意思，下面就可以去直接用music来代替kk.mp3 
    //mciSendString("play music", 0, 0, 0);//播放音乐 


    // render loop
    // -----------
    window.run();
    //system("pause");
    return 0;
}



//GLuint VAO_M, VBO_M[3];
//glm::vec3 ModelPos(1.2f, 1.0f, 2.0f);
//ImportedModel myModel("C:\\Users\\75247\\Desktop\\learncg\\blender\\simplecar.obj");
/*
void setupVertices(ImportedModel myModel)
{
    vector<glm::vec3> vert = myModel.getVertices();
    vector<glm::vec2> text = myModel.getTextureCoords();
    vector<glm::vec3> norm = myModel.getNormals();

    vector<float> pValues;
    vector<float> tValues;
    vector<float> nValues;

    for (int i = 0; i < myModel.getNumVertices(); i++)
    {
        pValues.push_back(vert[i].x);
        pValues.push_back(vert[i].y);
        pValues.push_back(vert[i].z);

        tValues.push_back(text[i].s);
        tValues.push_back(text[i].t);

        nValues.push_back(norm[i].x);
        nValues.push_back(norm[i].y);
        nValues.push_back(norm[i].z);
    }

    glGenVertexArrays(1, &VAO_M);

    glBindVertexArray(VAO_M);

    glGenBuffers(3, VBO_M);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_M[0]);
    glBufferData(GL_ARRAY_BUFFER, pValues.size() * sizeof(float), &(pValues[0]), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, myModel.getVertices().size() * sizeof(float), &(pVlaues[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_M[1]);
    glBufferData(GL_ARRAY_BUFFER, tValues.size() * sizeof(float), &(tValues[0]), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, myModel.getTextureCoords().size() * sizeof(float), &(tValues[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_M[2]);
    glBufferData(GL_ARRAY_BUFFER, nValues.size() * sizeof(float), &(nValues[0]), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, myModel.getNormals().size() * sizeof(float), &(nValues[0]), GL_STATIC_DRAW);
}
*/



/*int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    /*
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    */
    //glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
/*
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}

glEnable(GL_DEPTH_TEST);

// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//stbi_set_flip_vertically_on_load(true);

// configure global opengl state
// -----------------------------
setupModel(sphere, VAO, VBO);
Shader lightingShader("Sphere.vs", "Sphere.fs");
Shader lightSphereShader("3.1.light_cube.vs", "3.1.light_cube.fs");
Shader ModelShader("model.vs", "model.fs");
Shader skyboxShader("6.1.skybox.vs", "6.1.skybox.fs");
// positions all containers
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f), //sun
    glm::vec3(16.0f,  0.0f, 0.0f),  //earth
    glm::vec3(17.7f, 0.2f, 0.5f), //moon
    glm::vec3(12.0f, 0.0f, 0.0f),  //venus
    glm::vec3(30.4f, -0.4f, -1.5f)       //juypter

};
float skyboxVertices[] = {
    // positions          
    -100.0f,  100.0f, -100.0f,
    -100.0f, -100.0f, -100.0f,
     100.0f, -100.0f, -100.0f,
     100.0f, -100.0f, -100.0f,
     100.0f,  100.0f, -100.0f,
    -100.0f,  100.0f, -100.0f,

    -100.0f, -100.0f,  100.0f,
    -100.0f, -100.0f, -100.0f,
    -100.0f,  100.0f, -100.0f,
    -100.0f,  100.0f, -100.0f,
    -100.0f,  100.0f,  100.0f,
    -100.0f, -100.0f,  100.0f,

     100.0f, -100.0f, -100.0f,
     100.0f, -100.0f,  100.0f,
     100.0f,  100.0f,  100.0f,
     100.0f,  100.0f,  100.0f,
     100.0f,  100.0f, -100.0f,
     100.0f, -100.0f, -100.0f,

    -100.0f, -100.0f,  100.0f,
    -100.0f,  100.0f,  100.0f,
     100.0f,  100.0f,  100.0f,
     100.0f,  100.0f,  100.0f,
     100.0f, -100.0f,  100.0f,
    -100.0f, -100.0f,  100.0f,

    -100.0f,  100.0f, -100.0f,
     100.0f,  100.0f, -100.0f,
     100.0f,  100.0f,  100.0f,
     100.0f,  100.0f,  100.0f,
    -100.0f,  100.0f,  100.0f,
    -100.0f,  100.0f, -100.0f,

    -100.0f, -100.0f, -100.0f,
    -100.0f, -100.0f,  100.0f,
     100.0f, -100.0f, -100.0f,
     100.0f, -100.0f, -100.0f,
    -100.0f, -100.0f,  100.0f,
     100.0f, -100.0f,  100.0f
};

// skybox VAO
unsigned int skyboxVAO, skyboxVBO;
glGenVertexArrays(1, &skyboxVAO);
glGenBuffers(1, &skyboxVBO);
glBindVertexArray(skyboxVAO);
glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

unsigned int cubeVBO, cubeVAO;
glGenBuffers(1, &cubeVBO);
glGenVertexArrays(1, &cubeVAO);

glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindVertexArray(cubeVAO);

glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
// note that we update the lamp's position attribute's stride to reflect the updated buffer data
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);


glm::vec3 moonshift = glm::vec3(9.7f, 0.2f, 0.0f);

setupModel(sphere1, VAO1, VBO1);
setupModel(sphere2, VAO2, VBO2);
setupModel(sphere3, VAO3, VBO3);
setupModel(sphere4, VAO4, VBO4);
setupModel(sphere5, VAO5, VBO5);


unsigned int diffuseMap = loadTexture("C:\\Users\\75247\\Desktop\\learncg\\wall.jpg");


unsigned int diffuseMap1 = loadTexture("C:\\Users\\75247\\Desktop\\sun3.png");
unsigned int diffuseMap2 = loadTexture("C:\\Users\\75247\\Desktop\\earth.png");
unsigned int diffuseMap3 = loadTexture("C:\\Users\\75247\\Desktop\\moon.png");
unsigned int diffuseMap4 = loadTexture("C:\\Users\\75247\\Desktop\\Venus.png");
unsigned int diffuseMap5 = loadTexture("C:\\Users\\75247\\Desktop\\juypter.png");

lightingShader.use();
lightingShader.setInt("material.diffuse", 0);
//lightingShader.setInt("material.specular", 1);
// load textures
// -------------
vector<std::string> faces
{
   "C:\\Users\\75247\\Desktop\\learncg\\skybox\\right.jpg",
    "C:\\Users\\75247\\Desktop\\learncg\\skybox\\left.jpg" ,
    "C:\\Users\\75247\\Desktop\\learncg\\skybox\\top.jpg" ,
   "C:\\Users\\75247\\Desktop\\learncg\\skybox\\bottom.jpg" ,
    "C:\\Users\\75247\\Desktop\\learncg\\skybox\\front.jpg" ,
   "C:\\Users\\75247\\Desktop\\learncg\\skybox\\back.jpg" ,
};
unsigned int cubemapTexture = loadCubemap(faces);
*/

/*
//auto cameraPos = glm::vec3(-0.5f, 2.0f, 1.5f);
int a = 100;
while (a--)//!glfwWindowShouldClose(window))
{
    ShaderInit();

    GameLogic::init(2, 2);
    window.run();
    float y;
    float z;
    //processInput(window);
    for (int i = 0; i < 36000; i++) {
        y = 100 * cos(i * theta);
        z = 100 * sin(i * theta);
        // per-frame time logic
    // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        //deltaTime = currentFrame - lastFrame;
        //lastFrame = currentFrame;
        lightPos = glm::vec3(0.0f, y, z);
        // input
        // -----
        //processInput(window);
        //if (glfwWindowShouldClose(window)) {
        //    break;
        //}

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::vec3 lightColor;
        lightColor.x = 251.0 / 255.0;
        lightColor.y = 172.0 / 255.0;
        lightColor.z = 19.0 / 255.0;


        /*
        setupVertices(myModel);

        ModelShader.use();
        // view/projection transformations
        glm::mat4 projectionm = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 viewm = camera.GetViewMatrix();
        ModelShader.setMat4("projection", projectionm);
        ModelShader.setMat4("view", viewm);

        // render the loaded model
        glm::mat4 modelm = glm::mat4(1.0f);
        modelm = glm::translate(modelm, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        modelm = glm::scale(modelm, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ModelShader.setMat4("model", modelm);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_M[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_M[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_M[2]);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());
        */
        //glBindVertexArray(VAO_M); 
        //glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());

/*
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMat();

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(3, 3, 3));
        model = glm::rotate(model, (float)(2 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 1.0f));
        /*
        glm::mat4 view = glm::lookAt(cameraPos,
            glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        */
/*
        lightSphereShader.use();
        lightSphereShader.setMat4("projection", projection);
        lightSphereShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightSphereShader.setMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setMat4("model", model);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);

        // light properties
        //lightingShader.setVec3("light.ambient", ambientColor);
        //lightingShader.setVec3("light.diffuse", diffuseColor);
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);

        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setFloat("light.constant", 1.0f);
        lightingShader.setFloat("light.linear", 0.09f);
        lightingShader.setFloat("light.quadratic", 0.032f);
        // material properties
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightingShader.setFloat("material.shininess", 32.0f);
        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        // bind diffuse map

        // bind specular map
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, specularMap);
        //glBindVertexArray(VAO_M); 
        //glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());

        /*
        unsigned int diffuseMap1 = loadTexture("C:\\Users\\75247\\Desktop\\Sun2.jpg");
        unsigned int diffuseMap2 = loadTexture("C:\\Users\\75247\\Desktop\\earth.png");
        unsigned int diffuseMap3 = loadTexture("C:\\Users\\75247\\Desktop\\moon.png");
        unsigned int diffuseMap4 = loadTexture("C:\\Users\\75247\\Desktop\\Venus.png");
        unsigned int diffuseMap5 = loadTexture("C:\\Users\\75247\\Desktop\\juypter.png");*/
/*
        for (unsigned int i = 0; i < 5; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            if (i == 0) {
                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                // sun
                lightingShader.setVec3("light.ambient", 5.2f, 5.2f, 5.2f);
                lightingShader.setVec3("light.diffuse", 3.9f, 3.9f, 3.9f);
                //model = glm::scale(model, glm::vec3(3.5, 3.5, 3.5));
                glBindTexture(GL_TEXTURE_2D, diffuseMap4);
                glBindVertexArray(VAO1);
            }
            else if (i == 1) {
                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                // earth
                //model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
                glBindTexture(GL_TEXTURE_2D, diffuseMap2);
                glBindVertexArray(VAO2);
            }
            else if (i == 2) {
                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                // moon
                //model = glm::scale(model, glm::vec3(0.15, 0.15, 0.15));
                glBindTexture(GL_TEXTURE_2D, diffuseMap3);
                glBindVertexArray(VAO3);
            }
            else if (i == 3) {
                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                // Venus
                //model = glm::scale(model, glm::vec3(0.7, 0.7, 0.7));
                glBindTexture(GL_TEXTURE_2D, diffuseMap4);
                glBindVertexArray(VAO4);
            }
            else {
                // bind diffuse map
                glActiveTexture(GL_TEXTURE0);
                // juypter
                //model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
                glBindTexture(GL_TEXTURE_2D, diffuseMap5);
                glBindVertexArray(VAO5);
            }
            if (i == 0) {
                //Sun
                //model = glm::rotate(model, (float)(0.20 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                //model = glm::translate(model, cubePositions[i]);
                model = glm::translate(model, lightPos);
                model = glm::scale(model, glm::vec3(8.5, 8.5, 8.5));
                //float angle = 20.0f * i;
                model = glm::rotate(model, (float)(0.19 * glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
                lightingShader.setMat4("model", model);
            }
            else if (i == 1) {
                // earth
                model = glm::rotate(model, (float)(0.5 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, cubePositions[i]);
                model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
                //float angle = 20.0f * i;
                model = glm::rotate(model, (float)(0.5 * glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
                lightingShader.setMat4("model", model);
            }
            else if (i == 2) {
                // moon
                //model = glm::rotate(model, (float)(0.1 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                //model = glm::translate(model, moonshift);
                model = glm::rotate(model, (float)(0.5 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, cubePositions[1]);
                model = glm::scale(model, glm::vec3(0.15, 0.15, 0.15));
                //float angle = 20.0f * i;
                model = glm::rotate(model, (float)(0.5 * glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::translate(model, moonshift);
                model = glm::rotate(model, (float)(0.1 * glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
                lightingShader.setMat4("model", model);
            }
            else if (i == 3) {
                // Venus
                model = glm::rotate(model, (float)(0.3 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, cubePositions[i]);
                model = glm::scale(model, glm::vec3(0.7, 0.7, 0.7));
                //float angle = 20.0f * i;
                model = glm::rotate(model, (float)(0.3 * glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
                lightingShader.setMat4("model", model);
            }
            else {
                // Juypter
                model = glm::rotate(model, (float)(0.6 * glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, cubePositions[i]);
                model = glm::scale(model, glm::vec3(3.5, 3.5, 3.5));
                // angle = 20.0f * i;
                model = glm::rotate(model, (float)(0.6 * glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
                lightingShader.setMat4("model", model);
            }

            if (i == 0) {
                glDrawArrays(GL_TRIANGLES, 0, sphere1.GetNumIndices());
            }
            else if (i == 1) {
                glDrawArrays(GL_TRIANGLES, 0, sphere2.GetNumIndices());
            }
            else if (i == 2) {
                glDrawArrays(GL_TRIANGLES, 0, sphere3.GetNumIndices());
            }
            else if (i == 3) {
                glDrawArrays(GL_TRIANGLES, 0, sphere4.GetNumIndices());
            }
            else {
                glDrawArrays(GL_TRIANGLES, 0, sphere5.GetNumIndices());
            }
        }

        // draw skybox as last

        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.getViewMat())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        // render the cube
        // glBindVertexArray(cubeVAO);
        // glDrawArrays(GL_TRIANGLES, 0, 36);*/

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //glfwSwapBuffers(window);
        //glfwPollEvents();
/*
    }



}
*/
/*
// glfw: terminate, clearing all previously allocated GLFW resources.
// ------------------------------------------------------------------
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(3, VBO);

glDeleteVertexArrays(1, &VAO1);
glDeleteBuffers(3, VBO1);
glDeleteVertexArrays(1, &VAO2);
glDeleteBuffers(3, VBO2);
glDeleteVertexArrays(1, &VAO3);
glDeleteBuffers(3, VBO3);
glDeleteVertexArrays(1, &VAO4);
glDeleteBuffers(3, VBO4);
glDeleteVertexArrays(1, &VAO5);
glDeleteBuffers(3, VBO5);

//glDeleteVertexArrays(1, &VAO_M);
//glDeleteBuffers(3, VBO_M);

glDeleteVertexArrays(1, &cubeVAO);
glDeleteBuffers(1, &cubeVBO);

glfwTerminate();
return 0;
}
*/
/*
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKey(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKey(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKey(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKey(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.processMouse(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processScroll(static_cast<float>(yoffset));
}
*/

/*
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}*/
/*
// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}*/