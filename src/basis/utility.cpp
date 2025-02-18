#include "utility.h"
namespace DrawUtility {
const int SPACING = 1;
const int NORMAL_SIZE = 20;
Font inter20;
void drawText(std::string text, Vector2 position, Font font, Color textColor,
              int fontSize, int spacing, VerticalAlignment verticalAlign,
              HorizontalAlignment horizontalAlign) {
    Vector2 textDimension =
        MeasureTextEx(font, text.c_str(), fontSize, spacing);

    if (verticalAlign == VerticalAlignment::CENTERED)
        position.y -= 0.5 * textDimension.y;
    if (verticalAlign == VerticalAlignment::TOP) position.y -= textDimension.y;

    if (horizontalAlign == HorizontalAlignment::CENTERED)
        position.x -= 0.5 * textDimension.x;
    if (horizontalAlign == HorizontalAlignment::RIGHT)
        position.x -= textDimension.x;
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, textColor);
}

void init() { inter20 = LoadFontEx("assets/Inter-Black.ttf", 20, NULL, 0); }
void drawEdge(Vector2 beginPosition, Vector2 endPosition, Color color) {
    if (Vector2Distance(beginPosition, endPosition) == 0) return;
    Vector2 distanceVect = Vector2Subtract(endPosition, beginPosition);
    
    // distanceVect = Vector2ClampValue(distanceVect, 1, 1);
    // distanceVect = Vector2Scale(distanceVect, -1);
    // Vector2 perpendicularVect = {-distanceVect.y, distanceVect.x};
    // Vector2 point1 = Vector2Add(endPosition, Vector2Add(Vector2Scale(distanceVect, 10), Vector2Scale(perpendicularVect, 5)));
    // Vector2 point2 = Vector2Add(endPosition, Vector2Add(Vector2Scale(distanceVect, 10), Vector2Scale(perpendicularVect, -5)));
    
    DrawLineEx(beginPosition, endPosition, 2, color);
    // DrawTriangle(endPosition, point1, point2, color);
    // DrawTriangle(endPosition, point2, point1, color);
}
}  // namespace DrawUtility