#include "welcomeMenu.h"

#include "colorPalette.h"
namespace WelcomeMenu {
using namespace ColorPalette::FlatUI;
const int BANNER_X = 0;
const int BANNER_Y = 0;
const int BANNER_WIDTH = 1600;
const int BANNER_HEIGHT = 200;

const int BUTTON_WIDTH = 250;
const int BUTTON_HEIGHT = 80;

const int FONT_SIZE = 20;

const int LEFT_MARGIN = 200;
const int UPPER_MARGIN = 50;
const int BUTTON_DISTANCE = 40;
const ColorSet BUTTON_COLOR{WET_ASPHALT, MIDNIGHT_BLUE, CLOUDS,
                            SILVER,      BLACK,         BLACK};
Button trie(250,
            BANNER_HEIGHT + UPPER_MARGIN +
                1 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
            BUTTON_WIDTH, BUTTON_HEIGHT, "Trie", FONT_SIZE, &buttonColorSet);
Button linkedList(650,
                  BANNER_HEIGHT + UPPER_MARGIN +
                      1 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
                  BUTTON_WIDTH, BUTTON_HEIGHT, "Linked List", FONT_SIZE,
                  &buttonColorSet);
Button graph(1050,
             BANNER_HEIGHT + UPPER_MARGIN +
                 1 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
             BUTTON_WIDTH, BUTTON_HEIGHT, "Graph", FONT_SIZE, &buttonColorSet);
Button hashTable(450,
                 BANNER_HEIGHT + UPPER_MARGIN +
                     3 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
                 BUTTON_WIDTH, BUTTON_HEIGHT, "Hash table", FONT_SIZE,
                 &buttonColorSet);
Button AVLTree(850,
               BANNER_HEIGHT + UPPER_MARGIN +
                   3 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
               BUTTON_WIDTH, BUTTON_HEIGHT, "AVL Tree", FONT_SIZE,
               &buttonColorSet);

void render() {
    Vector2 bannerLocation = {GetRenderWidth() / 2 + 10, 125};
    DrawRectangleGradientV(0, 0, GetRenderWidth(), GetRenderHeight() / 10 * 2,
                           backgroundSet.backgroundNormal, Color{0, 0, 0, 0});
    Utility::drawText("Data Visualizer", bannerLocation, Utility::noto,
                          buttonColorSet.textNormal, 100, 1,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);

    trie.render();
    linkedList.render();
    graph.render();
    hashTable.render();
    AVLTree.render();
}
bool isTriePressed() { return trie.isPressed(); }
bool isLinkedListPressed() { return linkedList.isPressed(); };
bool isGraphPressed() { return graph.isPressed(); };
bool isHashTablePressed() { return hashTable.isPressed(); };
bool isAVLTreePressed() { return AVLTree.isPressed(); };

}  // namespace WelcomeMenu