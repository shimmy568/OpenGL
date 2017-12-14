#include <Drawable.h>
#include <unordered_map>
#include <string>
#include <stdexcept>

Drawable::Drawable(){
    //Create and bind this objects vertex array
    glGenVertexArrays(1, &(Drawable::vertexArrayObject));
    glBindVertexArray(Drawable::vertexArrayObject);


}

Drawable::~Drawable(){

}

/**
 * Generates the element list of a vertex list that may or may not have dupes in it
 * @author Owen Anderson
 * @throws std::invalid_argument Throws this if the vertexs vector is not in multiples of three or elements is not empty
 *
 * @param vertexs - The list of vertex data that will be formatted 
 * @param elements - An empty vector that the element data will be put into
 * 
 * @returns The new vertex data that only contains unique data points
 */
float* Drawable::formatVertexAndElementData(std::vector<float> vertexs, std::vector<float>* elements){

    //Make sure the input is good
    if(vertexs.size() % 3 != 0){
        throw std::invalid_argument("Vertexs must be provided in multiples of three");
    }
    if(elements->size() != 0){
        throw std::invalid_argument("Elements vector must be empty");
    }

    //Find all unique vertex data points and generate the element list based on that
    std::unordered_map<std::string, int> dupeChecker;
    int curElement = 0;
    std::vector<float> uniqueVertexData;
    for(int i = 0; i < vertexs.size() / 3; i+=3){
        std::string vertKey = std::to_string(vertexs[i]) + "," + std::to_string(vertexs[i + 1]) + "," + std::to_string(vertexs[i + 2]);
        auto res = dupeChecker.find(vertKey);
        if(res == dupeChecker.end()){
            //Vertex is not unique
            (*elements).push_back(res->second);
        } else {
            //Vertex is unique
            dupeChecker.insert({vertKey, curElement});
            (*elements).push_back(curElement);
            uniqueVertexData.push_back(vertexs[i]);
            uniqueVertexData.push_back(vertexs[i + 1]);
            uniqueVertexData.push_back(vertexs[i + 2]);
            curElement++;
        }
    }
    
    //Return an array of the unique vertex data
    return &uniqueVertexData[0];
}