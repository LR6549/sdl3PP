//
// Created by lr6549 on 2/1/26.
//

#include "Widget.hpp"
#include "widgetCommand/WidgetCommand.hpp"

JFLX::sdl3PP::Widget::Widget(
    float x,
    float y,
    float width,
    float height,
    std::unique_ptr<WidgetCommand> widgetCommand
)
    : wX(x),
      wY(y),
      wWidth(width),
      wHeight(height),
      wWidgetCommand(std::move(widgetCommand))
{
}
