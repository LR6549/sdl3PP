//
// Created by lr6549 on 2/1/26.
//

#include "Widget.hpp"
#include "widgetCommand/WidgetCommand.hpp"

/*
 * Constructor Functions
*/

// Constructor: initializes position, size, and assigns the widget's command
JFLX::sdl3PP::Widget::Widget(const int widgetID, const float x, const float y, const float width, const float height, std::unique_ptr<WidgetCommand> widgetCommand) : wWidgetID(widgetID), wX(x), wY(y), wWidth(width), wHeight(height), wWidgetCommand(std::move(widgetCommand)) {}

/*
 * Void Functions
*/


// Rebuilds the SDL_FRect from the current position and size members
void JFLX::sdl3PP::Widget::updateRect() {
    wRect = { wX, wY, wWidth, wHeight };
}


/*
 * Get Functions
*/

int JFLX::sdl3PP::Widget::getWidgetID() const {
    return wWidgetID;
}

float JFLX::sdl3PP::Widget::getX() const {
    return wX;
}
float JFLX::sdl3PP::Widget::getY() const {
    return wX;
}

float JFLX::sdl3PP::Widget::getWidth() const {
    return wWidth;
}

float JFLX::sdl3PP::Widget::getHeight() const {
    return wHeight;
}

SDL_Color JFLX::sdl3PP::Widget::getColor() const {
    return wColor;
}

SDL_Color JFLX::sdl3PP::Widget::getColorH() const {
    return wColorH;
}

SDL_Color JFLX::sdl3PP::Widget::getColorA() const {
    return wColorA;
}

float JFLX::sdl3PP::Widget::getActiveDuration() const {
    return wActiveDuration;
}

JFLX::sdl3PP::WidgetCommand* JFLX::sdl3PP::Widget::getWidgetCommand() const {
    return wWidgetCommand.get();
}

/*
 * Set Functions
*/

// Sets the X position and refreshes the rect
void JFLX::sdl3PP::Widget::setX(const float x) {
    wX = x;
    updateRect();
}

// Sets the Y position and refreshes the rect
void JFLX::sdl3PP::Widget::setY(const float y) {
    wY = y;
    updateRect();
}

// Sets the width and refreshes the rect
void JFLX::sdl3PP::Widget::setWidth(const float width) {
    wWidth = width;
    updateRect();
}

// Sets the height and refreshes the rect
void JFLX::sdl3PP::Widget::setHeight(const float height) {
    wHeight = height;
    updateRect();
}

// Sets position and size in one call and refreshes the rect
void JFLX::sdl3PP::Widget::setPosition(const float x, const float y, const float width, const float height) {
    wX = x;
    wY = y;
    wWidth = width;
    wHeight = height;
    updateRect();
}

// Sets the three display colors: normal, hovered, and active (just triggered)
void JFLX::sdl3PP::Widget::setColor(const SDL_Color color, const SDL_Color colorH, const SDL_Color colorA) {
    wColor = color;
    wColorH = colorH;
    wColorA = colorA;
}

// Sets how long (in update ticks) the active color is shown after a command fires
void JFLX::sdl3PP::Widget::setActiveDuration(const float duration) {
    wActiveDuration = duration;
}

// Shows or hides the widget
void JFLX::sdl3PP::Widget::setVisibility(const bool shown) {
    wIsShown = shown;
}


// Replaces the current widget command with a new one
void JFLX::sdl3PP::Widget::setWidgetCommand(std::unique_ptr<WidgetCommand> widgetCommand) {
    wWidgetCommand = std::move(widgetCommand);
}


