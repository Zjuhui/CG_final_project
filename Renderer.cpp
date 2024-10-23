#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include "Renderer.h"
#include "ImportedModel.h"
#include "TextureLoader.h"
//#include "Program.h"
#include "SceneRender.h"
//#include "Floor.h"

extern Camera camera;
glm::mat4 projection, view, model;

void initProgram();

Shader * floorShader, * playerShader, * shadowShader, * skyBoxShader , * bulletShader;

//shadow log

extern unsigned int noiseTexture;
extern unsigned int depthTexture, depthFBO;


unsigned int initializeReflectionFBO();
unsigned int initializeRefractionFBO();
extern glm::vec3 light_pos;
extern ImportedModel myModel;
//void renderShadowDepth(vector<Player*> playerList, vector<Bullet*> bulletList);
// utility function for loading a 2D texture from file
// ---------------------------------------------------

unsigned int loadTexture_t(char const* path)
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
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glBindTexture(GL_TEXTURE_2D, textureRef);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        //glGenerateMipmap(GL_TEXTURE_2D); 

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int diffuseMap = loadTexture_a("C:/Users/75247/Desktop/duckCM.bmp");


//water shader 
// 
// Global var for convenience
unsigned int reflectionColorBuffer;
unsigned int refractionColorBuffer;

extern float deltaTime;    // time between current frame and last frame
extern float lastFrame;

float reflect_plane[4] = { 0, 1, 0, 0 };
float refract_plane[4] = { 0, -1, 0, 0 };
float plane[4] = { 0, -1, 0, 100000 };

unsigned int texture1, texture2;

unsigned int DuDvTexture;
unsigned int normalTexture;

unsigned int waterTexture;

float wave_speed = 0.07f;
float moveFactor = 0;

Shader waterShader("water.vs", "water.fs");
Shader wallShader("wall.vs","wall.fs");

// vertex data
float water[] = { // all y set to 0
    
    -80, 80, // botton left
    80,  80, // bottom right
    80,  -80, // top right
    -80,  80, // botton left
    80,  -80, // top right
    -80,  -80 // top left
     
    /*
    -1, 1,

    1, 1,

    1, -1,

    -1, 1,

    1, -1,

    -1, -1
    */
};

float wall[] = {
    // position texture
    -2, 2, -5,   0, 1,
    -2, -2, -5,  0, 0,
    2, -2, -5,   1, 0,
    2, -2, -5,   1, 0,
    2, 2, -5,    1, 1,
    -2, 2, -5,   0, 1,

    2, 2, 5,     0, 1,
    2, -2, 5,    0, 0,
    -2, -2, 5,   1, 0,
    -2, -2, 5,   1, 0,
    -2, 2, 5,    1, 1,
    2, 2, 5,     0, 1,

    -2, 2, 5,    0, 1,
    -2, -2, 5,   0, 0,
    -2, -2, -5,  1, 0,
    -2, -2, -5,  1, 0,
    -2, 2, -5,   1, 1,
    -2, 2, 5,    0, 1,

    2, 2, -5,    0, 1,
    2, -2, -5,   0, 0,
    2, -2, 5,    1, 0,
    2, -2, 5,    1, 0,
    2, 2, 5,     1, 1,
    2, 2, -5,    0, 1
};

float floor_a[] = {
        -2, -2, -5,  0, 1,
        -2, -2, 5,   0, 0,
        2, -2, 5,    1, 0,
        2, -2, 5,    1, 0,
        2, -2, -5,   1, 1,
        -2, -2, -5,  0, 1,
};

