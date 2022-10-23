#pragma once

#include <vector>
#include <map>
#include "work_with_files.h"

using ExtendedChar = uint16_t;

class Trie {

public:
    class Node {
    public:
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        Node* parent_ = nullptr;
        size_t freq_ = 0;
        bool term_ = false;
        ExtendedChar symbol_;

        explicit Node(std::pair<ExtendedChar, size_t> pair);
        Node(Node* left, Node* right);
        Node() {
        }
        explicit Node(Node* parent);
        ~Node();
    };
    explicit Trie(std::map<ExtendedChar, size_t> cnt);
    Trie(std::vector<ExtendedChar>& letters, std::map<size_t, size_t>& cnt_sizes);
    ~Trie();
    void GetCode(std::map<ExtendedChar, std::vector<bool>>&) const;
    void DfsGetCode(Node* cur_node, std::vector<bool>& cur_code,
                    std::map<ExtendedChar, std::vector<bool>>& result) const;
    ExtendedChar GetNextSymbol(FileToRead& archive) const;

private:
    Node* root_ = nullptr;
};
