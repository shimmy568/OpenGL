#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <array>
#include <vector>
#include <Shader.h>

class Drawable
{
  private:
    GLuint vertexArrayObject;
    GLuint vertexBufferObject;
    GLuint elementBufferObject;

    float xPosition;
    float yPosition;
    float zPosition;

    float xAngle;
    float yAngle;
    float zAngle;
    
    float xScale;
    float yScale;
    float zScale;

    Shader* shader;

    std::vector<float> formatElementData(std::vector<float> data, std::vector<int>* elements, int step);
    std::vector<float> spliceData(std::vector<float> vectorData, std::vector<float> colorData);
  public:
    Drawable(std::vector<float> vertData, std::vector<float> colorData, Shader* shad);
    ~Drawable();

    std::array<float, 3> getPosition();
    std::array<float, 3> getAngles();
    float getXPosition();
    float getYPosition();
    float getZPosition();
    float getXAngle();
    float getYAngle();
    float getZAngle();
    void clearData();
};

#endif