/*
float wall[] = {
    // Î»ÖÃ  ÎÆÀí
    -80, 0, -5,   0, 1,
    -80, 0, 5,    0, 0,
    80,  0, 5,    1, 0,
    80,  0, 5,    1, 0,
    80,  0, -5,   1, 1,
    -80, 0, -5,   0, 1,

    80,  0, -5,   0, 1,
    80,  0, 5,    0, 0,
    -80, 0, 5,    1, 0,
    -80, 0, 5,    1, 0,
    -80, 0, -5,   1, 1,
    80,  0, -5,   0, 1,

    -80, 0, -5,   0, 1,
    -80, 0, 5,    0, 0,
    -80, 0, 5,    1, 0,
    -80, 0, 5,    1, 0,
    -80, 0, -5,   1, 1,
    -80, 0, -5,   0, 1,

    80,  0, -5,   0, 1,
    80,  0, 5,    0, 0,
    80,  0, 5,    1, 0,
    80,  0, 5,    1, 0,
    80,  0, -5,   1, 1,
    80,  0, -5,   0, 1
};

float floor_a[] = {
        -80, 0, -5,  0, 1,
        -80, 0, 5,   0, 0,
        80,  0, 5,   1, 0,
        80,  0, 5,   1, 0,
        80,  0, -5,  1, 1,
        -80, 0, -5,  0, 1
};
*/
unsigned int wallVAO, floor_aVAO;
unsigned int wallVBO, floor_aVBO;

 
unsigned int waterVBO, waterVAO;

//
void ShaderInit() {
	floorShader = new Shader("floor.vs","floor.fs");
	playerShader = new Shader("player.vs","player.fs");
	shadowShader = new Shader("shadow.vs","shadow.fs");
    skyBoxShader = new Shader("6.1.skybox.vs", "6.1.skybox.fs");

    bulletShader = new Shader("bullet.vs","bullet.fs");

    skyBoxInit("C:/Users/75247/Desktop/skybox");
    floorInit("C:/Users/75247/Desktop/water.jpg");
	shadowInit();
    bulletRenderInit();
	playerRenderInit();

    //WaterRenderInit();
    wallRender();
}

void renderFloor() {
    floorShader->use();
    floorShader->setMat4("view", view);
    floorShader->setMat4("projection", projection);
    floorShader->setMat4("model", model);
    floorShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    floorShader->setVec3("lightPos", light_pos);
    floorShader->setVec3("cameraPos", (camera.bind()) ? camera.getPlayerPos() : camera.getPosition());

    float near_plane = -100.0f, far_plane = 100.0f;
    glm::mat4 lightProjection = glm::ortho(-30.0f, 30.0f, -60.0f, 50.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(SHADOW_LIGHT_POS), glm::vec3(SHADOW_WATCH_POS), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    floorShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    floorShader->setInt("NoiseTexture", 0);
    floorShader->setInt("shadowMap", 1);

    drawFloor();
}

void renderSkybox() {
    skyBoxShader->use();
    view = glm::mat4(glm::mat3(camera.getViewMat()));
    skyBoxShader->setMat4("view", view);
    skyBoxShader->setMat4("projection", projection);
    drawSkyBox(projection, camera);
}

void renderBullet(Bullet* bullet, float time) {
    bulletShader->use();
    glm::mat4 model;
    model = glm::translate(model, bullet->getPos());
    float ratio = bullet->getRadius();
    model = glm::scale(model, glm::vec3(ratio, ratio, ratio));
    bulletShader->setMat4("projection", projection);
    bulletShader->setMat4("view", view);
    bulletShader->setMat4("model", model);
    bulletShader->setVec3("color", bullet->getColor());
    drawBullet();
}


void renderPlayer(Player* player, float time) {
    //playerShader->useProgram();
    playerShader->use();
    glm::mat4 model;
    float ratio = player->getHalfLength();
    float fateY = player->getFateY();
    model = glm::translate(model, player->getPos() + glm::vec3(0, fateY * ratio, 0));
    model = glm::scale(model, glm::vec3(ratio, fateY * ratio, ratio));
    model = glm::rotate(model, glm::radians(player->rotateAngle()), glm::vec3(0, 1, 0));
    playerShader->setMat4("projection", projection);
    playerShader->setMat4("view", view);
    playerShader->setMat4("model", model);
    glm::vec3 c;
    if (player->Attacked()) {
        c = glm::vec3(1, 0, 0);
        player->Attacked() = false;
    }
    else {
    c = player->getColor();
    }
    playerShader->setVec3("color", c);
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, diffuseMap); 
    drawPlayer();
}

