/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

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

#endif /* !ISYSTEM_HPP_ */
