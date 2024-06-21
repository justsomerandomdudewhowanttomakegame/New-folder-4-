#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "shaders.h"

using namespace std;

float hitBoxVertices[] = {
    1.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
        
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  0.0f,
    
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  1.0f,  
    
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  1.0f,
    
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  1.0f, 
    
    1.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f   
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    8, 9, 10,
    10, 11, 8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20 
};

class Entity{
private:
    unsigned int hitBoxVAO, hitBoxVBO, hitBoxIBO;
public:
    Entity(float &x, float &y, float &z);

    void update_hitbox(float &x ,float &y, float &z);
    void draw_hitbox(Shader &shader);
};

Entity::Entity(float &x, float &y, float &z){
    glGenVertexArrays(1, &hitBoxVAO);
    glGenBuffers(1, &hitBoxVBO);
    glGenBuffers(1, &hitBoxIBO);
    update_hitbox(x ,y, z);
}

void Entity::update_hitbox(float &x ,float &y, float &z){
    for(int i=0; i<11; i++){
        hitBoxVertices[i*3] += x;
        hitBoxVertices[i*3+1] += y;
        hitBoxVertices[i*3+2] += z;
    }

    glBindVertexArray(hitBoxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, hitBoxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hitBoxVertices), hitBoxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hitBoxIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
} 

void Entity::draw_hitbox(Shader &ourShader){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f ,0.0f, 0.0f));
    ourShader.setMat4("model", model);

    glBindVertexArray(hitBoxVAO);
    glDrawElements(GL_LINE, 36, GL_UNSIGNED_INT, 0);
}