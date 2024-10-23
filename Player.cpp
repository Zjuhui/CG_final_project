#include "Player.h"
#include "ImportedModel.h"


unsigned int playerVAO, playerVBO, playerEBO;
vector<float> playerVertices;
vector<unsigned int> playerElement;

unsigned int bulletVAO, bulletVBO, bulletEBO;
vector<float> bulletVertices;
vector<unsigned int> bulletElement;

ImportedModel myModel("C:/Users/75247/Desktop/duck5.obj");
GLuint VAO_M, VBO_M[3];

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


extern unsigned int diffuseMap;
void readOBJ(const char* filename, vector<float>& vertices, vector<unsigned int>& elements) {
    FILE* fp = fopen(filename, "r");
    if (fp == nullptr) {
        puts("Error: failed to read player obj file!");
        exit(-1);
    }
    char cmd[1024];
    char seps[] = " ,\t\n";
    while (true) {
        if (fgets(cmd, 1024, fp) == nullptr) break;
        char* token = strtok(cmd, seps);
        if (token == nullptr) continue;

        if (strcmp(token, "v") == 0) {
            for (int i = 0; i < 3; ++i) {
                token = strtok(nullptr, seps);
                vertices.push_back(atof(token));
            }
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
        }
        if (strcmp(token, "f") == 0) {
            for (int i = 0; i < 3; ++i) {
                token = strtok(nullptr, seps);
                elements.push_back(atof(token) - 1);
            }
        }
    }
    fclose(fp);
}

void playerRenderInit() {
    setupVertices(myModel);
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

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, diffuseMap); 

    //glEnable(GL_DEPTH_TEST); 
    //指定用于深度缓冲比较值；
    //glDepthFunc(GL_LEQUAL); 
    //glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices()); 
    //readOBJ("C:/Users/75247/Desktop/learncg/objLoaderShuttle/objLoaderShuttle/resources/shuttle.obj", playerVertices, playerElement);
    //glGenVertexArrays(1, &playerVAO);
    //glGenBuffers(1, &playerVBO);
    //glGenBuffers(1, &playerEBO);
    //glBindVertexArray(playerVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
    //glBufferData(GL_ARRAY_BUFFER, playerVertices.size() * sizeof(float), &playerVertices[0], GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, playerElement.size() * sizeof(unsigned int), &playerElement[0], GL_STATIC_DRAW);
}

void drawPlayer() {
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, diffuseMap);
    //  glActiveTexture(GL_TEXTURE0);
    glEnable(GL_DEPTH_TEST);  
    //指定用于深度缓冲比较值； 
    glDepthFunc(GL_LEQUAL);  
    glBindVertexArray(VAO_M); 
    glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());  

    //glEnable(GL_DEPTH_TEST);  
    //glDepthFunc(GL_LEQUAL); 
    //glBindVertexArray(VAO_M); 
    //glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices()); 
    //glBindVertexArray(playerVAO);
    //glDrawElements(GL_TRIANGLES, playerElement.size() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}

void bulletRenderInit() {
    readOBJ("C:/Users/75247/Desktop/bullet.obj", bulletVertices, bulletElement);
    glGenVertexArrays(1, &bulletVAO);
    glGenBuffers(1, &bulletVBO);
    glGenBuffers(1, &bulletEBO);
    glBindVertexArray(bulletVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bulletVBO);
    glBufferData(GL_ARRAY_BUFFER, bulletVertices.size() * sizeof(float), &bulletVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bulletEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bulletElement.size() * sizeof(unsigned int), &bulletElement[0], GL_STATIC_DRAW);
}

void drawBullet() {
    glBindVertexArray(bulletVAO);
    glDrawElements(GL_TRIANGLES, bulletElement.size() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}


//log 
void drawParticle() {
    glBindVertexArray(bulletVAO);
    glDrawElements(GL_TRIANGLES, bulletElement.size() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}






































































