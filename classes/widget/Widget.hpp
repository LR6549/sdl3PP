//
// Created by lr6549 on 2/1/26.
//

#ifndef SDL3_WIDGETS_WIDGET_HPP
#define SDL3_WIDGETS_WIDGET_HPP

#define SDL3PP_WidgetHandler
#include "SDL3++.hpp"

#include <memory>
#include <JFLX/logging.hpp>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include "widget/widgetCommand/WidgetCommand.hpp"

namespace JFLX::sdl3PP {
    class WidgetCommand;

    class Widget {
    public: //! Maybe make private, yet it would restrict user accessibility!
        int wWidgetID;

        float wX = 0.0f;
        float wY = 0.0f;
        float wWidth  = 0.0f;
        float wHeight = 0.0f;

        SDL_Color wColor  = {255, 255, 255, 255};
        SDL_Color wColorA = {255, 255, 255, 255};
        SDL_Color wColorH = {255, 255, 255, 255};

        SDL_FRect wRect = {wX, wY, wWidth, wHeight};

        bool wIsShown = false;
        bool wIsHovered = false;
        float wActive = 0.0f;
        float wActiveDuration = 0.0f;

        bool wForceHoverActivationMouse = true;
        bool wForceHoverActivationKeyboard = false;

        bool wMouseActivated = false;
        bool wWasPressedMouse = false;
        SDL_MouseButtonFlags wButton = SDL_BUTTON_LEFT;
        bool wKeyboardActivated = false;
        bool wWasPressedKey   = false;
        SDL_Scancode wKey = SDL_SCANCODE_UNKNOWN;

        SDL_Renderer* wRenderer = nullptr;

        std::unique_ptr<WidgetCommand> wWidgetCommand;

        Widget(int widgetID, float x, float y, float width, float height, std::unique_ptr<WidgetCommand> widgetCommand);

        void updateRect();

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        void setPosition(float x, float y, float width, float height);
        void setColor(SDL_Color color, SDL_Color colorH, SDL_Color colorA);
        void setVisibility(bool shown);
        void setActiveDuration(float duration);
        void setWidgetCommand(std::unique_ptr<WidgetCommand> widgetCommand);
        void setActivation(bool useButton = false, bool forceHoverActivationMouse = true, SDL_MouseButtonFlags button = SDL_BUTTON_LEFT, bool useKey = false, bool forceHoverActivationKeyboard = false, SDL_Scancode key = SDLK_UNKNOWN);


        void draw();
        void draw(SDL_Renderer* r);

        void update();
    };

    std::vector<std::unique_ptr<Widget>> widgets;

    bool initWidgets();

    void updateWidgets(SDL_Window* w);
}

#endif // SDL3_WIDGETS_WIDGET_HPP