// Configures how the widget is triggered:
//   useButton                      -> fire command on mouse button press
//   forceHoverActivationMouse      -> only fire mouse command when hovered
//   forceClickPressMouse           -> click or hold activation for the key
//   button                         -> which mouse button to listen to
//   useKey                         -> fire command on keyboard key press
//   forceHoverActivationKeyboard   -> only fire keyboard command when hovered
//   forceClickPressKeyboard        -> click or hold activation for the button
//   key                            -> which scancode to listen to
void JFLX::sdl3PP::Widget::setActivation(const bool useButton, const bool forceHoverActivationMouse, const bool forceClickPressMouse, const SDL_MouseButtonFlags button, const bool useKey, const bool forceHoverActivationKeyboard, const bool forceClickPressKeyboard, const SDL_Scancode key) {
    // Mouse
    wMouseActivated = useButton;
    wForceHoverActivationMouse = forceHoverActivationMouse;
    wForceClickPressMouse = forceClickPressMouse;
    wButton = button;
    // Keyboard
    wKeyboardActivated = useKey;
    wForceHoverActivationKeyboard = forceHoverActivationKeyboard;
    wForceClickPressKeyboard = forceClickPressKeyboard;
    wKey = key;
}


/*
 * State Check Functions
*/

bool JFLX::sdl3PP::Widget::isVisible() const {
    return wIsShown;
}

bool JFLX::sdl3PP::Widget::isHovered() const {
    return wIsHovered;
}

bool JFLX::sdl3PP::Widget::isPressed() const {
    return wIsPressed;
}


/*
 * Object Call Functions
*/


// Draws the widget using its internal renderer (wRenderer)
// Color priority: active (just triggered) > hovered > normal
// wActive counts down each draw call until the active color expires
void JFLX::sdl3PP::Widget::draw() {
    SDL_Color color;
    if (wActive > 0.0f) {
        wActive -= 0.1f;
        color = wColorA;
    } else {
        color = wIsHovered ? wColorH : wColor;
    }

    if (!SDL_SetRenderDrawColor(wRenderer, color.r, color.g, color.b, color.a)) {
        JFLX::log(("Could not set renderer Color for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    } else if (!SDL_RenderFillRect(wRenderer, &wRect)) {
        JFLX::log(("Could not fill rectangle for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    } else if (!SDL_RenderPresent(wRenderer)){
        JFLX::log(("Could not render Preset for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }
}

// Draws the widget using an external renderer (e.g. shared scene renderer)
// Same color logic as draw() above
void JFLX::sdl3PP::Widget::draw(SDL_Renderer* r) {
    SDL_Color color;
    if (wActive > 0.0f) {
        wActive -= 0.1f;
        color = wColorA;
    } else {
        color = wIsHovered ? wColorH : wColor;
    }

    if (!SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a)) {
        JFLX::log(("Could not set renderer Color for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    } else if (!SDL_RenderFillRect(r, &wRect)) {
        JFLX::log(("Could not fill rectangle for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    } else if (!SDL_RenderPresent(r)){
        JFLX::log(("Could not render Preset for Widget ["+std::to_string(wWidgetID)+"]") , SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }
}


// Main per-frame update: checks hover, fires input commands, then draws
void JFLX::sdl3PP::Widget::update() {
    float mx, my;
    SDL_GetMouseState(&mx, &my);

    wIsHovered = (mx >= wRect.x && mx <= wRect.x + wRect.w && my >= wRect.y && my <= wRect.y + wRect.h);

    if (wWidgetCommand) {
        if (wMouseActivated) {
            if (!wForceHoverActivationMouse || wForceHoverActivationMouse && wIsHovered) {
                bool pressed = SDL_GetMouseState(nullptr, nullptr) & wButton;
                wIsPressed = false;
                if (pressed && (!wWasPressedMouse || !wForceClickPressMouse)) {
                    wWidgetCommand->runCommand(this);
                    wActive = wActiveDuration;
                    wIsPressed = true;
                }
                wWasPressedMouse = pressed;
            }
        }

        if (wKeyboardActivated && wKey != SDL_SCANCODE_UNKNOWN) {
            if (!wForceHoverActivationKeyboard || wForceHoverActivationKeyboard && wIsHovered) {
                bool pressed = SDL_GetKeyboardState(nullptr)[wKey];
                wIsPressed = false;
                if (pressed && (!wWasPressedKey || !wForceClickPressKeyboard)) {
                    wWidgetCommand->runCommand(this);
                    wActive = wActiveDuration;
                    wIsPressed = true;
                }
                wWasPressedKey = pressed;
            }
        }
    }

    if (wIsShown)
        draw();

}