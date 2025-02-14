#include <iostream>
#include "raylib.h"
#include "button.h"
#include "GUIObject.h"
int main() {
    InitWindow(1200, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    Button test({0, 0}, {200, 100}, "test button");
    while(!WindowShouldClose()) {
        BeginDrawing();
        test.render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}