#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <chrono>

#include <Shader.h>

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

    //Vertex array object (look into how these work)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Create vertex data
    float vertices[] = {
        -0.5f,  0.5f, 0.5f, //TopLeft
         0.5f,  0.5f, 0.0f, //TopRight
         0.5f, -0.5f, 0.5f, //BottomRight
        -0.5f, -0.5f, 1.0f, //BottomLeft
        };

    //Send the vertex data to the gpu
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elements[] = {
        0, 1, 2,
        0, 3, 2
    };

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    //Load shader src
    const char* vertShaderSrc =
#include "shad.vert"
        ;

    const char* fragShaderSrc =
#include "shad.frag"
        ;

    Shader* basicShader = new Shader(vertShaderSrc, fragShaderSrc);
    
    //Set shader output
    glBindFragDataLocation(basicShader->getGlPointer(), 0, "outColor");

    //Set the active shader
    glLinkProgram(basicShader->getGlPointer());
    glUseProgram(basicShader->getGlPointer());

    //Configure how the shader reads from the vertex buffer
    //Position info
    GLint posAttrib = glGetAttribLocation(basicShader->getGlPointer(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

    //Color info
    GLint colAttrib = glGetAttribLocation(basicShader->getGlPointer(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(2*sizeof(float)));

    while (!glfwWindowShouldClose(window))
    {

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Shit go here
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    delete basicShader;

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
    return 0;
}