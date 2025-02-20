#include "overload.h"
bool operator==(Color a, Color b) {
    if (a.r != b.r) return false;
    if (a.g != b.g) return false;
    if (a.b != b.b) return false;
    if (a.a != b.a) return false;
    return true;
}