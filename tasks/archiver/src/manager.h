#pragma once

#include "parser.h"
#include "encoder.h"
#include "decoder.h"
#include <iostream>

void Manager(int argc, char** argv) {
    Parser parser(argc, argv);
    if (!parser.CheckIfCorrect()) {
        std::cout << parser.GetMessage();
        return;
    }
    Parser::Mode cur_mode = parser.GetMode();
    if (cur_mode == Parser::Mode::encode) {
        Encoder encoder(parser.files_, parser.archive_name_);
        encoder.Archive();
    } else if (cur_mode == Parser::Mode::decode) {
        Decoder decoder(parser.archive_name_);
        decoder.Unzip();
    } else {
        std::cout
            << "Enter:\narchive -c archive_name file1 [file2 ..]\nto archive files file1, file2, ... and save the "
               "result to archive_name\narchive -d archive_name\nto unzip files from archive archive_name and put them "
               "in the current directory";
    }
};
