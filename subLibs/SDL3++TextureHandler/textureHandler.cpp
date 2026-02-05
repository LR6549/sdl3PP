//
// Created by lenny on 21.01.2026.
//

#include "textureHandler.hpp"

#include <algorithm>
#include <iostream>

bool JFLX::sdl3PP::textureHandler::loadTextureFolder(const std::string& folderPath) {
    cleanup();

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Texture folder does not exist: " << folderPath << "\n";
        return false;
    }

    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }

    if (files.empty()) {
        std::cerr << "Texture folder is empty: " << folderPath << "\n";
        return false;
    }

    std::ranges::sort(files);

    for (const auto& file : files) {
        sf::Texture tex;
        if (!tex.loadFromFile(file.string())) {
            std::cerr << "Failed to load texture: " << file << "\n";
            cleanup();
            return false;
        }

        textureLayers[file.stem().string()] =
            static_cast<int>(textures.size());

        textures.push_back(std::move(tex));
    }

    return true;
}

int JFLX::sdl3PP::textureHandler::getTextureLayer(const std::string& name) const {
    auto it = textureLayers.find(name);
    return (it == textureLayers.end()) ? -1 : it->second;
}

const sf::Texture* JFLX::sdl3PP::textureHandler::getTexture(int layer) const {
    if (layer < 0 || layer >= static_cast<int>(textures.size())) {
        return nullptr;
    }
    return &textures[layer];
}

void JFLX::sdl3PP::textureHandler::cleanup() {
    textures.clear();
    textureLayers.clear();
}
