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

#define PARSER_ALL_ENTITIES "all_entities"
#define PARSER_MAP "map"
#define PARSER_TYPE "type"
#define PARSER_TEXTURES "textures"
#define PARSER_ENTITY_INSTANCE "instance"
#define PARSER_MAP_TILES "tiles"
#define PARSER_MAP_TILESIZE "tile_size"
#define PARSER_INDEX_TEXTURES "index_textures"

namespace Parser {
    enum class type_t {
        NONE,
        INT,
        FLOAT,
        STRING,
    };

    class Any {
        public:
            /*
            ** @brief constructs a Any object, the type of the object is set depending on the argument
            **
            ** @param value: the value of the Any object
            */
            Any(int i);
            Any(float f);
            Any(std::string s);
            Any(double d);
            Any();

            /*
            ** @brief get the type of the value stored
            **
            ** @returns the type of the value stored
            */
            Parser::type_t getType() const;

            /*
            ** @brief get the value
            **
            ** @returns the value stored as an int, if the value cannot be converted to an int, std::numeric_limits<int>::infinity() ir returned
            */
            int getInt() const;

            /*
            ** @brief get the value
            **
            ** @returns the value stored as an float, if the value cannot be converted to a float, std::numeric_limits<float>::infinity() ir returned
            */
            float getFloat() const;

            /*
            ** @brief get the value
            **
            ** @returns the value stored as an string
            */
            std::string getString() const;

        protected:
        private:
            int _i;
            float _f;
            std::string _s;
            Parser::type_t _type;
    };

    typedef struct {
            int id;
            std::string type;
            std::pair<std::vector<std::string>, std::vector<int>> textures;
            std::unordered_map<std::string, Parser::Any> instance;
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
            ** @param verbose Display all entities in the json file for debug, default false
            ** @return itself
            ** @throw ParserException if the file is not found / set
            */
            ParserJson &parse(bool verbose = false);

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

            /*
            ** @brief Display all entities in the json file for debug
            */
            void displayEntities();

            std::string _path;
            std::vector<entity_t> _entities;
            int _lastId;
    };
} // namespace Parser
