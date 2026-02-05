//
// Created by lenny on 22.01.2026.
//

#ifndef VBOUND_TEXTRENDERER_H
#define VBOUND_TEXTRENDERER_H

#define SDL3PP_TextRenderer

#include "SDL3++.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL3_ttf/SDL_ttf.h>

#include <JFLX/logging.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace JFLX::sdl3PP {
    class TextRenderer {
        private:
            SDL_Renderer* defaultRenderer = nullptr;
            std::vector<TTF_Font*> fonts = {};
            std::unordered_map<std::string, int> fontLayer = {};

        public:
        TextRenderer();
        TextRenderer(SDL_Renderer* r);
        ~TextRenderer();

        void setDefaultRenderer(SDL_Renderer* renderer);


        [[nodiscard]] TTF_Font* getFont(int index) const;
        [[nodiscard]] TTF_Font* getFont(const std::string& fontName) const;

        void loadFont(const std::string& pathToFont);

        /*
         * If defaultWindow and/or defaultRenderer is set, you may leave the nullptr(s).
         * Orientation Table (How to Anchor around x and y) :
         * Left:    -1
         * Center:   0
         * Right:    1
        */
        void drawText(const std::string &text, float fontSize, float x, float y, TTF_Font* font, SDL_Color color = {0, 0, 0, 255}, int orientation = 1, bool outline = false, SDL_Renderer *rRenderer = nullptr) const;

        /*
         * A wrapper for drawText using a index for the font
        */
        void drawText(const std::string &text, float fontSize, float x, float y, int fontIndex, SDL_Color color = {0, 0, 0, 255}, int orientation = 1, bool outline = false, SDL_Renderer *rRenderer = nullptr) const;

        /*
         * A wrapper for drawText using a name index for the font
        */
        void drawText(const std::string &text, float fontSize, float x, float y, const std::string &fontName, SDL_Color color = {0, 0, 0, 255}, int orientation = 1, bool outline = false, SDL_Renderer *rRenderer = nullptr) const;

        void cleanUp();
    };
}


#endif //VBOUND_TEXTRENDERER_H