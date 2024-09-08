#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "location.hpp"
#include "ray.hpp"

struct camera{
    location loc; //back core of the camera
    // float unitsPerPixelVertical;
    float viewportHeight;
    float focalLength;
    int screenWidth;
    int screenHeight;
    int pixelScale;

    vector3 pixelDeltaU;
    vector3 pixelDeltaV;

    vector3 pixel00Loc;

    camera(location loc,float viewportHeight,float focalLength, int screenWidth, int screenHeight, int pixelScale)
    : loc(loc), viewportHeight(viewportHeight), focalLength(focalLength), screenWidth(screenWidth), screenHeight(screenHeight), pixelScale(pixelScale){
        recalculate();
    }

    void recalculate(){
        float aspect = ((float)screenWidth)/screenHeight;

        vector3 viewportU = loc.rightVector * (viewportHeight * aspect);
        vector3 viewportV = loc.fwdVector.cross(loc.rightVector) * viewportHeight * 1;//vector3(0, viewportHeight * -1, 0); 

        pixelDeltaU = viewportU / (screenWidth / pixelScale);
        pixelDeltaV = viewportV / (screenHeight / pixelScale);

        vector3 viewportUpperLeft = loc.pos + (loc.fwdVector * focalLength) - viewportU/2 - viewportV/2;
    
        pixel00Loc = viewportUpperLeft + (pixelDeltaU + pixelDeltaV) * 0.5;
    }

    ray generateRay(int x, int y){
        vector3 pixelCenter = pixel00Loc + (pixelDeltaU * x) + (pixelDeltaV * y);

        return ray{loc.pos, pixelCenter - loc.pos };
    }
};

#endif