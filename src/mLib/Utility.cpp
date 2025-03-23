#include <mLib/Utility.hpp>

namespace mLib
{
    Font mFont;
    const char *TrieInsert[15] = {
        "Begin",  // 0      
        "cur = root", // 1
        "for char x in word",   
        "if cur->children[x] == NULL",      // 2
        "cur->children[x] = new TrieNode",  // 2
        "cur = cur->children[x]", // 3
        "cur->isEndOfWord = true", // 4
        "End", // 5
    };

    const char *TrieSearch[15] = {
        "Begin",    //6
        "cur = root", //7
        "for char x in word", 
        "if cur->children[x] == NULL", //8
        "End", //8
        "cur = cur->children[x]", //9
        "End", // 10
    };

    const char *TrieDelete[15] = {
        "Begin",  // 11
        "cur = root", // 12
        "for char x in word",
        "if cur->children[x] == NULL", // 13
        "return false", // 13
        "cur = cur->children[x]", // 14
        "cur->isEndOfWord = false", // 15
        "while cur->children.size() == 0", 
        "and cur != root",
        "temp = cur, cur = cur->parent", // 16
        "delete temp", // 17
        "End", // 18
    };

    const char *hashInsert[15] = {
        "Begin", // 0
        "index = value % m", // 1
        "while root[index]->value != -1", // 2
        "index = (index + 1) % m", // 2
        "if root[index]->value == -1", // 3
        "root[index]->value = value", // 3
        "End", // 4
    };

    const char *hashSearch[15] = {
        "Begin", // 5
        "index = value % m", // 6
        "while root[index]->value != value", // 7
        "index = (index + 1) % m", // 7
        "if root[index]->value == value", // 8
        "End", // 9
    };

    const char *hashDelete[15] = {
        "Begin", // 10
        "index = value % m", // 11
        "while root[index]->value != value", // 12
        "&& root[index]->value != -1", // 12
        "index = (index + 1) % m", // 12
        "if root[index]->value == value", // 13
        "root[index]->value = -1", // 13
        "End", // 14
    };

    const char *AVLInsert[15] = {
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

    const char *AVLSearch[15] = {
        "Begin", // 9
        "search for node", // 10
        "End", // 11
    };

    const char *AVLDelete[15] = {
        "Begin", // 12
        "search for node", // 13
        "if node is internal node", // 14
        "find successor S, node.v = S.v", // 14
        "delete successor S", // 14
        "else delete node", // 15
        "endif",
        "rebalance", // 16
        "Case 1: Left rotation", // 17
        "Case 2: Right rotation", // 18
        "Case 3: Left-Right rotation", // 19
        "Case 4: Right-Left rotation", // 20
        "End", // 21
    };
} // namespace mLib
