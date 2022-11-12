#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/Shader.h"
#include "graphics/texture.h"
#include "graphics/model/cube.hpp"
#include "io/joystick.h"
#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/camera.h"
#include "io/Screen.h"

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(double dt);
string loadShaderSrc(const char* fileName);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float mixVal = 0.2f;
Joystick mainJ(0);
mat4 transform = mat4(1.0f);

Camera cameras[2] = {
    Camera(vec3(0.0f, 0.0f, 3.0f)),
    Camera(vec3(0.0f, 0.0f, 10.0f))
};
int activeCam = 0;

//Camera camera(vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Screen screen;



float x, y, z;

int main()
{
    int success;
    char infoLog[512];

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (!screen.init()) {
        cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    screen.setParameters();
    glEnable(GL_DEPTH_TEST);

    /*
        shaders
    */
    Shader shader("assets/object.vs", "assets/object.fs");

    Cube cube(vec3(0.0f, 0.0f, -1.0f), vec3(0.75f));
    cube.init();


    mainJ.update();
    if (mainJ.isPresent()) {
        cout << mainJ.getName()<<" is present " << endl;
    }
    else {
        cout << "Not Present." << endl;
    }

    x = 0.0f;
    y = 0.0f;
    z = 3.0f;
    
    // render loop
    // -----------
    while (!screen.shouldClose())
    {
        // input
        // -----
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        processInput(deltaTime);

        // render
        // ------
        screen.update(); 

        shader.activate();
        shader.setFloat("mixVal", mixVal);

        //create transformation for screen
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);
        //view = translate(view, vec3(-x, -y, -z));
        view = cameras[activeCam].getViewMatrix();
        projection = perspective(radians(cameras[activeCam].getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        cube.render(shader);

        screen.newFrame();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(double dt)
{
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        screen.setShouldClose(true);
    }

    //change mix color
    if (Keyboard::keyWentDown(GLFW_KEY_UP)) {
        mixVal += 0.02f;
        if (mixVal > 1) {
            mixVal = 1.0f;
        }
    }

    if (Keyboard::keyWentDown(GLFW_KEY_DOWN)) {
        mixVal -= 0.02f;
        if (mixVal < 0) {
            mixVal = 0.0f;
        }
    }

    //move camera
    if (Keyboard::key(GLFW_KEY_W)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::FORWARD, dt);
    }
    if (Keyboard::key(GLFW_KEY_S)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::BACKWARD, dt);
    }
    if (Keyboard::key(GLFW_KEY_D)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::RIGHT, dt);
    }
    if (Keyboard::key(GLFW_KEY_A)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::LEFT, dt);
    }
    if (Keyboard::key(GLFW_KEY_SPACE)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::UP, dt);
    }
    if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
        cameras[activeCam].updateCameraPosition(CameraDirection::DOWN, dt);
    }

    if (Keyboard::keyWentDown(GLFW_KEY_TAB)) {
            activeCam += activeCam==0? 1 : -1;
        
    }

    double dx = Mouse::getDX(), dy = Mouse::getDY();
    if (dx != 0 | dy != 0) {
        cameras[activeCam].updateCameraDirection(dx, dy);
    }

    double scrollDy = Mouse::getScrollDY(), scrollDx = Mouse::getScrollDX();
    if (scrollDy != 0) {
        cameras[activeCam].updateCameraZoom(scrollDy);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}