#pragma once

#include <fstream>
#include <vector>
#include <map>
#include <iostream>

using ExtendedChar = uint16_t;
const size_t CHAR_SIZE = 8;
const size_t EXTENDED_CHAR_SIZE = 9;
const ExtendedChar FILENAME_END = 256;
const ExtendedChar ONE_MORE_FILE = 257;
const ExtendedChar ARCHIVE_END = 258;

class FileToRead {
    std::ifstream file_;
    static const size_t BUF_SIZE = 1024;
    char buffer_[BUF_SIZE];
    size_t last_size_ = BUF_SIZE;
    size_t cur_byte_ = 0;
    size_t cur_bit_ = 7;

public:
    void ReadBuf();

    explicit FileToRead(const std::string& file_name);

    void CountSymbolsInFile(std::map<ExtendedChar, size_t>& cnt);

    bool GetByte(char& c);

    bool GetBit();

    ExtendedChar GetExtendedChar();
};

class FileToWrite {
    std::fstream file_;
    static const size_t BUF_SIZE = 8;
    std::vector<bool> buffer_;

public:
    explicit FileToWrite(const std::string& file_name);

    void WriteBuf();

    void WriteBit(bool bit);

    void WriteCode(const std::vector<bool>& vec);

    void WriteExtendedChar(ExtendedChar a);

    void WriteFile(const std::string& file_name, std::map<ExtendedChar, std::vector<bool>>& canonical);

    void WriteByte(char c);
};
