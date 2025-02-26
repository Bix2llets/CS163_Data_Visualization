#include "animation.h"
#include "utility.h"
#include "colorPalette.h"
#include "animationColor.h"
#include "arrow.h"
#include "raylib.h"
class Node : public Animation {
    std::string data;
    const ColorPalette::ColorSet PALETTE;
    float animationRate;
    int radius;
    AnimationColor borderColor;
    AnimationEdge nextNodeEdge;
    Node* nextNode;
    
    Node(std::string data, int x, int y, int radius = 50, 
         ColorPalette::ColorSet palette = ColorPalette::DEF_SET,
         float animationRate = 1.0f)
        : data{data},
          Animation{x, y, animationRate},
          animationRate{animationRate}, 
          PALETTE{palette} {};
    Node(int data, int x, int y, int radius = 50,
         ColorPalette::ColorSet palette = ColorPalette::DEF_SET,
         float animationRate = 1.0f)
        : Node(std::to_string(data), x, y, radius, palette, animationRate) {};

    // * Constructor done
    
    void render();
};
