#ifndef CHNAGE_PROCEDURE_HPP
#define CHNAGE_PROCEDURE_HPP

#include "raylib.h"
#include <cassert>

class ChangeProcedure {
private:
    float alpha;
    bool requestChange;
    int oldValue, newValue, *targetPos;
public:
    ChangeProcedure(int _oldValue, int _newValue, int *_targetPos) : alpha(0.0f), requestChange(true), oldValue(_oldValue), newValue(_newValue), targetPos(_targetPos) {}

    void updateAlpha(float currTime, float rate) {
        if (currTime >= rate) {
            alpha = 255.f;
            *targetPos = newValue;
            requestChange = false;
            return ;
        }
        alpha = 255.f * (currTime / rate);
    }

    float getAlpha() const {
        return 255.f - alpha;
    }

    bool isCompleted() const {
        return requestChange == false;
    }

    int getOldValue() const {
        return oldValue;
    }

    int getNewValue() const {
        return newValue;
    }

};


#endif // #CHNAGE_PROCEDURE_HPP