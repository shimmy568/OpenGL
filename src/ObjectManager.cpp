#include <ObjectManager.h>
#include <Camera.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdlib>

ObjectManager::ObjectManager(float fov, float screenRatio, float zNear, float zFar)
{
    ObjectManager::projMat = glm::perspective(glm::radians(fov), screenRatio, zNear, zFar);

    // Create default camera
    Camera cam;
    ObjectManager::currentCam = "default";
    ObjectManager::cameras.insert({"default", &cam});
}

ObjectManager::~ObjectManager()
{
    // Currently empty use if needed
}

void ObjectManager::render()
{
    auto res = ObjectManager::cameras.find(ObjectManager::currentCam);
    Camera *currentCam = res->second;
    for (int i = 0; i < ObjectManager::objects.size(); i++)
    {
        ObjectManager::objects[i].draw(currentCam->getViewMatrix(), ObjectManager::projMat);
    }
}

void ObjectManager::update()
{
    // TODO
}

bool ObjectManager::addCamera(std::string camName, Camera *cam)
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

std::string ObjectManager::getCurrentCameraName()
{
    return ObjectManager::currentCam;
}

/**
 * Gives the current camera
 */
Camera *ObjectManager::getCurrentCamera()
{
    //Based on other functions current cam will point to a position in the hashmap that is filled
    return ObjectManager::cameras.at(ObjectManager::currentCam);
}

/**
 * Gets a pointer to any camera in the object manager based on name
 * 
 * @returns - The pointer to that camera
 */
Camera *ObjectManager::getCamera(std::string camName)
{
    auto res = ObjectManager::cameras.find(camName);
    if (res == ObjectManager::cameras.end())
    {
        return nullptr;
    }
    return res->second;
}

/**
 * Sets the current camera
 * 
 * @returns - Weather or not is was able to set
 */
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
    ObjectManager::cameras.erase(camName);
    return true;
}

/**
 * Generate a new ID that has not been used in the object list before
 * 
 * @returns - The new ID
 */
int ObjectManager::generateNewObjectID()
{
    int num;
    bool unique = false;
    while (!unique)
    {
        num = rand();
        auto res = ObjectManager::objects.find(num);
        if (res == ObjectManager::objects.end())
        {
            unique = true;
        }
    }
    return num;
}

int ObjectManager::addObject(Drawable *obj)
{
    //Get a unique object ID
    int id = ObjectManager::generateNewObjectID();

    //Insert the object into the object list using the new id
    ObjectManager::objects.insert({id, obj});

    return id;
}

/**
 * Removes an object from the object list given an id
 * 
 * @returns - Weather or not it was found in the list
 */
bool ObjectManager::removeObject(int id)
{
    //Check if object is in list. If it is not return false
    auto res = ObjectManager::objects.find(id);
    if (res == ObjectManager::objects.end())
    {
        return false;
    }

    //Remove the object
    ObjectManager::objects.erase(id);
    return true;
}

/**
 * Gets an object from the object list given an ID
 * 
 * @returns - The object, nullptr if it wasn't found
 */
Drawable* ObjectManager::getObject(int id)
{
    auto res = ObjectManager::objects.find(id);
    if(res == ObjectManager::objects.end()){
        return nullptr;
    }

    return res->second;
}