#pragma once

#include "parser.h"
#include "encoder.h"
#include "decoder.h"
#include <iostream>

void Manager(){
    Parser parser;
    if (!parser.CheckIfCorrect()) {
        std::cout<<parser.GetMessage();
        return;
    }
    Parser::Mode cur_mode = parser.GetMode();
    if (cur_mode == Parser::Mode::encode){

    } else if (cur_mode == Parser::Mode::decode){

    } else {

    }
};