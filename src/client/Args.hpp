/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Args
*/

#pragma once

#include <cstdlib>
#include <iostream>
#include <regex>

class Args {
    public:
        /**
         * @brief Construct a new Args object
         */
        Args();
        /**
         * @brief Destroy the Args object
         */
        ~Args();
        /**
         * @brief Get the Port object
         * @return int
         */
        int getPort() const;
        /**
         * @brief Get the Ip object
         * @return std::string
         */
        std::string getIp() const;
        /**
         * @brief Set the Port object
         * @param port
         * @return void
         */
        void setPort(int port);
        /**
         * @brief Set the Ip object
         * @param ip
         * @return void
         */
        void setIp(const std::string &ip);
        /**
         * @brief Set the Args object
         * @param ac
         * @param av
         * @return 1 if -help, 85 if error, 0 if ok
         */
        int setArgs(int ac, char **av);
        /**
         * @brief Set the Mute object to true
         */
        void setMute();
        /**
         * @brief Get the Mute object
         * @return true
         * @return false
         */
        bool getMute() const;

    private:
        int _port;
        std::string _ip;
        bool _mute;
};
