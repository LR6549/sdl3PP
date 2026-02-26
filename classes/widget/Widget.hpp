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
        bool wIsPressed = false;

        float wActive = 0.0f;
        float wActiveDuration = 0.0f;

        bool wMouseActivated = false;
        bool wForceHoverActivationMouse = true;
        bool wForceClickPressMouse = true;
        bool wWasPressedMouse = false;
        SDL_MouseButtonFlags wButton = SDL_BUTTON_LEFT;

        bool wKeyboardActivated = false;
        bool wForceHoverActivationKeyboard = false;
        bool wForceClickPressKeyboard = false;
        bool wWasPressedKey   = false;
        SDL_Scancode wKey = SDL_SCANCODE_UNKNOWN;

        SDL_Renderer* wRenderer = nullptr;

        std::unique_ptr<WidgetCommand> wWidgetCommand;

        Widget(int widgetID, float x, float y, float width, float height, std::unique_ptr<WidgetCommand> widgetCommand);

        void updateRect();

        int getWidgetID() const;
        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;
        SDL_Color getColor() const;
        SDL_Color getColorH() const;
        SDL_Color getColorA() const;
        float getActiveDuration() const;
        WidgetCommand* getWidgetCommand() const;

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        void setPosition(float x, float y, float width, float height);
        void setColor(SDL_Color color, SDL_Color colorH, SDL_Color colorA);
        void setVisibility(bool shown);
        void setActiveDuration(float duration);
        void setWidgetCommand(std::unique_ptr<WidgetCommand> widgetCommand);
        void setActivation(bool useButton = false, bool forceHoverActivationMouse = true, bool forceClickPressMouse = true, SDL_MouseButtonFlags button = SDL_BUTTON_LEFT, bool useKey = false, bool forceHoverActivationKeyboard = false, bool forceClickPressKeyboard = false, SDL_Scancode key = SDL_SCANCODE_UNKNOWN);

        bool isVisible() const;
        bool isHovered() const;
        bool isPressed() const;

        void draw();
        void draw(SDL_Renderer* r);

        void update();
    };

    inline std::vector<std::unique_ptr<Widget>> widgetVect;

    bool initWidgets();

    void updateWidgets(SDL_Window* w);
}

#endif // SDL3_WIDGETS_WIDGET_HPP
