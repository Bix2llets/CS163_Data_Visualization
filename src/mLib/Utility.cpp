#include <mLib/Utility.hpp>

namespace Utility {

int highlightingRow;
Color highlightColor = {128, 239, 128, 255};
Texture2D diceTexture[6], dice, pause, play, prev, next, backward, forward,
    expand, collapse;
const std::vector<std::string> TrieInsert = {
    "Begin",       // 0
    "cur = root",  // 1
    "for char x in word",
    "   if cur->c[x] == NULL, cur->c[x] = new TrieNode",  // 2
    "   cur = cur->c[x]",                                 // 3
    "cur->isEndOfWord = true",                            // 4
    "End",                                                // 5
};

const std::vector<std::string> TrieSearch = {
    "Begin",       // 6
    "cur = root",  // 7
    "for char x in word",
    "   if cur->c[x] == NULL, End",     // 8
    "   else cur = cur->c[x]",          // 9
    "if cur->isEndOfWord, return cur",  // 10
    "End",                              // 11
};

const std::vector<std::string> TrieDelete = {
    "Begin",       // 12
    "cur = root",  // 13
    "for char x in word",
    "   if cur->c[x] == NULL, return false",  // 14
    "   cur = cur->c[x]",                     // 15
    "...",
    "End",  // 19
};

const std::vector<std::string> TrieDelete2 = {
    "Begin",  // 12
    "...",
    "if cur->isEndOfWord = false, return false",
    "cur->isEndOfWord = false",  // 16
    "while cur.isLeaf() & !cur.isEnd() & cur != root,",
    "   temp = cur, cur = cur->parent",  // 17
    "   delete temp",                    // 18
    "End",                               // 19
};

const std::vector<std::string> hashInsert = {
    "Begin",                                 // 0
    "i = v % m",                             // 1
    "while a[i]->v != -1, i = (i + 1) % m",  // 2
    "if a[i]->v = -1, a[i]->v = v",          // 3
    "End",                                   // 4
};

const std::vector<std::string> hashSearch = {
    "Begin",                                         // 5
    "i = v % m",                                     // 6
    "while a[i]->v != (v and -1), i = (i + 1) % m",  // 7
    "if a[i]->v == v, return i",                     // 8
    "End",                                           // 9
};

const std::vector<std::string> hashDelete = {
    "Begin",                                         // 10
    "i = v % m",                                     // 11
    "while a[i]->v != (v and -1), i = (i + 1) % m",  // 12
    "if a[i]->v == v, a[i]->v = -1",                 // 13
    "End",                                           // 14
};

const std::vector<std::string> AVLInsert = {
    "Begin",                        // 0
    "search for insert position",   // 1
    "insert node",                  // 2
    "rebalance",                    // 3
    "Case 1: Left rotation",        // 4
    "Case 2: Right rotation",       // 5
    "Case 3: Left-Right rotation",  // 6
    "Case 4: Right-Left rotation",  // 7
    "End",                          // 8
};

const std::vector<std::string> AVLSearch = {
    "Begin",                               // 9
    "if node.data = value, return node",   // 10
    "if node.data < value, search right",  // 11
    "if node.data > value, search left",   // 12
    "End",                                 // 13
};

const std::vector<std::string> AVLDelete = {
    "Begin",            // 14
    "search for node",  // 15
    "if node is internal node",
    "   find successor S",    // 16
    "   node.data = S.data",  // 17
    "   delete successor S",  // 18
    "else delete node",       // 19
    "...",
    "End",  // 25
};

const std::vector<std::string> AVLDelete2 = {
    "Begin",  // 14
    "...",
    "rebalance",                    // 20
    "Case 1: Left rotation",        // 21
    "Case 2: Right rotation",       // 22
    "Case 3: Left-Right rotation",  // 23
    "Case 4: Right-Left rotation",  // 24
    "End",                          // 25
};

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
void Init() {
    inter30 = LoadFontEx("assets/Inter-Black.ttf", 30, nullptr, 0);
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
void DrawTextTrie(int index) {
    if (index == -1) {
        highlightingRow = index;
        CodePane::loadCode(TrieInsert);
        CodePane::setHighlight(&highlightingRow);
        return;
    }
    if (index <= 5) {
        highlightingRow = index;
        if (highlightingRow > 1) highlightingRow++;
        CodePane::loadCode(TrieInsert);
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 11) {
        highlightingRow = index - 6;
        if (highlightingRow > 1) highlightingRow++;
        CodePane::loadCode(TrieSearch);
        CodePane::setHighlight(&highlightingRow);
    } else {
        if (index <= 15) {
            CodePane::loadCode(TrieDelete);
            highlightingRow = index - 12;
            if (highlightingRow > 1) highlightingRow++;
            CodePane::setHighlight(&highlightingRow);
        } else {
            CodePane::loadCode(TrieDelete2);
            highlightingRow = index - 16;
            highlightingRow += 3;
            if (highlightingRow > 3) highlightingRow++;
            CodePane::setHighlight(&highlightingRow);
        }
    }
}
void DrawTextHash(int index) {
    if (index == -1) {
        highlightingRow = index;
        CodePane::loadCode(hashInsert);
        CodePane::setHighlight(&highlightingRow);
        return;
    }
    if (index <= 4) {
        highlightingRow = index;
        CodePane::loadCode(hashInsert);
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 9) {
        highlightingRow = index - 5;
        CodePane::loadCode(hashSearch);
        CodePane::setHighlight(&highlightingRow);
    } else {
        highlightingRow = index - 10;
        CodePane::loadCode(hashDelete);
        CodePane::setHighlight(&highlightingRow);
    }
}
void DrawTextAVL(int index) {
    if (index == -1) {
        highlightingRow = index;
        CodePane::loadCode(AVLInsert);
        CodePane::setHighlight(&highlightingRow);
        return;
    }
    if (index <= 8) {
        CodePane::loadCode(AVLInsert);
        highlightingRow = index;
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 13) {
        CodePane::loadCode(AVLSearch);
        highlightingRow = index - 9;
        CodePane::setHighlight(&highlightingRow);
    } else {
        if (index <= 19) {
            CodePane::loadCode(AVLDelete);
            highlightingRow = index - 14;
            if (highlightingRow > 1) highlightingRow++;
            CodePane::setHighlight(&highlightingRow);
        } else {
            CodePane::loadCode(AVLDelete2);
            highlightingRow = index - 20;
            highlightingRow += 2;
            CodePane::setHighlight(&highlightingRow);
        }
    }
}
}  // namespace Utility
