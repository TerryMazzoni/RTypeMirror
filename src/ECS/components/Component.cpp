/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#include "Component.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "Scale.hpp"
#include "Text.hpp"
#include "Texture.hpp"

namespace ECS {
    template <typename T>
    Component<T>::Component(std::any value)
    {
        _value = std::any_cast<T>(value);
    }

    template <typename T>
    int Component<T>::setValue(std::any value)
    {
        _value = std::any_cast<T>(value);
        return 0;
    }

    template <typename T>
    std::any Component<T>::getValue() const
    {
        return _value;
    }

    template <typename T>
    ComponentType Component<T>::getType() const
    {
        return _type;
    }

    template <typename T>
    void Component<T>::setType(ComponentType type)
    {
        _type = type;
    }
} // namespace ECS

template class ECS::Component<ECS::Color>;
template class ECS::Component<ECS::Position>;
template class ECS::Component<ECS::Rotation>;
template class ECS::Component<ECS::Scale>;
template class ECS::Component<ECS::Text>;
template class ECS::Component<ECS::Texture>;
