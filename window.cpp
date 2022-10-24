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
#include "Shader.h"
#include "io/joystick.h"
#include "io/keyboard.h"
#include "io/mouse.h"

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
string loadShaderSrc(const char* fileName);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float mixVal = 0.2f;
mat4 transform = mat4(1.0f);
Joystick mainJ(0);

float x, y, z, d;

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

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, Keyboard::keyCallback);

    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

    

    
    glEnable(GL_DEPTH_TEST);

    /*
        shaders
    */
    Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
    Shader shader2("assets/vertex_core.glsl", "assets/fragment_core2.glsl");

    //vertex array
    /*float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };*/
    //float vertices[] = {
    //    //positions               colors                texture coordinates
    //     0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.5f,           0.0f, 0.0f, 
    //    -0.5f,  0.5f, 0.0f,     0.5f, 1.0f, 0.75f,          0.0f, 1.0f,
    //    -0.5f, -0.5f, 0.0f,     0.6f, 1.0f, 0.2f,           1.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f,     1.0f, 0.2f, 1.0f,           1.0f, 1.0f
    //};

    //float vertices[] = {
    //    // positions		// colors			// texture coordinates
    //    -0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 0.5f,	0.0f, 0.0f,	// bottom left
    //    -0.5f, 0.5f, 0.0f,	0.5f, 1.0f, 0.75f,	0.0f, 1.0f,	// top left
    //    0.5f, -0.5f, 0.0f,	0.6f, 1.0f, 0.2f,	1.0f, 0.0f,	// bottom right
    //    0.5f, 0.5f, 0.0f,	1.0f, 0.2f, 1.0f,	1.0f, 1.0f	// top right
    //};

    //unsigned int indices[] = {
    //    0, 1, 2, // first triangle
    //    3, 1, 2  // second triangle
    //};

    float vertices[] = {
        // Positions            texCoord
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //unsigned indices[] = {
    //    0, 1, 2, // first tirangle
    //    2, 3, 0 // second triangle
    //};

    //VAO & VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //set attribute pointer
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/

    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //TEXTURES
    unsigned int texture1, texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // GL_TEXTURE_WRAP_S = X, GL_TEXTURE_WRAP_T = Y, GL_TEXTURE_WRAP_R = Z
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //LOAD image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/corousel1.jpg", &width, &height, &nChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    data = stbi_load("assets/image_016_0003.png", &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);

    shader.activate();
    shader.setInt("texture1", 0);

    shader.setInt("texture2", 1);

    // set up EBO
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

    /*mat4 trans = mat4(1.0f);
    trans = rotate(trans, radians(45.0f), vec3(1.0f, 0.0f, 0.0f));
    trans = rotate(trans, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    shader.activate();
    shader.setMat4("transform", trans);*/

    /*mat4 trans2 = mat4(1.0f);
    trans2 = scale(trans2, vec3(0.5f));
    trans2 = rotate(trans2, radians(-45.0f), vec3(0.0f, 0.0f, 1.0f));
    shader2.activate();
    shader2.setMat4("transform", trans2);*/


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
    d = 50.0f;
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.8f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //trans = rotate(trans, radians((float) glfwGetTime() / 10000.0f), vec3(0.0f, 0.0f, 1.0f));
        //shader.activate();
        //shader.setMat4("transform", trans);
        /*trans2 = rotate(trans2, radians(-(float)glfwGetTime() / 100.0f), vec3(0.0f, 0.0f, 1.0f));
        shader2.activate();
        shader2.setMat4("transform", trans2);*/
        // draw shapes
        glBindVertexArray(VAO);

        //create transformation for screen
        mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);


        model = rotate(model, (float)glfwGetTime() * radians(-55.0f), vec3(0.5f));
        view = translate(view, vec3(-x, -y, -z));
        projection = perspective(radians(d), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


        shader.activate();

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.setFloat("mixVal", mixVal);
        //shader.setMat4("transform", transform);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        //shader2.activate();
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
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

    if (Keyboard::keyWentDown(GLFW_KEY_W)) {
        //transform = translate(transform, vec3(0.0f, 0.1f, 0.0f));

        y -= 0.03f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_S)) {
        //transform = translate(transform, vec3(0.0f, -0.1f, 0.0f));
        y += 0.03f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_A)) {
        //transform = translate(transform, vec3(-0.1f, 0.0f, 0.0f));
        x += 0.03f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_D)) {
        //transform = translate(transform, vec3(0.1f, 0.0f, 0.0f));
        x -= 0.03f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_Q)) {
        //transform = translate(transform, vec3(0.1f, 0.0f, 0.0f));
        z -= 0.25f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_Z)) {
        //transform = translate(transform, vec3(0.1f, 0.0f, 0.0f));
        z += 0.25f;
    }
    

    if (Keyboard::keyWentDown(GLFW_KEY_E)) {
        //transform = translate(transform, vec3(0.1f, 0.0f, 0.0f));
        d -= 1.0f;
    }

    if (Keyboard::keyWentDown(GLFW_KEY_C)) {
        //transform = translate(transform, vec3(0.1f, 0.0f, 0.0f));
        d += 1.0f;
    }

    mainJ.update();

    /*float lx = mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_X);
    float ly = mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_STICK_Y);

    if (abs(lx) > 0.5f) {
        transform = translate(transform, vec3(lx/10, 0.0f, 0.0f));
    }

    if (abs(ly) > 0.5f) {
        transform = translate(transform, vec3(0.0f, ly / 10, 0.0f));
    }

    float rt = mainJ.axesState(GLFW_JOYSTICK_AXES_RIGHT_TRIGGER)/2 + 0.5;
    if (rt > 0.05f) {
        transform = scale(transform, vec3(1 + rt / 10, 1 + rt / 10, 0.0f));
    }
    float lt = mainJ.axesState(GLFW_JOYSTICK_AXES_LEFT_TRIGGER)/2 + 0.5;
    if (lt > 0.05f) {
        transform = scale(transform, vec3(1 - lt / 10, 1 - lt / 10, 0.0f));
    }*/
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