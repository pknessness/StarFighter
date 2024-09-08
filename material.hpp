#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "vector3.hpp"

struct material{
    vector3 color;
    float gloss;
    float emissivity;
};

#endif