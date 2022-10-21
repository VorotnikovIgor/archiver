#pragma once

#include <vector>
#include <queue>
#include <cstdint>
#include <map>

using ExtendedChar = int16_t;
using Code = std::vector<bool>;

class Trie {
    using ExtendedChar = int16_t;
    using Code = std::vector<bool>;

public:
    class Node {
    public:
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        Node* parent_ = nullptr;
        size_t freq_ = 0;
        bool term_ = true;
        ExtendedChar symbol_;

        explicit Node(std::pair<ExtendedChar, size_t> pair);
        Node(Node* left, Node* right);
        explicit Node(Node* parent);
        ~Node();
    };
    explicit Trie(std::map<ExtendedChar, size_t> cnt);
    Trie(std::vector<ExtendedChar>& letters, std::vector<int>& cnt_sizes);
    ~Trie();
    std::map<ExtendedChar, Code> GetCode();
    void DfsGetCode(Node* cur_node, Code& cur_code, std::map<ExtendedChar, Code>& result);

private:
    Node* root_ = nullptr;
};
