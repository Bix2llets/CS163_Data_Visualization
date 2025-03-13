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
} // namespace mLib
