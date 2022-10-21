#pragma once

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "work_with_files.h"
#include "trie.h"
#include <tuple>

class Encoder {
    using ExtendedChar = int16_t;
    const ExtendedChar FILENAME_END = 256;
    const ExtendedChar ONE_MORE_FILE = 257;
    const ExtendedChar ARCHIVE_END = 258;
    std::vector<std::string> files_;

public:
    Encoder(std::vector<std::string> files) : files_(files) {
    }
    std::map<ExtendedChar, size_t> GetCntOfSymbols() {
        std::map<ExtendedChar, size_t> cnt;
        cnt[FILENAME_END] = files_.size();
        if (files_.size() >= 2) {
            cnt[ONE_MORE_FILE] = files_.size() - 1;
        }
        cnt[ARCHIVE_END] = 1;
        for (const auto& file : files_) {
            for (const auto& symbol : file) {
                ++cnt[symbol];
            }
            auto fl = FileToRead(file);
            fl.CountSymbolsInFile(cnt);
        }
        return cnt;
    }

    void Increase(std::vector<bool>& vec) {
        size_t idx = vec.size() - 1;
        while (vec[idx]) {
            vec[idx] = false;
            idx--;
        }
        vec[idx] = true;
    }

    std::map<ExtendedChar, std::vector<bool>> GetCanonicalCodes() {
        std::map<ExtendedChar, std::vector<bool>> codes = Trie(GetCntOfSymbols()).GetCode();
        std::map<ExtendedChar, std::vector<bool>> result;
        std::vector<std::pair<ExtendedChar, std::vector<bool>>> new_pairs;
        new_pairs.reserve(codes.size());
        for (const auto& pair : codes) {
            new_pairs.push_back(pair);
        }
        auto cmp = [](const std::pair<ExtendedChar, std::vector<bool>>& a,
                      const std::pair<ExtendedChar, std::vector<bool>>& b) {
            return a.second.size() < b.second.size() || (a.second.size() == b.second.size() && a.second < b.second);
        };
        sort(new_pairs.begin(), new_pairs.end(), cmp);
        std::vector<bool> cur_code;
        size_t cur_let = 0;
        while (cur_let < codes.size()) {
            while (cur_code.size() < new_pairs[cur_let].second.size()) {
                cur_code.push_back(false);
            }
            new_pairs[cur_let].second = cur_code;
            ++cur_let;
            if (cur_let < codes.size()) {
                Increase(cur_code);
            }
        }
        for (const auto& pair : new_pairs) {
            result.insert(pair);
        }
        return result;
    }
};