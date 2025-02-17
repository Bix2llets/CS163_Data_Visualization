#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#include <string>

#include "GUIObject.h"
#include "colorPalette.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "utility.h"
class SinglyLinkedList : public GUIObject {
   private:
    const ColorPalette::ColorSet PALETTE;
    const float HORIZONTAL_DISTANCE;
    const float VERTICAL_DISTANCE;
    friend class Node;
    int countNode;
    const int LEFT_MARGIN;
    const int RIGHT_MARGIN;
    const float RADIUS;
    class Node : public GUIObject {
        friend class SinglyLinkedList;

       private:
        std::string data;
        Node *nextNode = nullptr;
        const ColorPalette::ColorSet PALETTE;
        const float RADIUS;
       public:
        ~Node();

        Node(std::string data = "", int x = 0,
             int y = 0, float radius = 50, ColorPalette::ColorSet palette = ColorPalette::DEF_SET)
            : GUIObject(x, y), data{data}, RADIUS{radius}, PALETTE{palette} {};
        Node(int data, int x = 0, int y = 0, float radius = 50, ColorPalette::ColorSet palette = ColorPalette::DEF_SET)
            : Node(std::to_string(data), x, y, radius, palette) {};
        Node *&getNextNode() { return nextNode; };

        void render();
        Vector2 getLeftMost() const;
        Vector2 getRightMost() const;
    };
    Node *root;

   public:
    SinglyLinkedList(float x, float y, ColorPalette::ColorSet colorSet)
        : GUIObject(x, y),
          root{nullptr},
          RADIUS{40},
          HORIZONTAL_DISTANCE{50},
          VERTICAL_DISTANCE{120},
          LEFT_MARGIN{50},
          RIGHT_MARGIN{50},
          countNode{0},
          PALETTE{colorSet} {}
    void addNode(std::string data);
    void addNode(int data);

    void removeEnd();
    void render();
};

#endif