#pragma once

#include <fstream>
#include <vector>
#include <map>

using ExtendedChar = int16_t;

class FileToRead{
    std::ifstream file_;
    std::vector<bool> buffer_;
public:
    explicit FileToRead(const std::string& file_name) : file_(file_name, std::ios_base::in){
    }
    void CountSymbolsInFile(std::map<ExtendedChar, size_t>& cnt){
        if (!file_.is_open()){
            std::cout<<"NO\n";
        }
        std::string line;
        while (std::getline(file_, line)){
            for (const auto& symbol: line){
                ++cnt[symbol];
            }
        }
    }
};

class FileToWrite{
    std::ofstream file_;
public:
    explicit FileToWrite(const std::string& file_name) : file_(file_name, std::ios_base::out){
    }


};
