#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"
enum class VerticalAlignment { TOP, CENTERED, BOTTOM };
enum class HorizontalAlignment { LEFT, CENTERED, RIGHT };
Vector2 randomPosition();

bool isStrNum(std::string str);
namespace Utility {
extern Font inter12;
extern Font inter16;
extern Font inter20;
extern Font inter30;
extern Font jbm20;
extern Font noto;
extern const int NORMAL_SIZE;
extern const int SPACING;

extern int highlightingRow;
extern Texture2D diceTexture[6], dice, pause, play, prev, next, forward,
    backward, expand, collapse;

void init();
void drawText(std::string text, Vector2 position, Font font, Color textColor,
              int fontSize, int spacing, VerticalAlignment verticalAlign,
              HorizontalAlignment horizontalAlign);

void drawEdge(Vector2 beginPostion, Vector2 endPosition, Color color);

extern const std::vector<std::string> TrieInsert;
extern const std::vector<std::string> TrieSearch;
extern const std::vector<std::string> TrieDelete;
extern const std::vector<std::string> TrieDelete2;
extern const std::vector<std::string> hashInsert;
extern const std::vector<std::string> hashSearch;
extern const std::vector<std::string> hashDelete;
extern const std::vector<std::string> AVLInsert;
extern const std::vector<std::string> AVLSearch;
extern const std::vector<std::string> AVLDelete;
extern const std::vector<std::string> AVLDelete2;

std::string GenerateRandomText(int length);
    int GenerateRandomNum(int length);
    void GenerateRandomText(char *text);
    void GenerateRandomNum(char *text);
    void DrawTextAVL(int index);
    void DrawTextTrie(int index);
    void DrawTextHash(int index);
}  // namespace Utility
