#ifndef HIT_HPP
#define HIT_HPP

#include "vector3.hpp"
#include "material.hpp"

struct Hit{
    bool hit;
    float distance;
    vector3 hitPoint;
    vector3 hitNormal;
    material mat;
};

#endif