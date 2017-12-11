#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <chrono>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

    glfwMakeContextCurrent(window);

    

    glewExperimental = GL_TRUE;
    glewInit();

    //Create vertex data
    float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f};

    //Send the vertex data to the gpu
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Load shader src
    const char* vertShaderSrc =
#include "shad.vert"
        ;

    const char* fragShaderSrc =
#include "shad.frag"
        ;

    //Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragmentShader);

    //Get shader compile status
    GLint status1;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status1);

    GLint status2;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);
    
    if(status1 == GL_TRUE && status2 == GL_TRUE){
        std::cout << "shader compiled good" << std::endl;
    }

    //Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //Set shader output
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    //Set the active shader
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    //Set color via uniform
    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

    //Vertex array object (look into how these work)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Configure how the shader reads from the vertex buffer
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
    auto t_start = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        //Change triangle color with time

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        glUniform3f(uniColor, (sin(time * 3.0f) + 1.0f) / 2.0f, (sin(time * 2.0f) + 1.0f) / 2.0f, (sin(time * 5.0f) + 1.0f) / 2.0f);
        

        //Shit go here
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    glfwTerminate();
    return 0;
}