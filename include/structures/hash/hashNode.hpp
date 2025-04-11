#ifndef hashNode_HPP
#define hashNode_HPP

#include "raylib.h"
#include "animation.h"
#include <map>

class hashNode : public Animation {
    public:
        bool targeted;
        int value, targetValue;
        inline hashNode(float x, float y, int value) : Animation(x, y), value(value) {
            targetValue = -1;
            targeted = false;
            setPosition((Vector2){x, y});
        }
        inline ~hashNode() {
        }
};

#endif // hashNode_HPP