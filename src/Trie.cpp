#include "Trie.hpp"

Trie::Trie() {
    root = new TrieNode();
    working.clear();
    itr1 = 0, itr2 = 0;
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
        char str[2] = {child.first, '\0'};
        DrawText(str, child.second->position.x + x, child.second->position.y + y, 20, BLACK);
        drawText(child.second, child.second->position.x + x, child.second->position.y + y);
    }
}

void Trie::draw(TrieNode *root, int x, int y) {
    if (root == NULL) {
        return;
    }
    DrawCircle(x, y, NODE_RADIUS, root -> highlighted ? RED : root ->selected ? GREEN : root->isEndOfWord ? BLUE : PURPLE);
    for (auto &child : root->children) 
        if (child.second->valid) {
        draw(child.second, child.second->position.x + x, child.second->position.y + y);
    }
}

void Trie::insertAnimation(std::string word) {
    vWT result;
    TrieNode *current = root;
    result.push_back({SELECTING, {current}});
    for (int i = 0; i < word.size(); i++) {
        result.push_back({HIGH_LIGHTING, {current}});
        if (current->children.find(word[i]) == current->children.end()) {
            current->children[word[i]] = new TrieNode();
            current->children[word[i]]->valid = false;
            current->children[word[i]]->position = current->position;
        }
        result.push_back({CREATE, {current->children[word[i]]}});
        current = current->children[word[i]];
        result.push_back({SELECTING, {current}});
    }
    current->isEndOfWord = true;
    result.push_back({HIGH_LIGHTING, {current}});
    working.push_back({2, result});
}

bool Trie::move(TrieNode *root)
{
    bool moved = false;
    if (root == NULL) return false;
    for (auto &child : root->children) {
        if (child.second->targetPosition.x != child.second->position .x || child.second->targetPosition.y != child.second->position.y) {
            moved = true;
            child.second->position = Lerp(child.second->position, child.second->targetPosition, 1);
        }
        if (move(child.second)) moved = true;
    }
    return moved;
}