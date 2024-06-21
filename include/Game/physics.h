#ifndef PHYSICS_H
#define PHYSICS_H

#include "Game/chunk.h"

using namespace std;

class Physics{
private:
    float velocity = 0.0;
    unordered_map<glm::vec3, int, Hash> voxelsPosition;
public:
    Physics(Chunk &chunk);
    bool AABB(glm::vec3 &position, const glm::vec3 &voxelPosition);
    void collision(glm::vec3 &position);
    void gravity(glm::vec3 &position, float &deltaTime);
    bool is_floating(glm::vec3 &position);
};

Physics::Physics(Chunk &chunk) : voxelsPosition(chunk.voxelsPosition){}

bool Physics::AABB(glm::vec3 &position, const glm::vec3 &voxelPosition){
    return ((position.x+0.5 >= voxelPosition.x && 
             position.x-0.5 <= voxelPosition.x+1) && 
            (position.y+0.5 >= voxelPosition.y && 
             position.y-0.5 <= voxelPosition.y+1) && 
            (position.z+0.5 >= voxelPosition.z && 
             position.z-0.5 <= voxelPosition.z+1));
}

void Physics::collision(glm::vec3 &position){
    for(const auto &it:voxelsPosition){
        if(AABB(position, it.first)){
            float distantX = abs(position.x - it.first.x + 0.5),
                  distantY = abs(position.y - it.first.y + 0.5),
                  distantZ = abs(position.z - it.first.z + 0.5);
            if(distantX > distantY && distantX > distantZ)
                position.x = round(position.x);
            if(distantY > distantX && distantY > distantZ)
                position.y = round(position.y);
            if(distantZ > distantX && distantZ > distantY)
                position.z = round(position.z);
        }
    }
}

void Physics::gravity(glm::vec3 &position, float &deltaTime){
    if(voxelsPosition.find(glm::vec3(round(position.x), position.y-1, round(position.z))) == voxelsPosition.end()){
        int g = 8;
        if(velocity < 25.0)
            velocity += deltaTime * g;
        else
            velocity = 25;
        position.y -= velocity * deltaTime;
    }else
        velocity = 0;
}

bool Physics::is_floating(glm::vec3 &position){
    float x=round(position.x), y=round(position.y), z=round(position.z);
    bool isFloating = false;
    return !AABB(position, glm::vec3(x, y-1, z)) &&
           !AABB(position, glm::vec3(x, y-1, z-1)) &&
           !AABB(position, glm::vec3(x+1, y-1, z-1)) &&
           !AABB(position, glm::vec3(x-1, y-1, z-1)) &&
           !AABB(position, glm::vec3(x+1, y-1, z)) &&
           !AABB(position, glm::vec3(x-1, y-1, z)) &&
           !AABB(position, glm::vec3(x, y-1, z+1)) &&
           !AABB(position, glm::vec3(x-1, y-1, z+1)) &&
           !AABB(position, glm::vec3(x+1, y-1, z+1));
}
#endif