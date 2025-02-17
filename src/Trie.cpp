#include "Trie.hpp"

Trie::Trie() {
    root = new TrieNode();
}

Vector2 Trie::Lerp(Vector2 start, Vector2 end, float t) {
    Vector2 direction = {end.x - start.x, end.y - start.y};
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 1.0)
        {
            direction.x /= length;
            direction.y /= length;
            return {start.x + direction.x * t, start.y + direction.y * t};
        }
        return end;
}

Vector2 Trie::calcPosition(TrieNode *root) {
    Vector2 width = {0, 0};
    std::vector<Vector2> widthList;
    std::vector<TrieNode*> queue;
    for (auto &child : root->children) 
        if (child.second->valid) {
        queue.push_back(child.second);
        widthList.push_back(calcPosition(child.second));
    }
    if (queue.size() == 0) return width;
    int mid1, mid2;
    if (queue.size() % 2 == 0) {
        mid1 = queue.size() / 2 - 1;
        mid2 = queue.size() / 2;
        queue[mid1]->targetPosition = (Vector2){- (widthList[mid1].y + xOFFSET / 2), yOFFSET};
        queue[mid2]->targetPosition = (Vector2){widthList[mid2].x + xOFFSET / 2, yOFFSET};
        width.x = widthList[mid1].x + widthList[mid1].y + xOFFSET / 2;
        width.y = widthList[mid2].x + widthList[mid2].y + xOFFSET / 2;

    } else {
        mid1 = queue.size() / 2;
        mid2 = queue.size() / 2;

        queue[mid1]->targetPosition = (Vector2){0, yOFFSET};
        width = widthList[mid1];
    }
    for (int i = mid1 - 1; i >= 0; i--) {
        queue[i]->targetPosition = (Vector2){- (width.x + widthList[i].y + xOFFSET), yOFFSET};
        width.x += widthList[i].x + widthList[i].y + xOFFSET;
    }
    for (int i = mid2 + 1; i < queue.size(); i++) {
        queue[i]->targetPosition = (Vector2){width.y + widthList[i].x + xOFFSET, yOFFSET};
        width.y += widthList[i].x + widthList[i].y + xOFFSET;
    }

    return width;
}

void Trie::drawLine(TrieNode*root, int x, int y) {
    if (root == NULL) {
        return;
    }
    for (auto &child : root->children) 
        if (child.second->valid) {
        DrawLineEx((Vector2){x, y}, (Vector2){child.second->position.x + x, child.second->position.y + y}, 3, BLACK);
        drawLine(child.second, child.second->position.x + x, child.second->position.y + y);
    }
}

void Trie::drawText(TrieNode *root, int x, int y)
{
    if (root == NULL) {
        return;
    }
    for (auto &child : root->children) 
        if (child.second->valid) {
        std ::cout << child.first << std::endl;
        DrawText(&child.first, child.second->position.x + x - 5, child.second->position.y + y - 5, 20, BLACK);
        drawText(child.second, child.second->position.x + x, child.second->position.y + y);
    }
}

void Trie::draw(TrieNode *root, int x, int y) {
    if (root == NULL) {
        return;
    }
    DrawCircle(x, y, NODE_RADIUS, root->selected ? GREEN : root->isEndOfWord ? RED : BLACK);
    for (auto &child : root->children) 
        if (child.second->valid) {
        draw(child.second, child.second->position.x + x, child.second->position.y + y);
    }
}

std::queue<TrieNode*> Trie::insertAnimation(std::string word) {
    std::queue<TrieNode*> result;
    TrieNode *current = root;
    result.push(current);
    for (int i = 0; i < word.size(); i++) {
        if (current->children.find(word[i]) == current->children.end()) {
            current->children[word[i]] = new TrieNode();
            current->children[word[i]]->valid = false;
            current->children[word[i]]->position = current->position;
        }
        current = current->children[word[i]];
        result.push(current);
    }
    current->isEndOfWord = true;
    while (!result.empty()) {
        work.push(result.front());
        result.pop();
    }
    return result;
}

bool Trie::move(TrieNode *root)
{
    bool moved = false;
    if (root == NULL) return false;
    for (auto &child : root->children) {
        if (child.second->targetPosition.x != child.second->position .x || child.second->targetPosition.y != child.second->position.y) {
            moved = true;
            child.second->position = Lerp(child.second->position, child.second->targetPosition, 5);
        }
        if (move(child.second)) moved = true;
    }
    return moved;
}