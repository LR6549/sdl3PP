//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_TEXTUREHANDLER_H
#define VBOUND_TEXTUREHANDLER_H

#define SDL3PP_TextureHandler
#include "SDL3++.hpp"


#include <unordered_map>
#include <string>
#include <filesystem>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

namespace fs = std::filesystem;

namespace JFLX::sdl3PP {

    class textureHandler {
    private:
        std::vector<sf::Texture> textures;
        std::unordered_map<std::string, int> textureLayers;

    public:
        bool loadTextureFolder(const std::string& folderPath);

        [[nodiscard]] int layers() const {
            return static_cast<int>(textures.size());
        }

        int getTextureLayer(const std::string& name) const;

        const sf::Texture* getTexture(int layer) const;

        void cleanup();
    };

}

#endif
