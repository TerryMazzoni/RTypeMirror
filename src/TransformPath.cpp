/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** transformPath
*/

#include <iostream>
#include <filesystem>

std::string transformPath(const std::string &path)
{
#ifdef _WIN32
    size_t pos = 0;
    std::filesystem::path absolutePath = std::filesystem::absolute(path);
    std::string windowsAbsolutePath = absolutePath.generic_string();
    std::string transformedPath = windowsAbsolutePath;
    while ((pos = transformedPath.find('/')) != std::string::npos) {
        transformedPath.replace(pos, 1, "\\");
    }
    return transformedPath;
#else
    return path;
#endif
}
