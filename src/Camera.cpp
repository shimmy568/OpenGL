#include <Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

/**
 * Sets the position that the cameara is located at
 * 
 * @param x - The x position of the camera
 * @param y - The y position of the camera
 * @param z - The z position of the camera
 */
void Camera::setCameraPosition(float x, float y, float z)
{
    Camera::camX = x;
    Camera::camY = y;
    Camera::camZ = z;
}

/**
 * Moves the position of the camera
 * 
 * @param dX - How much to move the camera by in the x direction
 * @param dY - How much to move the camera by in the y direction
 * @param dZ - How much to move the camera by in the z direction
 */
void Camera::moveCameraPosition(float dX, float dY, float dZ)
{
    Camera::camX += dX;
    Camera::camY += dY;
    Camera::camZ += dZ;
}

/**
 * Sets at what point the camera is looking at
 * 
 * @param x - The x position that the camera is looking at
 * @param y - The y position that the camera is looking at
 * @param z - The z position that the camera is looking at
 */
void Camera::setLookPosition(float x, float y, float z) {
    Camera::lookX = x;
    Camera::lookY = y;
    Camera::lookZ = z;
}

/**
 * Moves the position that the camera looks at
 * 
 * @param dX - How much to move the point the camera is looking at on the x axis
 * @param dY - How much to move the point the camera is looking at on the y axis
 * @param dZ - How much to move the point the camera is looking at on the z axis
 */
void Camera::moveLookPosition(float dX, float dY, float dZ){
    Camera::lookX += dX;
    Camera::lookY += dY;
    Camera::lookZ += dZ;
}