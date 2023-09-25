/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "IComponent.hpp"
#include "RlTexture.hpp"

namespace ECS {
    template <typename T>
    class Texture : public IComponent {
        public:
            Texture();
            ~Texture();

            int setValue(T value);
            Raylib::RlTexture getValue() const;

        protected:
        private:
            Raylib::RlTexture _texture;
    };
} // namespace ECS

#endif /* !TEXTURE_HPP_ */
