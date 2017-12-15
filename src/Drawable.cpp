#include <Drawable.h>
#include <unordered_map>
#include <string>
#include <array>
#include <vector>
#include <stdexcept>
#include <iostream>

Drawable::Drawable(std::vector<float> vertData, std::vector<float> colorData){
    //Create and bind this objects vertex array
    //glGenVertexArrays(1, &(Drawable::vertexArrayObject));
    //glBindVertexArray(Drawable::vertexArrayObject);

    //Generate unique data and element data
    std::vector<int> vertElementData;
    std::vector<float> uniqueVertexData = Drawable::formatElementData(vertData, &vertElementData, 3);

    std::vector<int> colorElementData;
    std::vector<float> uniqueColorData = Drawable::formatElementData(colorData, &colorElementData, 3);

}

Drawable::~Drawable(){

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
std::vector<float> Drawable::formatElementData(std::vector<float> data, std::vector<int>* elements, int step){

    //Make sure the input is good
    if(data.size() % step != 0){
        throw std::invalid_argument("Vertexs must be provided in multiples of the step");
    }
    if(elements->size() != 0){
        throw std::invalid_argument("Elements vector must be empty");
    }

    //Find all unique vertex data points and generate the element list based on that
    std::unordered_map<std::string, int> dupeChecker;
    int curElement = 0;
    std::vector<float> uniqueVertexData;
    for(int i = 0; i < data.size(); i+=step){
        std::string vertKey = std::to_string(data[i]) + "," + std::to_string(data[i + 1]) + "," + std::to_string(data[i + 2]);
        for(int o = 1; o < step; o++){
            vertKey += "," + std::to_string(data[i + step]);
        }
        auto res = dupeChecker.find(vertKey);
        if(res != dupeChecker.end()){
            //Vertex is not unique use the exsiting element value
            elements->push_back(res->second);
        } else {
            //Vertex is unique add to unique list and increment the element value
            dupeChecker.insert({vertKey, curElement});
            elements->push_back(curElement);
            for(int o = 0; o < step; o++){
                uniqueVertexData.push_back(data[i + o]);
            }
            curElement++;
        }
    }

    //Return an array of the unique vertex data
    return uniqueVertexData;
}