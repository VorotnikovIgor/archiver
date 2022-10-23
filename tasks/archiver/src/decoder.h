#pragma once

#include "work_with_files.h"
#include "trie.h"

class Decoder {
    std::string archive_name;

public:
    explicit Decoder(std::string file_name);
    void Unzip() const;
};