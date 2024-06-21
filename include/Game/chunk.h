#ifndef CHUNK_H
#define CHUNK_H
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game/PerlinNoise.hpp"
#include "Game/voxel.h"
#include "Game/shaders.h"
#include "Game/hash.h"

#include <functional>
#include <vector>
#include <unordered_map>

using namespace std;

class Chunk{
public:
    unordered_map<glm::vec3, int, Hash> voxelsPosition;
    vector<float> chunkVertexPositions;
    vector<unsigned int> chunkIndices;

    int indexCounter;
    int indicesPosition;

    Chunk(const glm::vec3 &chunkPosition);
    ~Chunk();

    void update_mesh();
    void draw_chunk();  

private:

    int chunkX = 16;
    int chunkY = 16;
    int chunkZ = 16;

    unsigned int chunkVAO, chunkVBO, chunkIBO;
    glm::vec3 chunkPosition;

    siv::PerlinNoise::seed_type seed = 140608u;
    siv::PerlinNoise perlin{seed};

    bool is_air(const glm::vec3 &position);
    void add_face(voxelFace face, float x, float y, float z);
};

Chunk::Chunk(const glm::vec3 &chunkPosition) : chunkPosition(chunkPosition.x, chunkPosition.y, chunkPosition.z){
    //create all the coord that have voxel
    for (int i = chunkPosition.x*chunkX; i < chunkPosition.x*chunkX+chunkX; i++){
        for (int k = chunkPosition.z*chunkZ; k < chunkPosition.z*chunkZ+chunkZ; k++){
            voxelsPosition[glm::vec3(static_cast<float>(i), round(chunkY * perlin.octave2D_11((float)i*0.01, (float)k*0.01, 8)), static_cast<float>(k))] = 0;
        }
    }
    /*glCreateVertexArrays(1, &chunkVAO);
    glCreateBuffers(1, &chunkVBO);
    glCreateBuffers(1, &chunkIBO);*/

    update_mesh();
}

Chunk::~Chunk(){
    /*glDeleteVertexArrays(1, &chunkVAO);
    glDeleteBuffers(1, &chunkVBO);
    glDeleteBuffers(1, &chunkIBO);*/
    chunkVertexPositions.clear();
    chunkIndices.clear();
    voxelsPosition.clear();
}

//check is neighbour voxel is air or not
bool Chunk::is_air(const glm::vec3 &position){
    if(voxelsPosition.find(position) == voxelsPosition.end())
        return true;
    return false;
}

//gen the vertices for the face
void Chunk::add_face(voxelFace face, float x, float y, float z){
    for(int i=0; i<4; i++){
        chunkVertexPositions.push_back(faceVertices[face][i*5 + 0] + x);
        chunkVertexPositions.push_back(faceVertices[face][i*5 + 1] + y);
        chunkVertexPositions.push_back(faceVertices[face][i*5 + 2] + z);
        chunkVertexPositions.push_back(faceVertices[face][i*5 + 3]);
        chunkVertexPositions.push_back(faceVertices[face][i*5 + 4]);
    }

    array<unsigned int, 6> indices = {0, 1, 2, 
                                      2, 3, 0};
    for(int i=0; i<6; i++)
        chunkIndices.push_back(indices[i] + indexCounter/* + indicesPosition*/);
    indexCounter += 4;
}  
//create the mesh
void Chunk::update_mesh(){
    for(auto &it:voxelsPosition){
        float x = it.first.x, y = it.first.y, z = it.first.z;

        if(is_air(glm::vec3(x, y, z+1)))
            add_face(Front, x, y, z);
        if(is_air(glm::vec3(x, y+1, z)))
            add_face(Top, x, y, z);
        if(is_air(glm::vec3(x, y-1, z)))
            add_face(Bottom, x, y, z);
        if(is_air(glm::vec3(x+1, y, z)))
            add_face(Right, x, y, z);
        if(is_air(glm::vec3(x-1, y, z)))
            add_face(Left, x, y, z);
        if(is_air(glm::vec3(x, y, z-1)))
            add_face(Back, x, y, z);
    }

    /*glNamedBufferData(chunkVBO, chunkVertexPositions.size()*sizeof(float), &chunkVertexPositions[0], GL_STATIC_DRAW);
    glNamedBufferData(chunkIBO, chunkIndices.size()*sizeof(unsigned int), &chunkIndices[0], GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(chunkVAO, 0);
    glVertexArrayAttribBinding(chunkVAO, 0, 0);
    glVertexArrayAttribFormat(chunkVAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(chunkVAO, 1);
    glVertexArrayAttribBinding(chunkVAO, 1, 0);
    glVertexArrayAttribFormat(chunkVAO, 1, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float));

    glVertexArrayVertexBuffer(chunkVAO, 0, chunkVBO, 0, 5*sizeof(float));
    glVertexArrayElementBuffer(chunkVAO, chunkIBO);*/
}

void Chunk::draw_chunk(){
    glBindVertexArray(chunkVAO);
    glDrawElements(GL_TRIANGLES, chunkIndices.size(), GL_UNSIGNED_INT, 0);
}
#endif