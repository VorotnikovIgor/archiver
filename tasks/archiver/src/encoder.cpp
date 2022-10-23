#include "encoder.h"
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

Encoder::Encoder(std::vector<std::string> files, std::string archive_name)
    : files_(files), archive_name_(archive_name) {
}

std::map<ExtendedChar, size_t> Encoder::GetCntOfSymbols(const std::string& file) const {
    std::map<ExtendedChar, size_t> cnt;
    cnt[FILENAME_END] = 1;
    cnt[ONE_MORE_FILE] = 1;
    cnt[ARCHIVE_END] = 1;
    for (const auto& symbol : file) {
        unsigned char unsigned_symbol = static_cast<unsigned char>(symbol);
        ++cnt[unsigned_symbol];
    }
    auto fl = FileToRead(file);
    fl.CountSymbolsInFile(cnt);
    return cnt;
}

void Encoder::Increase(std::vector<bool>& vec) const {
    size_t idx = vec.size() - 1;
    while (vec[idx]) {
        vec[idx] = false;
        idx--;
    }
    vec[idx] = true;
}

std::map<ExtendedChar, std::vector<bool>> Encoder::GetCanonicalCodes(const std::string& file) {
    std::map<ExtendedChar, std::vector<bool>> codes;
    Trie(GetCntOfSymbols(file)).GetCode(codes);
    // Print(codes);
    std::map<ExtendedChar, std::vector<bool>> result;
    std::vector<std::pair<ExtendedChar, std::vector<bool>>> new_pairs;
    new_pairs.reserve(codes.size());
    for (const auto& pair : codes) {
        new_pairs.push_back(pair);
    }
    auto cmp = [](const std::pair<ExtendedChar, std::vector<bool>>& a,
                  const std::pair<ExtendedChar, std::vector<bool>>& b) {
        return a.second.size() < b.second.size() || (a.second.size() == b.second.size() && a.first < b.first);
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
    sizes_.resize(new_pairs.back().second.size());
    for (const auto& pair : new_pairs) {
        result.insert(pair);
        canonical_let_order_.push_back(pair.first);
        ++sizes_[pair.second.size() - 1];
    }
    return result;
}

void Encoder::Archive() {
    FileToWrite output(archive_name_);
    for (size_t i = 0; i < files_.size(); ++i) {
        auto file_name = files_[i];
        std::map<ExtendedChar, std::vector<bool>> canonical = GetCanonicalCodes(file_name);
        output.WriteExtendedChar(canonical.size());
        for (const auto& symbol : canonical_let_order_) {
            output.WriteExtendedChar(symbol);
        }
        for (const auto& num_with_size : sizes_) {
            output.WriteExtendedChar(num_with_size);
        }
        output.WriteFile(file_name, canonical);
        if (i != files_.size() - 1) {
            output.WriteCode(canonical[ONE_MORE_FILE]);
        } else {
            output.WriteCode(canonical[ARCHIVE_END]);
        }
        canonical_let_order_.clear();
        sizes_.clear();
    }
    output.WriteBuf();
}
