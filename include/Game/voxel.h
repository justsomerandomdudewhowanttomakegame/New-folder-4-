#ifndef VOXEL_H
#define VOXEL_H

#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <unordered_map>
using namespace std;

enum voxelFace{
     Front,
     Top,
     Bottom,
     Right,
     Left,
     Back
};

unordered_map<voxelFace, array<float, 20>> faceVertices = {
     {voxelFace::Front, {1.0f,  1.0f,  1.0f,    1.0f, 1.0f,
                         1.0f,  0.0f,  1.0f,    1.0f, 0.0f,
                         0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
                         0.0f,  1.0f,  1.0f,    0.0f, 1.0f}
     }, 
          
     {voxelFace::Top,   {1.0f,  1.0f,  0.0f,    1.0f, 1.0f,
                         1.0f,  1.0f,  1.0f,    1.0f, 0.0f,
                         0.0f,  1.0f,  1.0f,    0.0f, 0.0f,
                         0.0f,  1.0f,  0.0f,    0.0f, 1.0f}
     },   
   
     {voxelFace::Bottom,{0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
                         1.0f,  0.0f,  1.0f,    1.0f, 0.0f,
                         1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                         0.0f,  0.0f,  0.0f,    0.0f, 1.0f}  
     },   
   
     {voxelFace::Right, {1.0f,  1.0f,  1.0f,    1.0f, 1.0f,
                         1.0f,  1.0f,  0.0f,    1.0f, 0.0f,
                         1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                         1.0f,  0.0f,  1.0f,    0.0f, 1.0f}
     },   
   
     {voxelFace::Left,  {0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
                         0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
                         0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
                         0.0f,  1.0f,  1.0f,    0.0f, 1.0f} 
     },   
   
     {voxelFace::Back,  {1.0f,  1.0f,  0.0f,    1.0f, 1.0f,
                         0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
                         0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
                         1.0f,  0.0f,  0.0f,    0.0f, 1.0f} 
     }
};

#endif