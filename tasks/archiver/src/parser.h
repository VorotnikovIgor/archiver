#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Parser {
public:
    enum Mode { encode, decode, help, not_started };

public:
    std::vector<std::string> files_;
    bool build_ = true;
    std::string message_;
    Mode cur_mode_ = Mode::not_started;
    std::string archive_name_;

public:
    void CheckFiles() {
        std::fstream check;
        check.open(archive_name_, std::ios::in);
        if (!check.is_open()) {
            build_ = false;
            message_ = "File " + archive_name_ + " is not found.\n";
            return;
        }
        check.close();
        for (const auto& file : files_) {
            check.open(file, std::ios::in);
            if (!check.is_open()) {
                build_ = false;
                message_ = "File " + file + " is not found.\n";
                return;
            }
            check.close();
        }
    }

    Parser(int argc, char** sym) {
        if (argc < 2) {
            message_ = "Please enter more arguments.\n";
            build_ = false;
            return;
        }
        if (sym[1][0] == '-') {
            if (sym[1][1] == 'c') {
                cur_mode_ = Mode::encode;
            } else if (sym[1][1] == 'd') {
                cur_mode_ = Mode::decode;
            } else {
                cur_mode_ = Mode::help;
            }
        } else {
            message_ = "Wrong query. Please, try again.\n";
            build_ = false;
        }
        if (!build_) {
            return;
        }
        if (cur_mode_ == Mode::help) {
            return;
        }
        archive_name_ = sym[2];
        for (int i = 3; i < argc; ++i) {
            files_.push_back(sym[i]);
        }
        CheckFiles();
    }

    bool CheckIfCorrect() const {
        return build_;
    }
    std::string GetMessage() const {
        return message_;
    }
    Mode GetMode() const {
        return cur_mode_;
    }
};