#include "utility.h"

#include "mainLoop.h"
namespace Utility {
const int SPACING = 1;
const int NORMAL_SIZE = 20;
Font inter12;
Font inter16;
Font inter20;
Font inter30;
Font jbm20;
Font noto;

int highlightingRow;
Texture2D diceTexture[6], dice, pause, play, prev, next, backward, forward,
    expand, collapse;

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

void init() {
    inter12 = LoadFontEx("assets/Inter-Black.ttf", 12, NULL, 0);
    inter16 = LoadFontEx("assets/Inter-Black.ttf", 16, NULL, 0);
    inter20 = LoadFontEx("assets/Inter-Black.ttf", 20, NULL, 0);
    inter30 = LoadFontEx("assets/Inter-Black.ttf", 30, nullptr, 0);
    jbm20 = LoadFontEx("assets/jetbrainsMono.ttf", 20, NULL, 0);
    noto = LoadFontEx("assets/NotoSerif-Regular.ttf", 100, nullptr, 0);
    highlightingRow = -1;
    diceTexture[0] = LoadTexture("assets/dice/1_dot.png");
    diceTexture[1] = LoadTexture("assets/dice/2_dots.png");
    diceTexture[2] = LoadTexture("assets/dice/3_dots.png");
    diceTexture[3] = LoadTexture("assets/dice/4_dots.png");
    diceTexture[4] = LoadTexture("assets/dice/5_dots.png");
    diceTexture[5] = LoadTexture("assets/dice/6_dots.png");
    dice = LoadTexture("assets/dice/dice.png");
    pause = LoadTexture("assets/animationButton/pause.png");
    play = LoadTexture("assets/animationButton/play.png");
    prev = LoadTexture("assets/animationButton/backward.png");
    next = LoadTexture("assets/animationButton/forward.png");
    forward = LoadTexture("assets/animationButton/next.png");
    backward = LoadTexture("assets/animationButton/prev.png");
    expand = LoadTexture("assets/animationButton/expand.png");
    collapse = LoadTexture("assets/animationButton/collapse.png");
}
void drawEdge(Vector2 beginPosition, Vector2 endPosition, Color color) {
    if (Vector2Distance(beginPosition, endPosition) == 0) return;
    Vector2 distanceVect = Vector2Subtract(endPosition, beginPosition);

    DrawLineEx(beginPosition, endPosition, 3, color);
}

std::string GenerateRandomText(int length) {
    length = GetRandomValue(1, length);
    std::string text;
    for (int i = 0; i < length; i++) {
        text.push_back((GetRandomValue(1, 1000000000) % 26) + 'A');
    }
    return text;
}

int GenerateRandomNum(int length) {
    length = GetRandomValue(1, length);
    std::cout << length << std::endl;
    int num = 0;
    for (int i = 0; i < length; i++) {
        num = num * 10 + GetRandomValue(0 + (i == 0), 9);
    }
    return num;
}

void GenerateRandomText(char *text) {
    int length = GetRandomValue(1, 10) % 5 + 1;
    for (int i = 0; i < length; i++) {
        text[i] = (GetRandomValue(1, 1000000000) % 26) + 'A';
    }
    text[length] = '\0';
}
void GenerateRandomNum(char *text) {
    int length = GetRandomValue(1, 10) % 3 + 1;
    for (int i = 0; i < length; i++) {
        text[i] = (GetRandomValue(1, 1000000000) % 10) + '0';
    }
    text[length] = '\0';
}
}  // namespace Utility

Vector2 randomPosition() {
    float posX =
        float(rand() % int(AppInfo::LOWER_RIGHT.x - AppInfo::UPPER_LEFT.x) +
              AppInfo::UPPER_LEFT.x);
    float posY =
        float(rand() % int(AppInfo::LOWER_RIGHT.y - AppInfo::UPPER_LEFT.y) +
              AppInfo::UPPER_LEFT.y);
    return Vector2{posX, posY};
}

bool isStrNum(std::string str) {
    for (char x : str)
        if (x < '0' || x > '9') return false;
    return true && str.size();
}