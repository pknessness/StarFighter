// #include "raylib-cpp/include/raylib-cpp.hpp"
extern "C" {
    #include "raylib5\include\raylib.h"
}
#include <cmath>
#include <stdint.h>
#include <stdio.h>
// #include "raylib5\include\raylib.h"

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

float randomValue(int in){
    long val = (in*(in*2140 + 21390) * (in * 2139021 + 213908)) & 0xFFFFFF;
    return val/0xFFFFFF;
}

uint8_t randomColor(int x, int y, int a){
    int in = (x * screenWidth + y) * (a+434);
    long val = (in*(in*2140 + 21390) * (in * 2139021 + 213908)) & 0xFFFFFF;
    printf("in:%d val:%d\n", in, val);
    return val >> 16;
}

struct vector3 {
    float x, y, z;

    vector3(float x, float y, float z) 
        : x(x), y(y), z(z)
    {
    }
    
    // addop. doesn't modify object. therefore const.
    vector3 operator+(const vector3& a)
    {
        return vector3(a.x+x, a.y+y, a.z+z);
    } 

    vector3 operator-(const vector3& a)
    {
        return vector3(a.x+x, a.y+y, a.z+z);
    } 

    float dot(const vector3& a)
    {
        return x*a.x + y*a.y, z*a.z;
    }

    vector3 cross(const vector3& a)
    {
        return vector3(y*a.z - z*a.y,z*a.x - x*a.z,x*a.y - y*a.x);
    }

    vector3 norm()
    {
        float mag = sqrt(x*x + y*y + z*z);
        return vector3(x/mag,y/mag,z/mag);
    }

    float mag()
    {
        return sqrt(x*x + y*y + z*z);
    }
};

struct location {
    vector3 pos;
    vector3 fwdVector;
    vector3 rightVector;
};

struct Cam{
    location loc; //back core of the camera
    float unitsPerPixelVertical;
    float pixelWidth;
    float pixelHeight;
    float focalLength;
};

void drawScaledPixel(int posX, int posY, Color color){
    // DrawPixel(0*posX)
    DrawRectangle(pixelScale * posX, pixelScale * posY, pixelScale, pixelScale, color);
}

int main() {
    InitWindow(screenWidth, screenHeight, "Raylib basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawText("It works!", 20, 20, 20, BLACK);
        for(int i = 0; i < screenWidth/pixelScale; i ++){
            for(int j = 0; j < screenHeight/pixelScale; j ++){
                uint8_t r = randomColor(i, j, 0);
                uint8_t g = randomColor(i, j, 1);
                uint8_t b = randomColor(i, j, 2);
                // printf("%d %d %d", r, g, b);
                drawScaledPixel(i,j,(Color){r,g,b,255});
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}