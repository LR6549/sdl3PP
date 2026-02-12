//
// Created by lr6549 on 2/1/26.
//

#ifndef SDL3_WIDGETS_WIDGETCOMMAND_HPP
#define SDL3_WIDGETS_WIDGETCOMMAND_HPP

#define SDL3PP_WidgetHandler
#include "SDL3++.hpp"



namespace JFLX::sdl3PP {
    class Widget;
    void voidNullptr();

    class WidgetCommand {
    private:

    public:
        void (*wCommand)();
        void* args = nullptr;

        WidgetCommand(void (&command)() = voidNullptr);

        void setCommand(void (&command)());

        void setArgs();

        void runCommand(Widget* widget);
    };
}


#endif //SDL3_WIDGETS_WIDGETCOMMAND_HPP