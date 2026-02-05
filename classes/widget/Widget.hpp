//
// Created by lr6549 on 2/1/26.
//

#ifndef SDL3_WIDGETS_WIDGET_HPP
#define SDL3_WIDGETS_WIDGET_HPP

#define SDL3PP_WidgetHandler
#include "SDL3++.hpp"

#include <memory>

namespace JFLX::sdl3PP {
    class WidgetCommand;

    class Widget {
    public:
        float wX = 0.0f;
        float wY = 0.0f;
        float wWidth  = 0.0f;
        float wHeight = 0.0f;

        bool wIsHovered = false;

        std::unique_ptr<WidgetCommand> wWidgetCommand;

        Widget(float x, float y, float width, float height, std::unique_ptr<WidgetCommand> widgetCommand);
    };

}

#endif // SDL3_WIDGETS_WIDGET_HPP
