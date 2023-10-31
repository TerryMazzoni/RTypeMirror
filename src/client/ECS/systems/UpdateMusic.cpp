/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** UpdateTexture
*/

#include "UpdateMusic.hpp"
#include "Musics.hpp"

namespace ECS {
    UpdateMusic::UpdateMusic()
    {
    }

    std::vector<Action> UpdateMusic::execute()
    {
        if (_isActivated && _entity.has_value()) {
            std::shared_ptr<ECS::Musics> music = std::dynamic_pointer_cast<ECS::Musics>(_entity.value().getComponent(ComponentType::Music));
            music->update();
        }
        return {};
    }

} // namespace ECS
