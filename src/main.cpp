#include <iostream>
#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
int main() {
    
    InitWindow(1200, 900, "Amogus");
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawLine(0, 0, 100, 100, BLACK);
        EndDrawing();
    }
    std::cout << "Succ\n";
}