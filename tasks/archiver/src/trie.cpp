#include "trie.h"

Trie::Node::Node(std::pair<ExtendedChar, size_t> pair) : freq_(pair.second), symbol_(pair.first) {
}

Trie::Node::Node(Node* parent) : parent_(parent) {
}

Trie::Node::Node(Trie::Node* left, Trie::Node* right) {
    left->parent_ = this;
    right->parent_ = this;
    left_ = left;
    right_ = right;
    freq_ = left->freq_ + right->freq_;
    term_ = false;
}

Trie::Trie(std::map<ExtendedChar, size_t> cnt) {
    auto cmp = [](Node* node1, Node* node2) { return node1->freq_ > node2->freq_; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);
    for (const auto& pair : cnt) {
        pq.push(new Node(pair));
    }
    while (pq.size() > 1) {
        Node* node1 = pq.top();
        pq.pop();
        Node* node2 = pq.top();
        pq.pop();
        pq.push(new Node(node1, node2));
    }
    root_ = pq.top();
}

Trie::Trie(std::vector<ExtendedChar>& letters, std::vector<int>& cnt_sizes){
    size_t cur_let_size = 1;
    size_t cur_size = 0;
    size_t cur_let = 0;
    Node* cur_node = root_;
    while (cur_let < letters.size()){
        while (!cnt_sizes[cur_let_size]){
            cur_let_size++;
        }
        while (cur_node->left_ && cur_node->right_){
            cur_node = cur_node->parent_;
            --cur_size;
        }
        while (cur_size < cur_let_size){
            if (!cur_node->left_){
                cur_node->right_ = new Node(cur_node);
                cur_node = cur_node->right_;
            } else {
                cur_node->left_ = new Node(cur_node);
                cur_node = cur_node->left_;
            }
            ++cur_size;
        }
        cur_node->symbol_ = letters[cur_let];
        cur_node->term_ = true;
        --cnt_sizes[cur_size];
        ++cur_let;
    }
}

std::map<ExtendedChar, Code> Trie::GetCode() {
    Code cur_code;
    std::map<ExtendedChar, Code> result;
    DfsGetCode(root_, cur_code, result);
    return result;
}

void Trie::DfsGetCode(Node* cur_node, Code& cur_code, std::map<ExtendedChar, Code>& result) {
    if (cur_node->term_) {
        result[cur_node->symbol_] = cur_code;
        cur_code.pop_back();
        return;
    }
    cur_code.push_back(false);
    DfsGetCode(cur_node->left_, cur_code, result);
    cur_code.push_back(true);
    DfsGetCode(cur_node->right_, cur_code, result);
    cur_code.pop_back();
}

Trie::Node::~Node(){
    delete left_;
    delete right_;
}

Trie::~Trie(){
    delete root_;
}