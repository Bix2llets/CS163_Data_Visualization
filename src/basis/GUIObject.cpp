#include "GUIObject.h"

void GUIObject::setPosition(Vector2 _position) {
    position = _position;

}

void GUIObject::setPosition(float x, float y) {
    position = Vector2{x, y};
}