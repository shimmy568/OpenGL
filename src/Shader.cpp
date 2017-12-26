#include <Shader.h>
#include <iostream>

/**
 * Compiles and links a shader program using a vertex and fragment shader program.
 * @author Owen Anderson
 */
Shader::Shader(const char *vertSrc, const char *fragSrc)
{
    // Compile shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    // Get shader compile status
    GLint status1;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status1);

    GLint status2;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status2);

    if (status1 != GL_TRUE || status2 != GL_TRUE)
    {
        std::cout << "shaders failed to compile" << std::endl;
        // Get shader complile log
        int length;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
        char *bufferVert = new char[length];
        glGetShaderInfoLog(vertShader, 512, NULL, bufferVert);
        std::cout << "Vertex shader comp log: " << bufferVert << std::endl;
        delete bufferVert;

        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
        char *bufferFrag = new char[length];
        glGetShaderInfoLog(fragShader, 512, NULL, bufferFrag);
        std::cout << "Fragment shader comp log: " << bufferFrag << std::endl;
        delete bufferFrag;
    }

    // Create shader program
    Shader::shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    // Link shader program
    glLinkProgram(Shader::shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

/**
 * Function that clears the shader program from memory
 * @author Owen Anderson
 */
void Shader::clearShaderProgram()
{
    glDeleteProgram(Shader::shaderProgram);
}

/**
 * The default destructor for the shader class, automaticly calls clearShaderProgram
 * @author Owen Anderson
 */
Shader::~Shader()
{
    Shader::clearShaderProgram();
}

/**
 * Gets the GL pointer to the shader program that this object represents
 * @author Owen Anderson
 * 
 * @returns GLuint - The pointer to the shader program in OpenGL
 */
GLuint Shader::getGlPointer()
{
    return Shader::shaderProgram;
}