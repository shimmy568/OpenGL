#include <Shader.h>
#include <iostream>

Shader::Shader(const char *vertSrc, const char *fragSrc)
{
    //Compile shaders
    Shader::vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Shader::vertShader, 1, &vertSrc, NULL);
    glCompileShader(Shader::vertShader);

    Shader::fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Shader::fragShader, 1, &fragSrc, NULL);
    glCompileShader(Shader::fragShader);

    //Get shader compile status
    GLint status1;
    glGetShaderiv(Shader::vertShader, GL_COMPILE_STATUS, &status1);

    GLint status2;
    glGetShaderiv(Shader::fragShader, GL_COMPILE_STATUS, &status2);

    if (status1 != GL_TRUE || status2 != GL_TRUE)
    {
        std::cout << "shaders failed to compile" << std::endl;
        //Get shader complile log
        int length;
        glGetShaderiv(Shader::vertShader, GL_INFO_LOG_LENGTH, &length);
        char* bufferVert = new char[length];
        glGetShaderInfoLog(Shader::vertShader, 512, NULL, bufferVert);
        std::cout << "Vertex shader comp log: " << bufferVert << std::endl;
        delete bufferVert;

        glGetShaderiv(Shader::fragShader, GL_INFO_LOG_LENGTH, &length);
        char* bufferFrag = new char[length];
        glGetShaderInfoLog(Shader::fragShader, 512, NULL, bufferFrag);
        std::cout << "Fragment shader comp log: " << bufferFrag << std::endl;
        delete bufferFrag;
    }

    //Create shader program
    Shader::shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, Shader::vertShader);
    glAttachShader(shaderProgram, Shader::fragShader);
}

Shader::~Shader()
{
    glDeleteProgram(Shader::shaderProgram);
    glDeleteShader(Shader::vertShader);
    glDeleteShader(Shader::fragShader);
}

GLuint Shader::getGlPointer()
{
    return Shader::shaderProgram;
}