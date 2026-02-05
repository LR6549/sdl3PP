//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_AUDIOHANDLER_H
#define VBOUND_AUDIOHANDLER_H

#define SDL3PP_AudioHandler
#include "SDL3++.hpp"


#include <string>
#include <unordered_map>
#include <filesystem>
#include <JFLX/logging.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL3_mixer/SDL_mixer.h>

namespace fs = std::filesystem;

namespace JFLX::sdl3PP {
    class AudioHandler {
    public:
        AudioHandler();
        ~AudioHandler();

        //* Load all sounds and music from the folders
        bool loadSounds(const std::string& path); // path = game root
        bool loadMusic(const std::string& path);

        //* Play a sound effect by name
        void playSound(const std::string& soundName);

        //* Play music track, fading out previous if needed
        void playMusic(const std::string& musicName, int fadeInMs = 2000);

        //* Stop music immediately or with fade out
        void stopMusic(int fadeOutMs = 1000) const;

        //* Check existence
        bool hasSound(const std::string& soundName) const;
        bool hasMusic(const std::string& musicName) const;

    private:
        std::unordered_map<std::string, MIX_Audio*> soundMap;
        std::unordered_map<std::string, MIX_Audio*> musicMap;

        MIX_Mixer* musicMixer = nullptr;
        MIX_Mixer* soundMixer = nullptr;
        MIX_Track* musicTrack = nullptr;

        //* Helper for cleanup
        void clear();
    };
}


#endif //VBOUND_AUDIOHANDLER_H