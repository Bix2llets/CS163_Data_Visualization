#include <iostream>

#include "GUIObject.h"
#include "button.h"
#include "raylib.h"
#include <memory>
const Color hoverColor{98, 111, 71, 255};
const Color textColor{254, 250, 224, 255};
const Color buttonColor{164, 180, 101, 255};

// namespace ButtonCollection {
//     std::shared_ptr<Button> btn1, btn2;

//     void init() {
//         btn1 = std::make_shared<Button>(Rectangle{0, 0, 150, 75}, "testButton1", 16, textColor, buttonColor, hoverColor);
//         btn2 = std::make_shared<Button>(Rectangle{150, 0, 150, 75}, "testButton2", 16, textColor, buttonColor, hoverColor);

//     }
//     void render() {
//         btn1->render();
//         btn2->render();
//     }
// }
int main() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    // ButtonCollection::init();
    // Button test({0, 0}, {150, 75}, "test button", 16, textColor, buttonColor, hoverColor);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        // test.render();
        // ButtonCollection::render();

        // if (test.isPressed()) std::cerr << "Button pressed\n";
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}