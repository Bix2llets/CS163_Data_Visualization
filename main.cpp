#include "raylib.h"
#include "graph.cpp"
// ...existing code...

int main() {
    InitWindow(800, 600, "Graph Visualization");
    SetTargetFPS(60);

    std::vector<Node> nodes = {
        {{100, 100}, {0, 0}, false},
        {{200, 200}, {0, 0}, false},
        {{300, 300}, {0, 0}, false}
    };

    while (!WindowShouldClose()) {
        // Update
        UpdateGraph(nodes);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGraph(nodes);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
