#ifndef RENDERER_H
#define RENDERER_H

#include <Drawable.h>
#include <Camera.h>
#include <string>
#include <unordered_map>
#include <vector>

class ObjectManager
{
  private:
    std::unordered_map<std::string, Camera> cameras;
    std::vector<Drawable> objects;
    glm::mat4 projMat;
    std::string currentCam;

  public:
    ObjectManager(float fov, float screenRatio, float zNear, float zFar);
    ~ObjectManager();
    void render();
    void update();
    bool setCamera(std::string camName);
    bool addCamera(std::string camName, Camera cam);
    bool removeCamera(std::string camName);
    std::string getCurrentCamera();
};

#endif