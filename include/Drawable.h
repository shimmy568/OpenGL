#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <array>
#include <vector>

class Drawable
{
  private:
    GLuint vertexArrayObject;
    GLuint vertexBufferArrayVertex;
    GLuint vertexBufferArrayColor;
    GLuint elementBufferArrayVertex;
    GLuint elementBufferArrayColor;

    float xPosition;
    float yPosition;
    float zPosition;

    float xAngle;
    float yAngle;
    float zAngle;
    
    float xScale;
    float yScale;
    float zScale;

    std::vector<float> formatElementData(std::vector<float> data, std::vector<int>* elements, int step);
  public:
    Drawable(std::vector<float> vertData, std::vector<float> colorData);
    ~Drawable();

    std::array<float, 3> getPosition();
    std::array<float, 3> getAngles();
    float getXPosition();
    float getYPosition();
    float getZPosition();
    float getXAngle();
    float getYAngle();
    float getZAngle();
};

#endif