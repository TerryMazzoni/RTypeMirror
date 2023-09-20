/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlMusic
*/

#include "RlMusic.hpp"

namespace Raylib
{
    void RlMusic::unload()
    {
        UnloadMusicStream(_music);
    }

    void RlMusic::play()
    {
        PlayMusicStream(_music);
    }

    void RlMusic::stop()
    {
        StopMusicStream(_music);
    }

    void RlMusic::setVolume(float volume)
    {
        SetMusicVolume(_music, volume);
    }

    void RlMusic::update()
    {
        UpdateMusicStream(_music);
    }

    RlMusic::RlMusic(std::string path)
    {
        _music = LoadMusicStream(path.c_str());
    }

    RlMusic::~RlMusic()
    {
    }
}
