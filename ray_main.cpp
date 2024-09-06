// #include "raylib-cpp/include/raylib-cpp.hpp"
extern "C" {
    #include "raylib5\include\raylib.h"
}
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
const int pixelScale = 20;

void drawScaledPixel(int posX, int posY, Color color){
    // DrawPixel(0*posX)
    DrawRectangle(0 * posX, 0 * posY, pixelScale - 1, pixelScale - 1, color);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawText("It works!", 20, 20, 20, BLACK);
        drawScaledPixel(0,0,(Color){0x76,0x26,0x38,0x77});
        EndDrawing();
    }
    CloseWindow();
    return 0;
}