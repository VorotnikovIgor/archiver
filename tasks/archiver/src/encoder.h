#pragma once

#include "work_with_files.h"
#include "trie.h"

using ExtendedChar = uint16_t;

class Encoder {
    std::vector<std::string> files_;
    std::string archive_name_;
    std::vector<ExtendedChar> canonical_let_order_;
    std::vector<size_t> sizes_;

public:
    explicit Encoder(std::vector<std::string> files, std::string archive_name);
    std::map<ExtendedChar, size_t> GetCntOfSymbols(const std::string& file) const;
    void Increase(std::vector<bool>& vec) const;
    std::map<ExtendedChar, std::vector<bool>> GetCanonicalCodes(const std::string& file);
    void Archive();
};