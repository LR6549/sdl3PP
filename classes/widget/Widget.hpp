//
// Created by lr6549 on 2/1/26.
//

#ifndef SDL3_WIDGETS_WIDGET_HPP
#define SDL3_WIDGETS_WIDGET_HPP

#define SDL3PP_WidgetHandler
#include "SDL3++.hpp"

#include <memory>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace JFLX::sdl3PP {
    class WidgetCommand;

    class Widget {
    public: //! Maybe make private, yet it would restrict user accessibility!
        float wX = 0.0f;
        float wY = 0.0f;
        float wWidth  = 0.0f;
        float wHeight = 0.0f;

        bool wIsShown = false;
        bool wIsHovered = false;

        SDL_Renderer* wRenderer = nullptr;

        std::unique_ptr<WidgetCommand> wWidgetCommand;

        Widget(float x, float y, float width, float height, std::unique_ptr<WidgetCommand> widgetCommand);

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        void setPosition(float x, float y, float width, float height);
        void setWidgetCommand(std::unique_ptr<WidgetCommand> widgetCommand);

        void isShown(bool shown);
        void isHovered(bool hovered);

        void draw();
        void draw(SDL_Renderer* r);

        void update();
    };

}

#endif // SDL3_WIDGETS_WIDGET_HPP
