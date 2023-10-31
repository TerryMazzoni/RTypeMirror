/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlMusic
*/

#include "RlMusic.hpp"

namespace Raylib
{

    void RlMusic::play()
    {
        PlayMusicStream(_music);
        SetMusicVolume(_music, 50.0);
    }

    void RlMusic::stop()
    {
        StopMusicStream(_music);
    }

    bool RlMusic::isPlaying()
    {
        return IsMusicStreamPlaying(_music);
    }

    void RlMusic::setVolume(float volume)
    {
        SetMusicVolume(_music, volume);
    }

    void RlMusic::update()
    {
        UpdateMusicStream(_music);
    }

    void RlMusic::setLoop(bool loop)
    {
        _music.looping = loop;
    }

    RlMusic::RlMusic(const std::string path)
    {
        _music = LoadMusicStream(path.c_str());
    }

    RlMusic::~RlMusic()
    {
        UnloadMusicStream(_music);
    }
}
