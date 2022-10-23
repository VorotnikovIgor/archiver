#pragma once

#include "work_with_files.h"
#include "trie.h"

class Decoder {
    std::string archive_name;
    const ExtendedChar FILENAME_END = 256;
    const ExtendedChar ONE_MORE_FILE = 257;
    const ExtendedChar ARCHIVE_END = 258;

public:
    explicit Decoder(std::string file_name);
    void Unzip() const;
};