void renderParticle(Particle* particle, float time) {
    bulletShader->use();
    
    glm::mat4 model;
    model = glm::translate(model, particle->getPos());
    float ratio = 0.1;
    model = glm::scale(model, glm::vec3(ratio, ratio, ratio));
    bulletShader->setMat4("projection", projection);
    bulletShader->setMat4("view", view);
    bulletShader->setMat4("model", model);
    bulletShader->setVec3("color", particle->getColor());
    drawParticle();
}

void renderShadowDepth(vector<Player*> playerList, vector<Bullet*> bulletList) {
    float near_plane = -100.0f, far_plane = 100.0f;
    glm::mat4 lightProjection = glm::ortho(-30.0f, 30.0f, -60.0f, 50.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(SHADOW_LIGHT_POS), glm::vec3(SHADOW_WATCH_POS), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    shadowBind();
    for (auto player : playerList) {
        glm::mat4 model;
        float ratio = player->getHalfLength();
        float fateY = player->getFateY();
        model = glm::translate(model, player->getPos() + glm::vec3(0, fateY * ratio, 0));
        model = glm::scale(model, glm::vec3(ratio, fateY * ratio, ratio));
        model = glm::rotate(model, glm::radians(player->rotateAngle()), glm::vec3(0, 1, 0));
        //model = glm::rotate(model, 90.0f, glm::vec3(0, 1, 0));
        shadowShader->setMat4("model", model);
        drawPlayer();
    }

    for (auto bullet : bulletList) {
        glm::mat4 model;
        model = glm::translate(model, bullet->getPos());
        float ratio = bullet->getRadius();
        model = glm::scale(model, glm::vec3(ratio, ratio, ratio));
        shadowShader->setMat4("model", model);
        drawBullet();
    }

    shadowUnBind();
}



bool getTextureID(unsigned int& ID, char* s) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(s, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to open img." << std::endl;
        return false;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return true;
}

bool getTextureID_a(unsigned int& ID, const char* s) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(s, &width, &height, &nrChannels, 0);
    if (!data) {
        //std::cerr << "Failed to open img." << std::endl;
        return false;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return true;
}


void WaterRenderInit() {
    //unsigned int waterVBO, waterVAO;
    glGenVertexArrays(1, &waterVAO);
    glGenBuffers(1, &waterVBO);
    glBindVertexArray(waterVAO); 
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(water), water, GL_STATIC_DRAW); 
    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0); 


    int width, height, nrChannels;

    // load DuDv texture
    glGenTextures(1, &DuDvTexture);
    glBindTexture(GL_TEXTURE_2D, DuDvTexture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("C:/Users/75247/Desktop/textures/waterDUDV.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load DuDv texture" << std::endl;
    }
    stbi_image_free(data);

    // load normal texture
    glGenTextures(1, &normalTexture);
    glBindTexture(GL_TEXTURE_2D, normalTexture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/75247/Desktop/textures/normalMap.png", &width, &height, &nrChannels, 0);
    // data = stbi_load("../textures/matchingNormalMap.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load normal texture" << std::endl;
    }
    stbi_image_free(data);

    // render water
    waterShader.use();
    waterShader.setInt("reflectionTexture", 0);
    waterShader.setInt("refractionTexture", 1);
    waterShader.setInt("dudvMap", 2);
    waterShader.setInt("normalMap", 3);

    glm::vec3 lightPos(100.0f, 100.0f, 25.0f); 

    glm::vec3 light_Color(1, 1, 1); 

    // pass camera position
    glm::vec3 cameraPos = camera.Position;
    GLuint cameraPosition_loc = glGetUniformLocation(waterShader.ID, "cameraPosition");
    glUniform3fv(cameraPosition_loc, 1, glm::value_ptr(cameraPos));
    // pass light position
    GLuint lightPosition_loc = glGetUniformLocation(waterShader.ID, "lightPosition");
    glUniform3fv(lightPosition_loc, 1, glm::value_ptr(lightPos));
    // pass light color
    GLuint lightColor_loc = glGetUniformLocation(waterShader.ID, "lightColor");
    glUniform3fv(lightColor_loc, 1, glm::value_ptr(light_Color)); 
    float currentFrame = glfwGetTime();
    // wave
    moveFactor += wave_speed * currentFrame * 0.001;
    if (moveFactor >= 1)
        moveFactor -= 1;
    waterShader.setFloat("moveFactor", moveFactor);

   


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflectionColorBuffer);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refractionColorBuffer);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, DuDvTexture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normalTexture);


    glBindVertexArray(waterVAO);



    // do transformations
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    waterShader.setMat4("projection", projection);
    // camera/view transformation
    glm::mat4 view = camera.getViewMat();
    waterShader.setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.0, 1.0, 5.0));
    waterShader.setMat4("model", model);





    glDrawArrays(GL_TRIANGLES, 0, 6);


}

