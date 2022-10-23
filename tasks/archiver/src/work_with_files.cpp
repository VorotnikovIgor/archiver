#include "work_with_files.h"

void FileToRead::ReadBuf() {
    file_.read(buffer_, BUF_SIZE);
    last_size_ = file_.gcount();
    cur_byte_ = 0;
}

FileToRead::FileToRead(const std::string& file_name) : file_(file_name, std::ios::in | std::ios::binary) {
    ReadBuf();
}

void FileToRead::CountSymbolsInFile(std::map<ExtendedChar, size_t>& cnt) {
    while (last_size_ > 0) {
        for (size_t i = 0; i < last_size_; ++i) {
            unsigned char unsigned_symbol = static_cast<unsigned char>(buffer_[i]);
            ++cnt[unsigned_symbol];
        }
        ReadBuf();
    }
}

bool FileToRead::GetByte(char& c) {
    if (last_size_ == 0) {
        return false;
    }
    c = buffer_[cur_byte_];
    ++cur_byte_;
    if (cur_byte_ == last_size_) {
        ReadBuf();
    }
    return true;
}

bool FileToRead::GetBit() {
    if (cur_byte_ >= last_size_) {
        ReadBuf();
    }
    bool ans = (buffer_[cur_byte_] >> (cur_bit_)&1);
    cur_bit_ = (cur_bit_ + CHAR_SIZE - 1) % CHAR_SIZE;
    if (cur_bit_ == CHAR_SIZE - 1) {
        ++cur_byte_;
    }
    return ans;
}

ExtendedChar FileToRead::GetExtendedChar() {
    ExtendedChar res = 0;
    for (size_t i = 0; i < EXTENDED_CHAR_SIZE; ++i) {
        res += (1 << (EXTENDED_CHAR_SIZE - 1 - i)) * GetBit();
    }
    return res;
}

FileToWrite::FileToWrite(const std::string& file_name) {
    file_.open(file_name, std::ios::out | std::ios::binary);
}

void FileToWrite::WriteBuf() {
    while (buffer_.size() % CHAR_SIZE != 0) {
        buffer_.push_back(false);
    }
    unsigned char result = 0;
    for (size_t i = 0; i < CHAR_SIZE; ++i) {
        result += buffer_[i] * (1 << (CHAR_SIZE - 1 - i));
    }
    file_ << result;
    buffer_.clear();
}

void FileToWrite::WriteBit(bool bit) {
    buffer_.push_back(bit);
    if (buffer_.size() == BUF_SIZE) {
        WriteBuf();
    }
}

void FileToWrite::WriteCode(const std::vector<bool>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        WriteBit(vec[i]);
    }
}

void FileToWrite::WriteExtendedChar(ExtendedChar a) {
    for (size_t i = 0; i < EXTENDED_CHAR_SIZE; ++i) {
        WriteBit(((a >> (EXTENDED_CHAR_SIZE - 1 - i)) & 1));
    }
}

void FileToWrite::WriteFile(const std::string& file_name, std::map<ExtendedChar, std::vector<bool>>& canonical) {
    for (const auto& c : file_name) {
        WriteCode(canonical[c]);
    }
    WriteCode(canonical[FILENAME_END]);
    FileToRead input(file_name);
    char c = 0;
    while (input.GetByte(c)) {
        unsigned char unsigned_symbol = static_cast<unsigned char>(c);
        WriteCode(canonical[unsigned_symbol]);
    }
}

void FileToWrite::WriteByte(char c) {
    file_ << c;
}