#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "vector3.hpp"

struct location {
    vector3 pos;
    vector3 fwdVector;
    vector3 rightVector;
};

#endif