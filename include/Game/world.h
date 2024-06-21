#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"

using namespace std;

class World{
public:
    int renderDistant = 2;
    unordered_map<glm::vec3, Chunk *, Hash> loadedChunk; // store loaded chunk
    vector<float> worldVertexPositions; // store chunks vertices that in render range
    vector<unsigned int> worldIndices; 
    vector<Chunk *> renderChunk; // will be used later
    World();
    ~World();
    void update_world(glm::vec3 &playerPosition);
    void draw_world();

private:
    int indicesPosition;

    unsigned int worldVAO, worldVBO, worldIBO;
    glm::vec3 playerCurrentChunk = glm::vec3(0.0f, -1.0f, 0.0f);
};

World::World(){
    glCreateVertexArrays(1, &worldVAO);
    glCreateBuffers(1, &worldVBO);
    glCreateBuffers(1, &worldIBO);
}

World::~World(){
    glDeleteVertexArrays(1, &worldVAO);
    glDeleteBuffers(1, &worldVBO);
    glDeleteBuffers(1, &worldIBO);
}

void World::update_world(glm::vec3 &playerPosition){
    // if the player still in the same chunk no need to generate more chunk
    if(playerCurrentChunk == glm::vec3(floor(playerPosition.x/16), 0.0f, floor(playerPosition.z/16)))
        return;

    // calculate the current chunk position
    playerCurrentChunk = glm::vec3(floor(playerPosition.x/16), 0.0f, floor(playerPosition.z/16));
    worldVertexPositions.clear();
    worldIndices.clear();
    renderChunk.clear();
    // generate the vertices for each chunk in the render distant
    for(int x=playerCurrentChunk.x-renderDistant; x<=playerCurrentChunk.x+renderDistant; x++){
        for(int z=playerCurrentChunk.z-renderDistant; z<=playerCurrentChunk.z+renderDistant; z++){
            glm::vec3 currentChunk = glm::vec3(static_cast<float>(x), 0.0f, static_cast<float>(z));

            Chunk chunk(currentChunk);
            Chunk *pChunk = &chunk;

            // if the chunk is loaded for the first time add it in the map
            if(loadedChunk.find(currentChunk) == loadedChunk.end()){
                loadedChunk[currentChunk] = &chunk;
                renderChunk.push_back(pChunk);
                worldVertexPositions.insert(worldVertexPositions.end(), pChunk->chunkVertexPositions.begin(), pChunk->chunkVertexPositions.end());
            }else{
                worldVertexPositions.insert(worldVertexPositions.end(), loadedChunk[currentChunk]->chunkVertexPositions.begin(), loadedChunk[currentChunk]->chunkVertexPositions.end());
            }
        }
    }

    // generate the indices( may improve later)
    array<unsigned int, 6> indices = {0, 1, 2, 
                                      2, 3, 0};
    for(int i=0; i<worldVertexPositions.size()/20; i++){
        worldIndices.push_back(indices[0] + i*4);
        worldIndices.push_back(indices[1] + i*4);
        worldIndices.push_back(indices[2] + i*4);
        worldIndices.push_back(indices[3] + i*4);
        worldIndices.push_back(indices[4] + i*4);
        worldIndices.push_back(indices[5] + i*4);
    }

    glNamedBufferData(worldVBO, worldVertexPositions.size()*sizeof(float), &worldVertexPositions[0], GL_STATIC_DRAW);
    glNamedBufferData(worldIBO, worldIndices.size()*sizeof(unsigned int), &worldIndices[0], GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(worldVAO, 0);
    glVertexArrayAttribBinding(worldVAO, 0, 0);
    glVertexArrayAttribFormat(worldVAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(worldVAO, 1);
    glVertexArrayAttribBinding(worldVAO, 1, 0);
    glVertexArrayAttribFormat(worldVAO, 1, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float));

    glVertexArrayVertexBuffer(worldVAO, 0, worldVBO, 0, 5*sizeof(float));
    glVertexArrayElementBuffer(worldVAO, worldIBO);

}

void World::draw_world(){
    glBindVertexArray(worldVAO);
    glDrawElements(GL_TRIANGLES, worldIndices.size(), GL_UNSIGNED_INT, 0);
}
#endif