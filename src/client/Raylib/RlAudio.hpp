/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlAudio
*/

#pragma once

extern "C" {
    #include "raylib.h"
}

namespace Raylib {
    /**
     * @brief Function to initialize audio device
     *
     */
    void initAudioDevice();
    /**
     * @brief Function to close audio device
     *
     */
    void closeAudioDevice();
    /**
     * @brief Function to set master volume
     *
     * @param volume Master volume to set
     */
    void setMasterVolume(float volume);
} // namespace Raylib
