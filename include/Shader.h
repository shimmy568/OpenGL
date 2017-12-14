#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
  private:
    GLuint shaderProgram;

  public:
    Shader(const char *vertSrc, const char *fragSrc);
    ~Shader();
    void clearShaderProgram();

    GLuint getGlPointer();
};

#endif