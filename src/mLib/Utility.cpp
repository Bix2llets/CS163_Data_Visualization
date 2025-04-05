#include <mLib/Utility.hpp>

namespace mLib
{
    Font mFont;
    int row;
    Color highlightColor = ORANGE;
    Texture2D diceTexture[6], dice, pause, play, prev, next, backward, forward, expand, collapse;
    const std::vector<std::string> TrieInsert = {
        "Begin",  // 0      
        "cur = root", // 1
        "for char x in word",   
        "   if cur->c[x] == NULL, cur->c[x] = new TrieNode",  // 2
        "   cur = cur->c[x]", // 3
        "cur->isEndOfWord = true", // 4
        "End", // 5
    };

    const std::vector<std::string> TrieSearch = {
        "Begin",    //6
        "cur = root", //7
        "for char x in word", 
        "   if cur->c[x] == NULL, End", //8
        "   else cur = cur->c[x]", //9
        "if cur->isEndOfWord, return cur", //10
        "End", // 11
    };

    const std::vector<std::string> TrieDelete = {
        "Begin",  // 12
        "cur = root", // 13
        "for char x in word",
        "   if cur->c[x] == NULL, return false", // 14
        "   cur = cur->c[x]", // 15
        "...",
        "End", // 19
    };

    const std::vector<std::string> TrieDelete2 = {
        "Begin",  // 12
        "...",
        "if cur->isEndOfWord = false, return false", 
        "cur->isEndOfWord = false", // 16
        "while cur.isLeaf() & !cur.isEnd() & cur != root,",
        "   temp = cur, cur = cur->parent", // 17
        "   delete temp", // 18
        "End", // 19
    };

    const std::vector<std::string> hashInsert = {
        "Begin", // 0
        "i = v % m", // 1
        "while a[i]->v != -1, i = (i + 1) % m", // 2
        "if a[i]->v = -1, a[i]->v = v", // 3
        "End", // 4
    };

    const std::vector<std::string> hashSearch = {
        "Begin", // 5
        "i = v % m", // 6
        "while a[i]->v != (v and -1), i = (i + 1) % m", // 7
        "if a[i]->v == v, return i", // 8
        "End", // 9
    };

    const std::vector<std::string> hashDelete = {
        "Begin", // 10
        "i = v % m", // 11
        "while a[i]->v != (v and -1), i = (i + 1) % m", // 12
        "if a[i]->v == v, a[i]->v = -1", // 13
        "End", // 14
    };

    const std::vector<std::string> AVLInsert = {
        "Begin", // 0
        "search for insert position", // 1
        "insert node", // 2
        "rebalance", // 3
        "Case 1: Left rotation", // 4
        "Case 2: Right rotation", // 5
        "Case 3: Left-Right rotation", // 6
        "Case 4: Right-Left rotation", // 7
        "End", // 8
    };

    const std::vector<std::string> AVLSearch = {
        "Begin", // 9
        "if node.data = value, return node", // 10
        "if node.data < value, search right", // 11
        "if node.data > value, search left", // 12
        "End", // 13
    };

    const std::vector<std::string> AVLDelete = {
        "Begin", // 14
        "search for node", // 15
        "if node is internal node",
        "   find successor S", // 16
        "   node.data = S.data", // 17
        "   delete successor S", // 18
        "else delete node", // 19
        "...",
        "End", // 25
    };

    const std::vector<std::string> AVLDelete2 = {
        "Begin", // 14
        "...",
        "rebalance", // 20
        "Case 1: Left rotation", // 21
        "Case 2: Right rotation", // 22
        "Case 3: Left-Right rotation", // 23
        "Case 4: Right-Left rotation", // 24
        "End", // 25
    };
} // namespace mLib
