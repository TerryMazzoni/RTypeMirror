/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Parser
*/

#pragma once

#include <typeinfo>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <any>
#include <filesystem>

#define PARSER_ALL_ENTITIES "allEntities"
#define PARSER_MAP "map"
#define PARSER_TYPE "type"
#define PARSER_ENTITY_TEXTURE "texture"
#define PARSER_ENTITY_INSTANCE "instance"
#define PARSER_MAP_TEXTURES "textures"
#define PARSER_MAP_TILES "tiles"
#define PARSER_MAP_TILESIZE "tileSize"

namespace Parser {
    enum class type_t {
        NONE,
        INT,
        FLOAT,
        STRING,
    };

    typedef struct {
            std::string type;
            std::string texture;
            std::map<std::string, std::any> instance;
            std::map<std::string, type_t> instanceType;
    } entity_t;

    class ParserException : public std::exception {

        public:
            ParserException(std::string message)
            {
                _message = "ERROR: " + message;
            };
            std::string what()
            {
                return _message;
            };

        private:
            std::string _message;
    };

    class ParserJson {
        public:
            /*
            ** @brief Construct a new ParserJson object
            **
            ** @param path Path to the json file
            */
            ParserJson(std::string path);

            /*
            ** @brief Construct a new ParserJson object
            */
            ParserJson();

            /*
            ** @brief Destroy the ParserJson object
            */
            ~ParserJson();

            /*
            ** @brief Set the Path object
            **
            ** @param path Path to the json file
            ** @return itself
            */
            ParserJson &setPath(std::string path);

            /*
            ** @brief Parse the json file
            **
            ** @return itself
            ** @throw ParserException if the file is not found / set
            */
            ParserJson &parse();

            /*
            ** @brief Get the Entities object
            **
            ** @return std::vector<entity_t> list of struct Parser::entity_t
            **
            */
            std::vector<entity_t> getEntities() const;

        protected:
        private:
            /*
            ** @brief Parse all entities in the json file
            */
            void parseEntity(boost::property_tree::ptree &entity);
            /*
            ** @brief Parse the map in the json file
            */
            void parseMap(boost::property_tree::ptree &map);

            std::string _path;
            std::vector<entity_t> _entities;
    };

} // namespace Parser
