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

const int FONT_SIZE = 30;

const int LEFT_MARGIN = 200;
const int UPPER_MARGIN = 50;
const int BUTTON_DISTANCE = 40;
const Color BUTTON_TEXT_COLOR = MIDNIGHT_BLUE;
const Color BUTTON_BACKGROUND_COLOR = CLOUDS;
const Color BUTTON_HIGHLIGHT_COLOR = SILVER;
Button trie(LEFT_MARGIN, BANNER_HEIGHT + UPPER_MARGIN, BUTTON_WIDTH,
            BUTTON_HEIGHT, "Trie", FONT_SIZE, BUTTON_TEXT_COLOR,
            BUTTON_BACKGROUND_COLOR, BUTTON_HIGHLIGHT_COLOR);
Button linkedList(LEFT_MARGIN,
                  BANNER_HEIGHT + UPPER_MARGIN +
                      1 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
                  BUTTON_WIDTH, BUTTON_HEIGHT, "Linked List", FONT_SIZE,
                  BUTTON_TEXT_COLOR, BUTTON_BACKGROUND_COLOR,
                  BUTTON_HIGHLIGHT_COLOR);
Button graph(LEFT_MARGIN,
             BANNER_HEIGHT + UPPER_MARGIN +
                 2 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
             BUTTON_WIDTH, BUTTON_HEIGHT, "Graph", FONT_SIZE, BUTTON_TEXT_COLOR,
             BUTTON_BACKGROUND_COLOR, BUTTON_HIGHLIGHT_COLOR);
Button hashTable(LEFT_MARGIN,
                 BANNER_HEIGHT + UPPER_MARGIN +
                     3 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
                 BUTTON_WIDTH, BUTTON_HEIGHT, "Hash table", FONT_SIZE,
                 BUTTON_TEXT_COLOR, BUTTON_BACKGROUND_COLOR,
                 BUTTON_HIGHLIGHT_COLOR);
Button AVLTree(LEFT_MARGIN,
               BANNER_HEIGHT + UPPER_MARGIN +
                   4 * (BUTTON_HEIGHT + BUTTON_DISTANCE),
               BUTTON_WIDTH, BUTTON_HEIGHT, "AVLTree", FONT_SIZE, BUTTON_TEXT_COLOR,
               BUTTON_BACKGROUND_COLOR, BUTTON_HIGHLIGHT_COLOR);

void render() {
    DrawRectangleGradientEx({0, 0, BANNER_WIDTH, BANNER_HEIGHT}, BELIZE_HOLE,
                            PETER_RIVER, PETER_RIVER, BELIZE_HOLE);
    trie.render();
    linkedList.render();
    graph.render();
    hashTable.render();
    AVLTree.render();
}
bool isTriePressed() {return trie.isPressed(); }
bool isLinkedListPressed() {return linkedList.isPressed(); };
bool isGraphPressed() {return graph.isPressed() ;};
bool isHashTablePressed() {return hashTable.isPressed(); };
bool isAVLTreePressed() {return AVLTree.isPressed(); };

}  // namespace WelcomeMenu