void floorRender() {
    glGenVertexArrays(1, &floor_aVAO);
    glGenBuffers(1, &floor_aVBO);

    glBindVertexArray(floor_aVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floor_aVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_a), floor_a, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("C:/Users/75247/Desktop/textures/marble.bmp", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/75247/Desktop/textures/bamboo.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free(data);
    //"C:/Users/75247/Desktop/Water-simulation/Graphics Engine/textures/normalMap.png"


}


void wallRender() {
    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallVBO);

    glBindVertexArray(wallVAO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wall), wall, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("C:/Users/75247/Desktop/Water-simulation/Graphics Engine/textures/marble.bmp", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/75247/Desktop/wood.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free(data);

    wallShader.use();
    wallShader.setInt("texture1", 0);

    unsigned int reflectionFBO = initializeReflectionFBO();
    unsigned int refractionFBO = initializeRefractionFBO();

    // render reflection texture
    glBindFramebuffer(GL_FRAMEBUFFER, reflectionFBO);
    float distance = 2 * (camera.Position.y - 0);
    camera.Position.y -= distance;
    camera.invertPitch(); // invert camera pitch
    renderScene(wallShader, reflect_plane);
    // reset camera back to original position
    camera.Position.y += distance;
    camera.invertPitch(); // invert back camera pitch

    // render refraction texture
    glBindFramebuffer(GL_FRAMEBUFFER, refractionFBO);
    renderScene(wallShader, refract_plane);

    // render to screen
    glDisable(GL_CLIP_DISTANCE0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // now bind back to default framebuffer
    renderScene(wallShader, plane);


}


// reflectionColorBuffer set as global var for convenience
unsigned int initializeReflectionFBO()
{
    // reflection frame buffer
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // create a color attachment texture
    unsigned int depthRenderBuffer, depthBuffer;
    glGenTextures(1, &reflectionColorBuffer);
    glBindTexture(GL_TEXTURE_2D, reflectionColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reflectionColorBuffer, 0);

    // create a depth render buffer attachment
    glGenRenderbuffers(1, &depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Reflection framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fbo;
}

unsigned int initializeRefractionFBO()
{
    // refraction frame buffer
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // create a color attachment texture
    unsigned int depthBuffer;
    glGenTextures(1, &refractionColorBuffer);
    glBindTexture(GL_TEXTURE_2D, refractionColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, refractionColorBuffer, 0);
    // create a depth attachment texture
    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Refraction framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fbo;
}


// draw everything aside from water
void renderScene(Shader wallShader, float clipPlane[4])
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1); // marble texture

    wallShader.use();
    // pass clip plane
    GLuint plane_location = glGetUniformLocation(wallShader.ID, "plane");
    glUniform4fv(plane_location, 1, clipPlane);
    // do transformations
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    wallShader.setMat4("projection", projection);
    // camera/view transformation
    glm::mat4 view = camera.getViewMat();
    wallShader.setMat4("view", view);
    glBindVertexArray(wallVAO);
    glm::mat4 model = glm::mat4(1.0f);
    wallShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    // draw floor
    glBindVertexArray(floor_aVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2); // floor texture
    glDrawArrays(GL_TRIANGLES, 0, 6);
}