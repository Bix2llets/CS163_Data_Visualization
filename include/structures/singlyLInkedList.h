#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#include <string>

#include "GUIObject.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "utility.h"
enum class Rotation {
    NO_ROTATION,
    CLOCKWISE,
    COUNTER_CLOCKWISE,
    HALF_CIRCLE

};
class SinglyLinkedList : public GUIObject {
   private:
    Rotation rotation;
    Color borderColor;
    Color backgroundColor;
    Color highlightColor;
    float width;
    float height;
    float distance;
    friend class Node;
    int countNode;
    const int START_X = 50;
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
    SinglyLinkedList(int x, int y) : GUIObject(x, y) {
        root = nullptr;
        width = 120;
        distance = 80;
        height = 60;
        rotation = Rotation::NO_ROTATION;
        countNode = 0;
    }
    Color getBorderColor() const { return borderColor; };
    Color getBackgroundColor() const { return backgroundColor; };
    Color getHighlightColor() const { return highlightColor; };
    void setColor(Color border, Color background, Color highlight);
    Rotation getRotation() const { return rotation; }
    void addNode(std::string data);
    void addNode(int data);
    
    void removeEnd();
    void render();
};

#endif