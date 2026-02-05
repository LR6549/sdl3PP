//
// Created by lenny on 21.01.2026.
//

#include "AudioHandler.hpp"

#include <ranges>
#include <SDL3/SDL.h>
#include <SDL3/SDL3_mixer/SDL_mixer.h>

JFLX::sdl3PP::AudioHandler::AudioHandler() {
    // Initialize SDL_mixer if needed
    if (!MIX_Init()) {
        JFLX::log("Failed to initialize SDL_mixer: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }

    SDL_AudioSpec audioSpec;
    audioSpec.freq = 44100;
    audioSpec.format = SDL_AUDIO_S16LE;
    audioSpec.channels = 2;

    musicMixer = MIX_CreateMixer(&audioSpec);
    soundMixer = MIX_CreateMixer(&audioSpec);

    if (!musicMixer || !soundMixer) {
        JFLX::log("Failed to create audio mixers: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }

    musicTrack = MIX_CreateTrack(musicMixer);
}

JFLX::sdl3PP::AudioHandler::~AudioHandler() {
    clear();

    if (musicTrack) MIX_DestroyTrack(musicTrack);
    if (musicMixer) MIX_DestroyMixer(musicMixer);
    if (soundMixer) MIX_DestroyMixer(soundMixer);

    MIX_Quit();
}

void JFLX::sdl3PP::AudioHandler::clear() {
    for (const auto &audio: soundMap | std::views::values) {
        if (audio) MIX_DestroyAudio(audio);
    }
    soundMap.clear();

    for (const auto &audio: musicMap | std::views::values) {
        if (audio) MIX_DestroyAudio(audio);
    }
    musicMap.clear();
}

bool JFLX::sdl3PP::AudioHandler::loadSounds(const std::string& path) {
    if (!fs::exists(path)) {
        JFLX::log("Sound folder does not exist: ", path, JFLX::LOGTYPE::JFLX_ERROR);
        return false;
    }

    for (const auto& dir : fs::recursive_directory_iterator(path)) {
        if (!dir.is_regular_file() || dir.path().extension() != ".mp3") continue;

        std::string name = dir.path().stem().string();
        std::string file = dir.path().string();

        MIX_Audio* audio = MIX_LoadAudio(soundMixer, file.c_str(), false);
        if (!audio) {
            JFLX::log("Failed to load sound: ", file, JFLX::LOGTYPE::JFLX_ERROR);
            continue;
        }

        soundMap[name] = audio;
        JFLX::log("Loaded sound: ", name, JFLX::LOGTYPE::JFLX_SUCCESS);
    }

    return true;
}

bool JFLX::sdl3PP::AudioHandler::loadMusic(const std::string& path) {
    std::string musicFolder = path + "data/music/";
    if (!fs::exists(musicFolder)) {
        JFLX::log("Music folder does not exist: ", musicFolder, JFLX::LOGTYPE::JFLX_ERROR);
        return false;
    }

    for (const auto& dir : fs::recursive_directory_iterator(musicFolder)) {
        if (!dir.is_regular_file() || dir.path().extension() != ".mp3") continue;

        std::string name = dir.path().stem().string();
        std::string file = dir.path().string();

        MIX_Audio* audio = MIX_LoadAudio(musicMixer, file.c_str(), false);
        if (!audio) {
            JFLX::log("Failed to load music: ", file, JFLX::LOGTYPE::JFLX_ERROR);
            continue;
        }

        musicMap[name] = audio;
        JFLX::log("Loaded music: ", name, JFLX::LOGTYPE::JFLX_SUCCESS);
    }

    return true;
}

void JFLX::sdl3PP::AudioHandler::playSound(const std::string& soundName) {
    const auto it = soundMap.find(soundName);
    if (it == soundMap.cend()) {
        JFLX::log("Sound not found: ", soundName, JFLX::LOGTYPE::JFLX_ERROR);
        return;
    }

    if (MIX_Audio* audio = it->second; MIX_PlayAudio(soundMixer, audio)) {
        JFLX::log("Played sound: ", soundName, JFLX::LOGTYPE::JFLX_SUCCESS);
    } else {
        JFLX::log("MIX_PlayAudio failed: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }
}

void JFLX::sdl3PP::AudioHandler::playMusic(const std::string& name, int fadeInMs) {
    const auto it = musicMap.find(name);
    if (it == musicMap.end()) {
        JFLX::log("Music not found: ", name, JFLX::LOGTYPE::JFLX_ERROR);
        return;
    }

    MIX_Audio* audio = it->second;

    if (musicTrack && MIX_TrackPlaying(musicTrack) && MIX_GetTrackAudio(musicTrack) == audio) {
        JFLX::log("Music already playing: ", name, JFLX::LOGTYPE::JFLX_INFO);
        return;
    }

    if (musicTrack && MIX_TrackPlaying(musicTrack)) {
        stopMusic(3000); // fade out previous track
    }

    MIX_SetTrackAudio(musicTrack, audio);

    SDL_PropertiesID options = SDL_CreateProperties();
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadeInMs);

    if (MIX_PlayTrack(musicTrack, options)) {
        JFLX::log("Playing music: ", name, JFLX::LOGTYPE::JFLX_SUCCESS);
    } else {
        JFLX::log("MIX_PlayTrack failed: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
    }

    SDL_DestroyProperties(options);
}

void JFLX::sdl3PP::AudioHandler::stopMusic(const int fadeOutMs) const {
    if (musicTrack && MIX_TrackPlaying(musicTrack)) {
        const SDL_PropertiesID props = SDL_CreateProperties();
        // Set fade out duration (milliseconds)
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadeOutMs);

        // Stop the track with fade out
        if (!MIX_StopTrack(musicTrack, props)) {
            JFLX::log("Failed to stop track with fade out: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
        }

        SDL_DestroyProperties(props);
    }

}

bool JFLX::sdl3PP::AudioHandler::hasSound(const std::string& soundName) const {
    return soundMap.contains(soundName);
}

bool JFLX::sdl3PP::AudioHandler::hasMusic(const std::string& musicName) const {
    return musicMap.contains(musicName);
}
