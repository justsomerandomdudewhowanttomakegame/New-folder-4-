#ifndef HASH_H
#define HASH_H

#include <glm/glm.hpp>
#include <algorithm>

using namespace std;

class Hash{
private:
    hash<int> hasher;
public:
    size_t operator()(const glm::vec3& v) const{
        size_t seed = 0;
        seed ^= hasher((v.x+2)*13 + (v.y+3)*15 + v.z*16) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return ((v.x+2)*13 + (v.y+3)*15 + v.z*16);
    }
};

#endif