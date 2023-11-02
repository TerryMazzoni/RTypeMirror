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
#define PATH_TEXTURES_ENEMY1 "assets/enemies/Enemy1/0.png,assets/enemies/Enemy1/1.png,assets/enemies/Enemy1/2.png,assets/enemies/Enemy1/3.png,assets/enemies/Enemy1/4.png,assets/enemies/Enemy1/5.png"
#define PATH_TEXTURES_ENEMY2 "assets/enemies/Enemy2/0.png,assets/enemies/Enemy2/1.png,assets/enemies/Enemy2/2.png,assets/enemies/Enemy2/3.png,assets/enemies/Enemy2/4.png,assets/enemies/Enemy2/5.png"
#define PATH_TEXTURES_BOSS1 "assets/enemies/Boss1/00.png,assets/enemies/Boss1/01.png,assets/enemies/Boss1/02.png,assets/enemies/Boss1/03.png,assets/enemies/Boss1/04.png,assets/enemies/Boss1/05.png,assets/enemies/Boss1/06.png,assets/enemies/Boss1/07.png,assets/enemies/Boss1/08.png,assets/enemies/Boss1/09.png"

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