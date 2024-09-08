// #include "raylib-cpp/include/raylib-cpp.hpp"
extern "C" {
    #include "raylib5\include\raylib.h"
}
#include <cmath>
#include <stdint.h>
#include <stdio.h>
// #include <stdlib>
#include <vector>
#include <algorithm>
#include <memory>
#include <typeinfo>
#include <limits>

// #include "raylib5\include\raylib.h"
#include "vector3.hpp"
#include "location.hpp"
#include "material.hpp"
#include "hit.hpp"
#include "camera.hpp"
#include "auxiliary.hpp"

#define HITTABLE_ID_SPHERE 1
#define HITTABLE_ID_TRIANGLE 2

using namespace std;

// int main() {
//     int screenWidth = 800;
//     int screenHeight = 450;

//     raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");
//     raylib::Texture logo("raylib_logo.png");

//     SetTargetFPS(60);

//     while (!window.ShouldClose())
//     {
//         BeginDrawing();

//         window.ClearBackground(RAYWHITE);

//         DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

//         // Object methods.
//         logo.Draw(
//             screenWidth / 2 - logo.GetWidth() / 2,
//             screenHeight / 2 - logo.GetHeight() / 2);

//         EndDrawing();
//     }

//     // UnloadTexture() and CloseWindow() are called automatically.

//     return 0;
// }

int pixelScale = 20;
int screenWidth = 800;
int screenHeight = 600;

int randSeed = 0;

int maxBounces = 2;

struct hittable{
    virtual ~hittable() = default;
    virtual Hit collide(ray ray) const
    {
        Hit h = {false, 0, vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
        printf("SOMETHING WENT WRONG\n");
        return h;
    };
};

class ListObj{
    public:
    ListObj* nextPointer;
    hittable* obj;
    uint8_t id;

    ListObj(hittable* ptr, uint8_t id):obj(ptr),nextPointer(NULL),id(id){

    }
};

class ObjList{
    public:
    static ListObj* startPointer;
    static ListObj* endPointer;
    static int size;

    ObjList(){

    }

    void pushHittable(hittable* ptr, uint8_t id){
        ListObj* obj = new ListObj(ptr, id);
        if(startPointer == NULL){
            startPointer = obj;
            endPointer = obj;
        }else{
            endPointer->nextPointer = obj;
            endPointer = obj;
        }
        size ++;
    }

    void pushSphere(hittable* ptr){
        pushHittable(ptr, HITTABLE_ID_SPHERE);
    }
};
ListObj* ObjList::startPointer = NULL;
ListObj* ObjList::endPointer = NULL;
int ObjList::size = 0;

// std::list<sphere> spheres;

struct sphere : hittable{
    vector3 pos; //center point
    float radius;
    material mat;

    sphere(vector3 pos, float radius,  material mat) 
        : pos(pos), radius(radius), mat(mat)
    {}

    sphere() 
        : pos({0,0,0}), radius(0), mat({{0,0,0},0,0})
    {}

