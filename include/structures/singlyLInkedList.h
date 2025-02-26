<<<<<<< HEAD
#include "animation.h"
=======
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#include <string>

#include "GUIObject.h"
#include "arrow.h"
#include "colorPalette.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "overload.h"
>>>>>>> basis
#include "utility.h"
#include "colorPalette.h"
#include "animationColor.h"
#include "arrow.h"
#include "raylib.h"
class Node : public Animation {
    std::string data;
    const ColorPalette::ColorSet PALETTE;
    float animationRate;
<<<<<<< HEAD
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
=======

    AnimationColor currentColor;
    class Node : public GUIObject {
        friend class SinglyLinkedList;

       private:
        float animationRate;
        std::string data;
        Node *nextNode = nullptr;
        const ColorPalette::ColorSet PALETTE;
        const float RADIUS;
        AnimationEdge nextNodeEdge;
        AnimationColor borderColor;
       public:
        ~Node();

        Node(std::string data = "", float x = 0, float y = 0, float radius = 50,
             ColorPalette::ColorSet palette = ColorPalette::DEF_SET,
             AnimationColor color = AnimationColor{1.0f}, float rate = 1.0f);
        Node(int data, int x = 0, int y = 0, float radius = 50,
             ColorPalette::ColorSet palette = ColorPalette::DEF_SET)
            : Node(std::to_string(data), x, y, radius, palette) {};
        Node *&getNextNode() { return nextNode; };

        Vector2 getLeftMost() const;
        Vector2 getRightMost() const;
        Vector2 getTopMost() const;
        Vector2 getBottomMost() const;

        void setAnimationRate(float rate);
        void resetAnimation();
        void render();
        void updateMotion();
        void updateColor();
        bool isMotionCompleted();
        bool isColorCompleted();
    };
    Node *root;

   public:
    SinglyLinkedList(float x, float y, ColorPalette::ColorSet colorSet, float animationRate = 1.0f)
        : GUIObject(x, y),
          root{nullptr},
          RADIUS{20},
          HORIZONTAL_DISTANCE{30},
          VERTICAL_DISTANCE{120},
          LEFT_MARGIN{50},
          RIGHT_MARGIN{50},
          countNode{0},
          PALETTE{colorSet},
          animationRate{animationRate} {}
    void addNode(std::string data, bool isInstant);
    void addNode(int data, bool isInstant);

    void removeEnd();
    void render();

    void setAnimationRate(float rate);
    void update();

    void resetAnimation();
    void setHighlight(bool highlight);

    void deHighlight();
>>>>>>> basis
};
