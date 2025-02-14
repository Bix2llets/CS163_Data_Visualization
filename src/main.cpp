#include <iostream>

#include "GUIObject.h"
#include "button.h"
#include "raylib.h"

const Color hoverColor{98, 111, 71, 255};
const Color textColor{254, 250, 224, 255};
const Color buttonColor{164, 180, 101, 255};
int main() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    Button test({0, 0}, {100, 50}, "test button", textColor, buttonColor, hoverColor);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        // GraphicInterface::render();
        test.render();
        if (test.isPressed()) std::cerr << "Button pressed\n";
        // anotherTest->render();
        // anotheranotherTest.render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}