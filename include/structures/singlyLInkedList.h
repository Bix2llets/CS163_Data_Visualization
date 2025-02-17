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
    const float WIDTH;
    const float HEIGHT;
    const float HORIZONTAL_DISTANCE;
    const float VERTICAL_DISTANCE;
    friend class Node;
    int countNode;
    const int LEFT_MARGIN;
    const int RIGHT_MARGIN;
    class Node : public GUIObject {
        friend class SinglyLinkedList;

       private:
        std::string data;
        Node *nextNode = nullptr;
        SinglyLinkedList &parentClass;

       public:
        ~Node();

        Node(SinglyLinkedList &parentClass, std::string data = "", int x = 0,
             int y = 0)
            : parentClass{parentClass}, GUIObject(x, y), data{data} {};
        Node(SinglyLinkedList &parentClass, int data, int x = 0, int y = 0)
            : Node(parentClass, std::to_string(data), x, y) {};
        Node *&getNextNode() { return nextNode; };

        void render();
        Vector2 getStartPoint() const;
        Vector2 getEndPoint() const;
    };
    Node *root;

   public:
    SinglyLinkedList(int x, int y, ColorPalette::ColorSet colorSet)
        : GUIObject(x, y),
          root{nullptr},
          WIDTH{120},
          HEIGHT{80},
          HORIZONTAL_DISTANCE{100},
          VERTICAL_DISTANCE{60},
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