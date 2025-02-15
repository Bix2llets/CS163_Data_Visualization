#include <iostream>
#include <memory>

#include "GUIObject.h"
#include "button.h"
#include "singlyLInkedList.h"
#include "raylib.h"
#include "utility.h"
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
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2);
    ll.addNode(1);
    ll.addNode(1);
    ll.addNode(1);
    ll.addNode(1);
    ll.addNode(1);
    ll.addNode(1);
    ll.addNode(1);

    ll.setColor(buttonColor, textColor, hoverColor);
    Button button1(400, 400, 100, 50, "Add Node");
    Button button2(500, 400, 100, 50, "Remove End");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        button1.render();
        button2.render();
        if (button1.isPressed()) ll.addNode(1);
        if (button2.isPressed()) ll.removeEnd();
        ll.render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}