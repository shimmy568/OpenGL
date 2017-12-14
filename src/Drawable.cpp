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
 */
bool Drawable::formatVertexAndElementData(std::vector<float>* vertexs, std::vector<float>* elements){
    if(vertexs->size() % 3 != 0){
        throw std::invalid_argument("Vertexs must be provided in multiples of three");
    }
    if(elements->size() != 0){
        throw std::invalid_argument("Elements vector must be empty");
    }
    std::unordered_map<std::string, bool> dupeChecker;

    for(int i = 0; i < vertexs->size(); i++){
        
    }
}