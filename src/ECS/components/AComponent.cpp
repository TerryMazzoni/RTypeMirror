/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "RlColor.hpp"
#include "RlTexture.hpp"

namespace ECS
{
    template <>
    ComponentType AComponent<Raylib::RlColor>::getType() const
    {
        return _type;
    }

    template <>
    void AComponent<Raylib::RlColor>::setType(ComponentType type)
    {
        _type = type;
    }

    template <>
    ComponentType AComponent<std::pair<float, float>>::getType() const
    {
        return _type;
    }

    template <>
    void AComponent<std::pair<float, float>>::setType(ComponentType type)
    {
        _type = type;
    }

    template <>
    ComponentType AComponent<float>::getType() const
    {
        return _type;
    }

    template <>
    void AComponent<float>::setType(ComponentType type)
    {
        _type = type;
    }

    template <>
    ComponentType AComponent<std::string>::getType() const
    {
        return _type;
    }

    template <>
    void AComponent<std::string>::setType(ComponentType type)
    {
        _type = type;
    }

    template <>
    ComponentType AComponent<Raylib::RlTexture>::getType() const
    {
        return _type;
    }

    template <>
    void AComponent<Raylib::RlTexture>::setType(ComponentType type)
    {
        _type = type;
    }
} // namespace ECS
