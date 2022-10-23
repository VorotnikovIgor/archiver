#include "decoder.h"

Decoder::Decoder(std::string file_name) : archive_name(file_name) {
}

void Decoder::Unzip() const {
    FileToRead archive(archive_name);
    ExtendedChar next_extended_char = 0;
    while (next_extended_char != ARCHIVE_END) {
        size_t cnt_let = archive.GetExtendedChar();
        std::vector<ExtendedChar> let_order(cnt_let);
        for (size_t i = 0; i < cnt_let; ++i) {
            let_order[i] = archive.GetExtendedChar();
        }
        size_t sum_of_sizes = 0;
        std::map<size_t, size_t> sizes;
        size_t cur_size = 1;
        while (sum_of_sizes < cnt_let) {
            ExtendedChar new_size = archive.GetExtendedChar();
            sizes[cur_size] += new_size;
            sum_of_sizes += new_size;
            ++cur_size;
        }
        Trie trie(let_order, sizes);
        next_extended_char = trie.GetNextSymbol(archive);
        std::string new_filename;
        while (next_extended_char != FILENAME_END) {
            new_filename += static_cast<char>(next_extended_char);
            next_extended_char = trie.GetNextSymbol(archive);
        }
        FileToWrite to_write(new_filename);
        next_extended_char = trie.GetNextSymbol(archive);
        while (next_extended_char != ONE_MORE_FILE && next_extended_char != ARCHIVE_END) {
            to_write.WriteByte(static_cast<char>(next_extended_char));
            next_extended_char = trie.GetNextSymbol(archive);
        }
    }
}