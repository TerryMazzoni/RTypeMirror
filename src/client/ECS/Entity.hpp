/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Entity
*/

#pragma once

#include <vector>
#include <memory>
#include <any>
#include <tuple>
#include "IComponent.hpp"

#define PATH_TEXTURES_PLAYER "assets/player/Layer 1_1.png,assets/player/Layer 1_2.png,assets/player/Layer 1_3.png,assets/player/Layer 1_4.png,assets/player/Layer 1_5.png,assets/player/Layer 1_6.png,assets/player/Layer 2_1.png,assets/player/Layer 2_2.png,assets/player/Layer 2_3.png,assets/player/Layer 2_4.png,assets/player/Layer 2_5.png,assets/player/Layer 2_6.png,assets/player/Layer 3_1.png,assets/player/Layer 3_2.png,assets/player/Layer 3_3.png,assets/player/Layer 3_4.png,assets/player/Layer 3_5.png,assets/player/Layer 3_6.png,assets/player/Layer 4_1.png,assets/player/Layer 4_2.png,assets/player/Layer 4_3.png,assets/player/Layer 4_4.png,assets/player/Layer 4_5.png,assets/player/Layer 4_6.png,0,6,12,18"

    namespace ECS
{
    struct Entity {
            EntityId id;
            std::vector<std::shared_ptr<ECS::IComponent>> components;

            /**
             * @brief Get a shared pointer to the Component object
             *
             * @param ComponentType
             * @return std::shared_ptr<ECS::IComponent>
             */
            std::shared_ptr<ECS::IComponent> getComponent(ComponentType type);
            void setComponent(ComponentType type, std::shared_ptr<ECS::IComponent> value);
    };

    using Action = std::tuple<std::vector<ECS::Entity>, ActionType, std::any>;

} // namespace ECS