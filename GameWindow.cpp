#include "GameWindow.h"
#include "camera.h"
#include "Renderer.h"
#include "defineList.h"
#include "Player.h"
#define PATH "D:\\CloudMusic\\"

//#include <stdio.h>
//#include <Mmsystem.h>
//#include <windows.h>

//#pragma comment(lib,"winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

Camera camera(glm::vec3(0.0f, 15.0f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;
extern GameLogic game;
glm::vec3 light_pos(100.0f, 100.0f, 25.0f);

const char* music1 = "D:\\CloudMusic\\Artur Tokhtash - The Expentance.wav";
const char* music2 = "D:\\CloudMusic\\Peaceful Warrior.wav";
const char* music3 = "D:\\CloudMusic\\Stephen Barton - Apex Legends_ Main Theme.wav";
const char* music4 = "D:\\CloudMusic\\无畏契约 _ Grabbitz - Die For You (为你而战).wav";
const char* music5 = "D:\\CloudMusic\\Artur Tokhtash - The Expentance.wav";


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    //camera.check();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKey(cameraMovement::FORWARD, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKey(cameraMovement::BACKWARD, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKey(cameraMovement::LEFT, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKey(cameraMovement::RIGHT, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.processKey(cameraMovement::CAMERA_PLAYER, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)  
        camera.processKey(cameraMovement::LAST_PLAYER, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)   
        camera.processKey(cameraMovement::NEXT_PLAYER, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKey(cameraMovement::UP, deltaTime, currentFrame);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKey(cameraMovement::DOWN, deltaTime, currentFrame);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        camera.processKey(cameraMovement::SHOOT, deltaTime, currentFrame);
    }
    if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
        camera.shooting = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstFlag = true;
    static float lastX, lastY;
    if (firstFlag) {
        lastX = xpos;
        lastY = ypos;
        firstFlag = false;
    }
    float xOffset = (xpos - lastX);
    float yOffset = (lastY - ypos);
    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xOffset, yOffset, currentFrame);
}

void scroll_callback(GLFWwindow* windows, double xOffset, double yOffset) {
    camera.processScroll(yOffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GameWindow::GameWindow() :window(NULL) {
    init();
}

void GameWindow::init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG_demo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GameWindow::run() {
    extern glm::mat4 projection, view, model;
    //PlaySound(TEXT("C:\\Users\\75247\\Music\\Peaceful Warrior.wav"), NULL, SND_FILENAME | SND_ASYNC);
    
    
    //system("pause");

    //mciSendString("D:\\CloudMusic\\Various Artists - World of Warships OST 12.mp3", NULL, 0, NULL);

    //mciSendString("open D:\\CloudMusic\\Artur Tokhtash - The Expentance(V0).mp3 alias a", 0, 0, 0);//alias是别名的意思，下面就可以去直接用music来代替kk.mp3 
    //mciSendString("play a", 0, 0, 0);//播放音乐   
    
    
    PlaySound(TEXT(music1), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
    //PlaySound(TEXT(music1), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
    while (!glfwWindowShouldClose(window))
    {   
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            PlaySound(TEXT(music2), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) { 
            PlaySound(TEXT(music3), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); 
        } 
        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
            PlaySound(TEXT(music4), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { 
            PlaySound(TEXT(music5), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        //mciSendString("play a", 0, 0, 0);//播放音乐  
        //mciSendString("open D:\\CloudMusic\\kk(V0).mp3 alias music", 0, 0, 0);//alias是别名的意思，下面就可以去直接用music来代替kk.mp3 
        //mciSendString("play music", 0, 0, 0);//播放音乐    
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        GameLogic::checkPlayer(currentFrame);
        
        for (auto bullet = Bullet::bulletQueue.begin(); bullet != Bullet::bulletQueue.end();) {
            GameLogic::checkBullet(*bullet, currentFrame);
            if (!(*bullet)->isAlive()) {
                bullet = Bullet::bulletQueue.erase(bullet);//
                continue;
            }
            bullet++;
        }
        for (auto player = Player::playerQueue.begin(); player != Player::playerQueue.end();) {
            if (!(*player)->isAlive()) {
                (*player)->deadBomb(currentFrame, (*player)->getDefeater());
                player = Player::playerQueue.erase(player);//
                continue;
            }
            player++;
        }
        for (auto particle = Particle::particleQueue.begin(); particle != Particle::particleQueue.end();) {
            //GameLogic::checkParticle(*bullet, currentFrame);
            (*particle)->update(deltaTime);
            if (!(*particle)->isAlive()) {
                particle = Particle::particleQueue.erase(particle);//
                continue;
            }
            particle++;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Depth test
        renderShadowDepth(Player::playerQueue , Bullet::bulletQueue);

        // render
        // ------

        projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.getViewMat();
        model = glm::mat4();

        for (auto bullet : Bullet::bulletQueue) {
            renderBullet(bullet, currentFrame);
        }
        GameLogic::plantBullet();



        for (auto player : Player::playerQueue) {
            renderPlayer(player, currentFrame);
        }
        for (auto particle : Particle::particleQueue) {
            renderParticle(particle, currentFrame);
        }
        
        renderFloor();
        
        //wallRender();

        WaterRenderInit();
        
        renderSkybox();
        //renderSkybox();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        camera.jitter += deltaTime;
        camera.shootJitter += deltaTime;
        if (camera.shooting) camera.processKey(cameraMovement::SHOOT, deltaTime, currentFrame);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}