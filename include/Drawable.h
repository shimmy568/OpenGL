#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <array>
#include <vector>

class Drawable
{
  private:
    GLuint vertexArrayObject;
    GLuint vertexBufferArray;
    GLuint elementBufferArray;

    float xPosition;
    float yPosition;
    float zPosition;

    float xAngle;
    float yAngle;
    float zAngle;
    
    float xScale;
    float yScale;
    float zScale;

    std::vector<float> formatVertexAndElementData(std::vector<float> vertexs, std::vector<int>* elements);
  public:
    Drawable(std::vector<float> vecData);
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