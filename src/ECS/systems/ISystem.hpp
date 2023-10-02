/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ISystem
*/

#pragma once
namespace ECS {
    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual int execute() = 0;
            virtual int setActivation(bool state) = 0;

        protected:
            int _id;
            bool _isActivated;

        private:
    };
} // namespace ECS
