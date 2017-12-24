#include <Drawable.h>
#include <unordered_map>
#include <string>
#include <array>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Drawable::Drawable(std::vector<float> vertData, std::vector<float> colorData, Shader *shad)
{
    Drawable::shader = shad;

    //Splice all the data into one vector(array)
    std::vector<float> splicedData = Drawable::spliceData(vertData, colorData);

    //Generate element data
    std::vector<int> elementData;
    std::vector<float> uniqueData = Drawable::formatElementData(splicedData, &elementData, 6);

    for(int i = 0; i < splicedData.size(); i++){
        if((i + 1) % 6 == 0){
            std::cout << splicedData[i] << std::endl;
        }else{
            std::cout << splicedData[i] << " ";
        }
    }

    for(int i = 0; i < uniqueData.size(); i++){
        if((i + 1) % 6 == 0){
            std::cout << uniqueData[i] << std::endl;
        }else{
            std::cout << uniqueData[i] << " ";
        }
    }

    for(int i = 0; i < elementData.size(); i++){
        std::cout << elementData[i] << std::endl;
    }

    //set element count
    Drawable::elementCount = elementData.size();

    //Create and bind this objects vertex array
    glGenVertexArrays(1, &(Drawable::vertexArrayObject));
    glBindVertexArray(Drawable::vertexArrayObject);

    //Load vbo and element data
    glGenBuffers(1, &(Drawable::vertexBufferObject));
    glGenBuffers(1, &(Drawable::elementBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, Drawable::vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uniqueData.size(), &uniqueData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Drawable::elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * elementData.size(), &elementData[0], GL_STATIC_DRAW);

    //Set vao
    glGenVertexArrays(1, &(Drawable::vertexArrayObject));
    glBindVertexArray(Drawable::vertexArrayObject);

    //Setup shader program
    GLint posAttrib = glGetAttribLocation(Drawable::shader->getGlPointer(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    GLint colorAttrib = glGetAttribLocation(Drawable::shader->getGlPointer(), "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    //Clear vao
    glBindVertexArray(0);
}

void Drawable::clearData()
{

    //Delete(invalidates) the vertex buffers used for this object
    glInvalidateBufferData(Drawable::vertexBufferObject);
    glInvalidateBufferData(Drawable::elementBufferObject);

    //Delete the vertex array for this object
    glDeleteVertexArrays(1, &(Drawable::vertexArrayObject));
}

Drawable::~Drawable()
{
    Drawable::clearData();
}

void Drawable::draw()
{
    //Use shader
    glUseProgram(Drawable::shader->getGlPointer());

    //bind vertex object
    glBindVertexArray(Drawable::vertexArrayObject);

    //bind buffers
    glBindBuffer(GL_ARRAY_BUFFER, Drawable::vertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Drawable::elementBufferObject);

    // Set up projection
    glm::mat4 view = glm::lookAt(
        glm::vec3(1.2f, 1.2f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));
    GLint uniView = glGetUniformLocation(Drawable::shader->getGlPointer(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(Drawable::shader->getGlPointer(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint uniModel = glGetUniformLocation(Drawable::shader->getGlPointer(), "model");

    glm::mat4 model;
    model = glm::rotate(
        model,
        glm::radians(Drawable::zAngle),
        glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << std::hex << err << std::endl;
    }

    //draw object
    glDrawElements(GL_TRIANGLES, Drawable::elementCount, GL_UNSIGNED_INT, 0);
}

std::vector<float> Drawable::spliceData(std::vector<float> vectorData, std::vector<float> colorData)
{
    //Verify that the number or points in each data is the same
    if (vectorData.size() / 3 != colorData.size() / 3)
    {
        throw std::invalid_argument("The vector data must have the same number of points");
    }

    std::vector<float> splicedData;
    for (int i = 0; i < vectorData.size() / 3; i++)
    {
        //Add vertex data for the point
        for (int o = 0; o < 3; o++)
        {
            splicedData.push_back(vectorData[i * 3 + o]);
        }

        //Add color data for the point
        for (int o = 0; o < 3; o++)
        {
            splicedData.push_back(colorData[i * 3 + o]);
        }
    }

    return splicedData;
}

/**
 * Generates the element list for a data list. This is the preprocessing stage for using the element buffers
 * for drawing instead of just the entire raw vertex data.
 * @author Owen Anderson
 * @throws std::invalid_argument Throws this if the vertexs vector is not in multiples of three or elements is not empty
 *
 * @param vertexs - The list of vertex data that will be formatted 
 * @param elements - A pointer to an empty vector that the element data will be put into
 * 
 * @returns The new vertex data that only contains unique data points
 */
std::vector<float> Drawable::formatElementData(std::vector<float> data, std::vector<int> *elements, int step)
{
    //Make sure the input is good
    if (data.size() % step != 0)
    {
        throw std::invalid_argument("Vertexs must be provided in multiples of the step");
    }
    if (elements->size() != 0)
    {
        throw std::invalid_argument("Elements vector must be empty");
    }

    //Find all unique vertex data points and generate the element list based on that
    std::unordered_map<std::string, int> dupeChecker;
    int curElement = 0;
    std::vector<float> uniqueVertexData;
    for (int i = 0; i < data.size(); i += step)
    {
        std::string vertKey = std::to_string(data[i]);
        for (int o = 1; o < step; o++)
        {
            vertKey += "," + std::to_string(data[i + o]);
        }
        auto res = dupeChecker.find(vertKey);
        if (res != dupeChecker.end())
        {
            //Vertex is not unique use the exsiting element value
            elements->push_back(res->second);
        }
        else
        {
            //Vertex is unique add to unique list and increment the element value
            dupeChecker.insert({vertKey, curElement});
            elements->push_back(curElement);
            for (int o = 0; o < step; o++)
            {
                uniqueVertexData.push_back(data[i + o]);
            }
            curElement++;
        }
    }

    //Return an array of the unique vertex data
    return uniqueVertexData;
}