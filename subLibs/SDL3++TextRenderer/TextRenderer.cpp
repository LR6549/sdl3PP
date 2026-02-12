//
// Created by lenny on 22.01.2026.
//

#include "TextRenderer.hpp"

JFLX::sdl3PP::TextRenderer::TextRenderer() = default;

JFLX::sdl3PP::TextRenderer::TextRenderer(SDL_Renderer* r) : defaultRenderer(r) {};

JFLX::sdl3PP::TextRenderer::~TextRenderer() {
    cleanUp();
}

void JFLX::sdl3PP::TextRenderer::setDefaultRenderer(SDL_Renderer *renderer) {
    defaultRenderer = renderer;
}

TTF_Font* JFLX::sdl3PP::TextRenderer::getFont(int index) const {
    if (index >= fonts.size()) {
        return nullptr;
    } return fonts[index];
}

TTF_Font* JFLX::sdl3PP::TextRenderer::getFont(const std::string& fontName) const {
    if (!fontIndex.contains(fontName)) {
        return nullptr;
    } return fonts[fontIndex.at(fontName)];
}

void JFLX::sdl3PP::TextRenderer::loadFont(const std::string &pathToFont) {
    TTF_Font* tempFont = TTF_OpenFont(pathToFont.c_str(), 32);
    if (!tempFont) {
        JFLX::log("Failed to load font ", (pathToFont + ", " + SDL_GetError()), JFLX::LOGTYPE::JFLX_ERROR);
        exit(1);
    }
    int index = fonts.size();
    fonts.push_back(tempFont);
}

void JFLX::sdl3PP::TextRenderer::drawText(const std::string& text, float fontSize, float x, float y, TTF_Font* font, const SDL_Color color, int orientation, bool outline, SDL_Renderer* rRenderer) const {
    if (!font) {
        JFLX::log("Font is nullptr: ", "", JFLX::LOGTYPE::JFLX_ERROR);
        return;
    }

    //* Render the text onto a surface
    if (SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), color); surface) {

        SDL_Renderer* renderer = !rRenderer ? defaultRenderer : rRenderer;

        SDL_DestroySurface(surface);

        if (SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); texture) {
            float textW, textH;
            SDL_GetTextureSize(texture, &textW, &textH);

            // Position based on orientation
            SDL_FRect dstRect;
            dstRect.w = (float)textW;
            dstRect.h = (float)textH;

            if (orientation == 0)       dstRect.x = x - (textW / 2.0f);
            else if (orientation == -1) dstRect.x = x - textW;
            else                        dstRect.x = x;

            dstRect.y = y;

            // Shadow first
            if (outline) {
                SDL_Surface* outlineSurface = TTF_RenderText_Blended(font, text.c_str(), text.size(), {0, 0, 0, 255});
                SDL_Texture* outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
                SDL_DestroySurface(outlineSurface);

                if (outlineTexture) {
                    SDL_FRect outlineRect = dstRect;

                    //* Offset in relation der fontSize
                    float offset = fontSize / 6.5f;

                    //* All directions around the texture (for an Outline)
                    const SDL_FPoint offsets[] = {
                        {-offset, -offset}, {0, -offset}, {offset, -offset},
                        {-offset,  0},                  {offset,  0},
                        {-offset,  offset}, {0,  offset}, {offset,  offset}
                    };

                    for (auto& o : offsets) {
                        outlineRect.x = dstRect.x + o.x;
                        outlineRect.y = dstRect.y + o.y;
                        SDL_RenderTexture(renderer, outlineTexture, nullptr, &outlineRect);
                    }

                    SDL_DestroyTexture(outlineTexture);
                }
            }


            //* Draw the text onto the window
            SDL_RenderTexture(renderer, texture, nullptr, &dstRect);

            SDL_DestroyTexture(texture);
        } else {
            JFLX::log("Failed to create text texture: ", SDL_GetError(),  JFLX::LOGTYPE::JFLX_ERROR);
            return;
        }
    } else {
        JFLX::log("Failed to render text: ", SDL_GetError(),  JFLX::LOGTYPE::JFLX_ERROR);
        return;
    }
}

void JFLX::sdl3PP::TextRenderer::drawText(const std::string& text, float fontSize, float x, float y, int fontIndex_, const SDL_Color color, int orientation, bool outline, SDL_Renderer* rRenderer) const {
    TTF_Font* font = getFont(fontIndex_);
    JFLX::sdl3PP::TextRenderer::drawText(text, fontSize, x, y, font, color, orientation, outline, rRenderer);
}

void JFLX::sdl3PP::TextRenderer::drawText(const std::string& text, float fontSize, float x, float y, const std::string&  fontName, const SDL_Color color, int orientation, bool outline, SDL_Renderer* rRenderer) const {
    TTF_Font* font = getFont(fontName);
    JFLX::sdl3PP::TextRenderer::drawText(text, fontSize, x, y, font, color, orientation, outline, rRenderer);
}

void JFLX::sdl3PP::TextRenderer::cleanUp() {
    defaultRenderer = nullptr;

    for (auto& font : fonts) {
        TTF_CloseFont(font);
    }
    fonts.clear();
    fontIndex.clear();
}
