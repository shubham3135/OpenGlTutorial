#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
string loadShaderSrc(const char* fileName);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /*
        shaders
    */

    // compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    string vertShaderSrc = loadShaderSrc("assets/vertex_core.glsl");
    const GLchar* vertShader = vertShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    //catch error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Error with vert shader comp. : " << endl << infoLog << endl;
    }

    //compile fragment shader
    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    string fragShaderSrc = loadShaderSrc("assets/fragment_core.glsl");
    const GLchar* fragShader = fragShaderSrc.c_str();
    glShaderSource(fragmentShader[0], 1, &fragShader, NULL);
    glCompileShader(fragmentShader[0]);

    //catch error
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
        cout << "Error with frag shader comp. : " << endl << infoLog << endl;
    }

    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    fragShaderSrc = loadShaderSrc("assets/fragment_core2.glsl");
    fragShader = fragShaderSrc.c_str();
    glShaderSource(fragmentShader[1], 1, &fragShader, NULL);
    glCompileShader(fragmentShader[1]);

    //catch error
    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
        cout << "Error with frag shader comp. : " << endl << infoLog << endl;
    }

    //create program
    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();

    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    glLinkProgram(shaderProgram[0]);

    //catch error
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram[0], 512, NULL, infoLog);
        cout << "Error with shader program comp. : " << endl << infoLog << endl;
    }

    //shaderProgram[1] = glCreateProgram();

    //glAttachShader(shaderProgram[1], vertexShader);
    //glAttachShader(shaderProgram[1], fragmentShader[1]);
    //glLinkProgram(shaderProgram[1]);

    ////catch error
    //glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(shaderProgram[1], 512, NULL, infoLog);
    //    cout << "Error with shader program comp. : " << endl << infoLog << endl;
    //}

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);
    //glDeleteShader(fragmentShader[1]);

    //vertex array
    /*float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };*/
    float vertices[] = {
        //positions               colors      
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.5f,
        -0.5f,  0.5f, 0.0f,     0.5f, 1.0f, 0.75f,
        -0.5f, -0.5f, 0.0f,     0.6f, 1.0f, 0.2f,
         0.5f, -0.5f, 0.0f,     1.0f, 0.2f, 1.0f
    };

    unsigned indices[] = {
        0, 1, 2, // first tirangle
        2, 3, 0 // second triangle
    };

    //VAO & VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //bind VAO
    glBindVertexArray(VAO);

    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //set attribute pointer
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    mat4 trans = mat4(1.0f);
    trans = rotate(trans, radians(45.0f), vec3(0.0f, 0.0f, 1.0f));
    glUseProgram(shaderProgram[0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram[0], "transform"), 1, GL_FALSE, value_ptr(trans));

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
        glClear(GL_COLOR_BUFFER_BIT);


        trans = rotate(trans, radians((float) glfwGetTime() / 1000.0f), vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram[0], "transform"), 1, GL_FALSE, value_ptr(trans));

        // draw shapes
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram[0]);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

string loadShaderSrc(const char* fileName) {
    ifstream file;
    stringstream buf;
    string ret = "";

    file.open(fileName);
    if (file.is_open()) {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else {
        cout << "Could not open " << fileName << endl;
    }
    file.close();
    return ret;
}