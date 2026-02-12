//
// Created by lr6549 on 2/1/26.
//

#include "WidgetCommand.hpp"

void JFLX::sdl3PP::WidgetCommand::setCommand(void (&command)()) {
    wCommand = command;
}

