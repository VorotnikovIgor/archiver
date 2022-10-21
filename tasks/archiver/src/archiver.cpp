#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "trie.h"
#include "encoder.h"

void Print(std::map<ExtendedChar, std::vector<bool>> codes) {
    for (const auto& pair : codes) {
        if (pair.first < 256) {
            std::cout << static_cast<char>(pair.first) << ": ";
        } else {
            std::cout << pair.first << ": ";
        }
        for (const auto& c : pair.second) {
            std::cout << c;
        }
        std::cout << '\n';
    }
}

int main(int argc, char** argv) {
    /*std::map<ExtendedChar, int> cnt;
    cnt[1] = 2;
    cnt[2] = 2;
    cnt[3] = 2;
    cnt[4] = 2;
    cnt[5] = 2;
    Trie t(cnt);
    auto answer = t.GetCode();
    for (const auto& pp: answer){
        std::cout<<pp.first<<": ";
        for (const auto& b:pp.second){
            std::cout<<b <<' ';
        }
        std::cout<<'\n';
    }*/
    std::vector<std::string> file = {"../tasks/archiver/tests/data/forest/forest.mp4"};
    auto ans = Encoder(file).GetCanonicalCodes();
    Print(ans);

    return 0;
}