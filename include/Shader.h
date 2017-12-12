#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
  private:
    GLuint vertShader;
    GLuint fragShader;
    GLuint shaderProgram;

  public:
    Shader(const char *vertSrc, const char *fragSrc);
    ~Shader();

    GLuint getGlPointer();
};

#endif