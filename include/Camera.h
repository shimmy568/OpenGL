#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
  private:
    glm::mat4 viewMatrix;

  public:
    Camera();
    ~Camera();

    float camX;
    float camY;
    float camZ;

    float lookX;
    float lookY;
    float lookZ;

    float upX;
    float upY;
    float upZ;

    glm::mat4 getViewMatrix();
    void setCameraPosition(float x, float y, float z);
    void moveCameraPosition(float dX, float dY, float dZ);
    void setLookPosition(float x, float y, float z);
    void moveLookPosition(float dX, float dY, float dZ);

  protected:
};

#endif