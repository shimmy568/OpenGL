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
    std::unordered_map<std::string, Camera*> cameras;
    std::unordered_map<int, Drawable*> objects;
    glm::mat4 projMat;
    std::string currentCam;

    int generateNewObjectID();

  public:
    ObjectManager(float fov, float screenRatio, float zNear, float zFar);
    ~ObjectManager();
    void render();
    void update();

    //Camera management
    bool setCamera(std::string camName);
    bool addCamera(std::string camName, Camera* cam);
    bool removeCamera(std::string camName);
    Camera* getCamera(std::string camName);
    Camera* getCurrentCamera();
    std::string getCurrentCameraName();

    //Object management
    int addObject(Drawable* obj);
    bool removeObject(int id);
    Drawable* getObject(int id);
};

#endif