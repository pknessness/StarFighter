#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

extern "C" {
    #include "raylib5\include\raylib.h"
}

#include <stdint.h>
#include "vector3.hpp"\

uint32_t ra = 124;

int maxHemiTries = 20;
int countSeed = 0;

Color color(float r, float g, float b, float a = 1.0){
    return (Color){(uint8_t)(r*255),(uint8_t)(g*255),(uint8_t)(b*255),(uint8_t)(a*255)};
}

Color color(vector3 color, float a = 1.0){
    return (Color){(uint8_t)(color.x*255),(uint8_t)(color.y*255),(uint8_t)(color.z*255),(uint8_t)(a*255)};
}

vector3 skybox(const ray& r){
    vector3 unit_direction = (r.dir).norm();
    auto a = 0.5*(unit_direction.y + 1.0);
    return {1.0-a + 0.5*a, 1.0-a + 0.7*a, 1.0-a + 1.0*a};// + color(0.5*a, 0.7*a, 1.0*a);
}

float randomSeeded(){
    long val = (countSeed*(countSeed*2140 + 21390) * (countSeed * 2139021 + 213908))>>8 & 0xFFFFFF;
    // printf("{%f %d}\n",(float)val/0xFFFFFF, countSeed);
    countSeed ++;
    // countSeed = val;
    return (float)val/0xFFFFFF;
}

float randomCont(){
    ra = (ra*(ra*2140 + 21390) * (ra * 2139021 + 213908))>>8 & 0xFFFFFF;
    return (float)ra/0xFFFFFF;
}

// uint8_t randomColor(int x, int y, int a){
//     int in = (x * screenWidth + y) * (a+434);
//     long val = (in*(in*2140 + 21390) * (in * 2139021 + 213908)) & 0xFFFFFF;
//     // printf("in:%d val:%d\n", in, val);
//     return val >> 16;
// }

vector3 randomVector(){
    vector3 v = {0,0,0};
    for(int i = 0; i < maxHemiTries; i ++){
        v = vector3{(randomCont()*2 - 1.0), (randomCont()*2 - 1.0), (randomCont()*2 - 1.0)};
        // printf("{%f %f %f}\n", v.x,v.y,v.z);
        if(v.mag2() < 1.0){
            return v.norm();
        }
    }
    return {0,0,0};
}

vector3 randomVectorSeeded(){
    vector3 v = {0,0,0};
    for(int i = 0; i < maxHemiTries; i ++){
        v = vector3{(randomSeeded()*2 - 1.0), (randomSeeded()*2 - 1.0), (randomSeeded()*2 - 1.0)};
        // printf("{%f %f %f}\n", v.x,v.y,v.z);
        if(v.mag2() < 1.0){
            return v.norm();
        }
    }
    return {0,0,0};
}

vector3 randomHemisphere(vector3 normal){
    vector3 v = randomVector();
    if(v.dot(normal) > 0.0){
        return v;
    }
    return v * -1;
}

vector3 randomHemisphereSeeded(vector3 normal){
    vector3 v = randomVectorSeeded();
    if(v.dot(normal) > 0.0){
        return v;
    }
    return v * -1;
}

#endif