    Hit collide(ray ray) const
    {
        vector3 offsetCenter = pos - ray.origin;
        float a = ray.dir.norm().mag2();//.dot(dir);
        float b = ray.dir.norm().dot(offsetCenter);
        float c = offsetCenter.mag2() - radius * radius;
        float discriminant = b*b - a*c;
        // printf("? orig{%.2f %.2f %.2f} dir{%.2f %.2f %.2f} spos:{%.2f %.2f %.2f}\n",origin.x,origin.y,origin.z, dir.x,dir.y,dir.z, s.pos.x, s.pos.y, s.pos.z);
        // printf("ABC %.2f, %.2f, %.2f D%.2f\n",a,b,c, discriminant);

        bool hit = discriminant >= 0;
    
        if(hit){
            float distA = (b + sqrt(discriminant))/(a);
            float distB = (b - sqrt(discriminant))/(a);
            if(distB < 0){
                Hit h = {false, 0, vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
                return h;
            }
            vector3 hitPoint = ray.origin + ray.dir.norm() * distB;
            vector3 normalVector = (pos - hitPoint).norm();
            // if(1 || ray.origin.x != 0)
            // {
            //     ray.origin.print();
            //     ray.dir.print();
            //     offsetCenter.print();
                
            //     printf("abc:%.3f %.3f %f dA:%.3f dB:%.3f em:%.3f d:%.3f r:%.3f",a,b,c,distA,distB,mat.emissivity, discriminant,radius);
                
            //     hitPoint.println();
            //     normalVector.println();
            // }
            
            if(ray.dir.dot(normalVector) > 0.0){
                normalVector = normalVector * -1;
            }
            Hit h = {true, distB, hitPoint, normalVector, mat};
            return h;
        }else{
            // printf("MISS {%f %f %f} {%f %f %f}\n",origin.x,origin.y,origin.z,dir.x,dir.y,dir.z);
            Hit h = {false, 0, vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
            return h;
        }
    }
};
// sphere spheres[10];
// std::list<sphere> spheres;
// hittable hittables[20];
// vector<hittable> objs;
ObjList objs;

struct triangle : hittable{
    vector3 pos; //back core of the camera
    float radius;
    material m;

    Hit collide(ray ray) const
    {
        return Hit{false, 0, vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
    }
};

// Hit collideSphere(const sphere& s) const
// {
//     vector3 offsetCenter = s.pos - origin;
//     float a = dir.mag2();//.dot(dir);
//     float b = dir.dot(offsetCenter);
//     float c = offsetCenter.mag2() - s.radius * s.radius;
//     float discriminant = b*b - a*c;
//     // printf("? orig{%.2f %.2f %.2f} dir{%.2f %.2f %.2f} spos:{%.2f %.2f %.2f}\n",origin.x,origin.y,origin.z, dir.x,dir.y,dir.z, s.pos.x, s.pos.y, s.pos.z);
//     // printf("ABC %.2f, %.2f, %.2f D%.2f\n",a,b,c, discriminant);

//     bool hit = discriminant >= 0;
        
//     if(hit){
//         // printf("HIT {%f %f %f} {%f %f %f}\n",origin.x,origin.y,origin.z,dir.x,dir.y,dir.z);
//         float distA = (b + sqrt(discriminant))/(a);
//         float distB = (b - sqrt(discriminant))/(a);
//         // printf("a:%f b:%f\n",distA,distB);
//         vector3 hitPoint = dir * distB;
//         vector3 normalVector = hitPoint - s.pos;
//         if(dir.dot(normalVector) > 0.0){
//             normalVector = normalVector * -1;
//         }
//         Hit h = {true, hitPoint, normalVector, s.mat};
//         return h;
//     }else{
//         // printf("MISS {%f %f %f} {%f %f %f}\n",origin.x,origin.y,origin.z,dir.x,dir.y,dir.z);
//         Hit h = {false, vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
//         return h;
//     }
// }

// Color operator*(const float a, const Color& c)
// {
//     return (Color){c.r * a,c.g * a,c.b * a,c.a * a};
// }

void createSphere(vector3 pos, float radius,  material mat){
    objs.pushSphere(new sphere(pos,radius,mat));
}

// void createSphere(vector3 pos, float radius,  material mat){
//     objs.pushSphere(new sphere(pos,radius,mat));
// }

Hit rayCollide(const ray& r){
    ListObj* ptr = ObjList::startPointer;
    Hit h = {false, numeric_limits<float>::max(), vector3{0,0,0}, vector3{0,0,0}, material{{0,0,0},0,0}};
    for(int i = 0; i < ObjList::size; i ++){
        if(ptr->id == HITTABLE_ID_SPHERE){
            sphere obj = *(sphere*)(ptr->obj);
            Hit x = obj.collide(r);
            if(x.hit && x.distance < h.distance){
                h = x;
            }
            // h = obj.collide(r);
        }
        ptr = ptr->nextPointer;
    }
    return h;
}

vector3 rayColor(const ray& r){
    // return (Color){124,43,96,255};
    // return (Color){r.dir.x,r.dir.y,r.dir.z,255};
    // printf("objects: %d\n",ObjList::size);
    vector3 light = {0,0,0};
    vector3 color = {1,1,1};
    bool hitted = false;

    ray project = r;
    for(int i = 0; i < maxBounces; i ++){
        Hit h = rayCollide(project);
        if(h.hit){
            hitted = true;
            // if(h.mat.emissivity < 1){
            // printf("p:");
            // project.origin.print();
            // printf("d:");
            // project.dir.print();

            project.origin = h.hitPoint;
            project.dir = randomHemisphere(h.hitNormal);
            
            // printf("hP:");
            // project.origin.print();
            // printf("d:");
            // project.dir.print();
            // printf("c:");
            // h.mat.color.print();
            // }

            vector3 emmited = h.mat.color * h.mat.emissivity;
            light += emmited * color;
            color *= h.mat.color;
            // printf("l:");
            // light.print();
            // printf("e:");
            // emmited.println();
            // printf("\n");
            // Color col = color();
            // ((h.hitNormal + vector3{1.0,1.0,1.0})/2).println();
            // return (h.hitNormal + vector3{1.0,1.0,1.0})/2;
            // return color;
        }
    }
    if(hitted){
        return light;
    }
    return skybox(r);
}

void drawScaledPixel(int posX, int posY, Color color){
    // DrawPixel(0*posX)
    DrawRectangle(pixelScale * posX, pixelScale * posY, pixelScale, pixelScale, color);
}

int main() {
    // memset(spheres, '\0', sizeof(spheres));
    InitWindow(screenWidth, screenHeight, "StarFighter");

    // Custom timming variables
    double previousTime = GetTime();    // Previous time measure
    double currentTime = 0.0;           // Current time measure
    double updateDrawTime = 0.0;        // Update + Draw time
    double waitTime = 0.0;              // Wait time (if target fps required)
    float deltaTime = 0.0f;             // Frame time (Update + Draw + Wait time)
    
    float timeCounter = 0.0f;           // Accumulative time counter (seconds)
    bool pause = false;                 // Pause control flag

    int printCounter = 0;
    
    int targetFPS = 60;                 // Our initial target fps

    material red = {{1.0,0.2,0.1},0.5,0};
    material blue = {{0.2,0.1,1.0},0.5,0};
    material sun = {{1.0,1.0,1.0},0,1};

    //CAMERA ORIENTATION STUFF
    // location camLoc = ;
    
    camera cam = camera(location{{0,0,1},{0,0,-1},{1,0,0}},2.0,1.0, screenWidth, screenHeight, pixelScale);

    // pixel00Loc.println();

    createSphere({0,0,0}, 0.4, red);

    // createSphere({0,1,-2}, 0.5, blue);

    createSphere({0,2,0}, 1, sun);

    // spheres[0].pos = {0,0,-1};
    // spheres[0].radius = 0.5;
    // spheres[0].m = red;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (!pause)
        {
            timeCounter += deltaTime;   // We count time (seconds)
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        countSeed = 0;
        // DrawText("It works!", 20, 20, 20, BLACK);
        for(int i = 0; i < (screenWidth/pixelScale); i ++){
            for(int j = 0; j < (screenHeight/pixelScale); j ++){

                cam.recalculate();
                Color pixelColor = color(rayColor(cam.generateRay(i,j)));
                drawScaledPixel(i,j,pixelColor);

                float zoom = 0.0001;
                float rotate = 0.0001;

                if(printCounter > 1000){
                    // randomVector().println();
                    printCounter = 0;
                }
                printCounter ++;

                if(IsKeyDown(KEY_RIGHT)){
                    // printf("right\n");
                    // camLoc.rightVector.println();
                    cam.loc.fwdVector = cam.loc.fwdVector.rotate({0,1,0},rotate);
                    cam.loc.rightVector = cam.loc.rightVector.rotate({0,1,0},rotate);
                    // camLoc.rightVector.println();
                    // if(printCounter > 1000){
                    //     cam.loc.fwdVector.println();
                    //     cam.loc.rightVector.println();
                    //     printCounter = 0;
                    // }
                    // printCounter ++;
                }else if(IsKeyDown(KEY_LEFT)){
                    // printf("left\n");
                    // camLoc.rightVector.println();
                    cam.loc.fwdVector = cam.loc.fwdVector.rotate({0,1,0},-rotate);
                    cam.loc.rightVector = cam.loc.rightVector.rotate({0,1,0},-rotate);
                    // camLoc.rightVector.println();
                    // if(printCounter > 1000){
                    //     cam.loc.fwdVector.println();
                    //     cam.loc.rightVector.println();
                    //     printCounter = 0;
                    // }
                    // printCounter ++;
                }if(IsKeyDown(KEY_UP)){
                    // printf("right\n");
                    // camLoc.rightVector.println();
                    cam.loc.pos += cam.loc.fwdVector * -zoom;
                    cam.focalLength += zoom;
                    // camLoc.rightVector.println();
                    // if(printCounter > 1000){
                    //     printf("%f ",cam.focalLength);
                    //     cam.loc.pos.println();
                    //     printCounter = 0;
                    // }
                    // printCounter ++;
                }else if(IsKeyDown(KEY_DOWN)){
                    // printf("left\n");
                    // camLoc.rightVector.println();
                    cam.loc.pos += cam.loc.fwdVector * zoom;
                    cam.focalLength -= zoom;
                    // camLoc.rightVector.println();
                    // if(printCounter > 1000){
                    //     printf("%f ",cam.focalLength);
                    //     cam.loc.pos.println();
                    //     printCounter = 0;
                    // }
                    // printCounter ++;
                }
            }
        }
        EndDrawing();
        // break;
        if (targetFPS > 0)          // We want a fixed frame rate
        {
            waitTime = (1.0f/(float)targetFPS) - updateDrawTime;
            if (waitTime > 0.0) 
            {
                WaitTime((float)waitTime);
                currentTime = GetTime();
                deltaTime = (float)(currentTime - previousTime);
            }
        }
        else deltaTime = (float)updateDrawTime;    // Framerate could be variable

        previousTime = currentTime;
    }
    CloseWindow();
    return 0;
}