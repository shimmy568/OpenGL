#include <ObjectManager.h>
#include <Camera.h>
#include <string>
#include <unordered_map>
#include <vector>

ObjectManager::ObjectManager(float fov, float screenRatio, float zNear, float zFar)
{
    ObjectManager::projMat = glm::perspective(glm::radians(fov), screenRatio, zNear, zFar);

    // Create default camera
    Camera cam;
    ObjectManager::currentCam = "default";
    ObjectManager::cameras.insert({"default", cam});
}

ObjectManager::~ObjectManager()
{
    // Currently empty use if needed
}

void ObjectManager::render()
{
    auto res = ObjectManager::cameras.find(ObjectManager::currentCam);
    Camera currentCam = res->second;
    for (int i = 0; i < ObjectManager::objects.size(); i++)
    {
        ObjectManager::objects[i].draw(currentCam.getViewMatrix(), ObjectManager::projMat);
    }
}

void ObjectManager::update()
{
    // TODO
}

bool ObjectManager::addCamera(std::string camName, Camera cam)
{
    // Check if the camera has been added to list allready
    auto res = ObjectManager::cameras.find(camName);
    if (res == ObjectManager::cameras.end())
    {
        return false; // If it has return false
    }

    // If it has not add it and return true
    ObjectManager::cameras.insert({camName, cam});
    return true;
}

std::string ObjectManager::getCurrentCamera()
{
    return ObjectManager::currentCam;
}

bool ObjectManager::setCamera(std::string camName)
{
    // Check if the camera exsits and if it is not don't set it
    auto res = ObjectManager::cameras.find(camName);
    if (res == ObjectManager::cameras.end())
    {
        return false;
    }

    // If it is in the camera hash map than set it to be the current camera
    ObjectManager::currentCam = camName;
    return true;
}

bool ObjectManager::removeCamera(std::string camName)
{
    // Check if the camera is in the hash map and if it is not dont remove
    auto res = ObjectManager::cameras.find(camName);
    if (res == ObjectManager::cameras.end())
    {
        return false; // return false
    }

    // If it is in the hash map remove it
}