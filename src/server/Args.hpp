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

class Args
{
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
     * @brief Set the Port object
     * @param port
     * @return void
     */
    void setPort(int port);
    /**
     * @brief Set the Args object
     * @param ac
     * @param av
     * @return 1 if -help, 85 if error, 0 if ok
     */
    int setArgs(int ac, char** av);

private:
    int _port;
};
