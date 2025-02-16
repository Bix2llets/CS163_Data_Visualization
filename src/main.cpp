#include <iostream>
#include <memory>

#include "GUIObject.h"
#include "button.h"
#include "singlyLInkedList.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"

using namespace ColorPalette::FlatUI;
int main() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2);

    ll.setColor(ColorPalette::FlatUI::MIDNIGHT_BLUE, ColorPalette::FlatUI::FLAT_ORANGE, ColorPalette::FlatUI::WET_ASPHALT);
    Button button1(400, 400, 100, 50, "Add Node", 12, ASBESTOS, CLOUDS, MIDNIGHT_BLUE);
    Button button2(500, 400, 100, 50, "Remove End");
    int nodeData = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        button1.render();
        button2.render();
        if (button1.isPressed()) 
        {
            nodeData++;
            ll.addNode(nodeData);
        }
        if (button2.isPressed()) 
        {
            ll.removeEnd();
            nodeData--;
        }
        ll.render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}