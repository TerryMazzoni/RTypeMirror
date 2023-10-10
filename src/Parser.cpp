/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Parser
*/

#include "Parser.hpp"

namespace Parser {
    ParserJson::ParserJson(std::string path)
    {
        _path = path;
        _entities = {};
    }

    ParserJson::ParserJson()
    {
        _path = "__default__";
        _entities = {};
    }

    ParserJson::~ParserJson()
    {
    }

    ParserJson &ParserJson::setPath(std::string path)
    {
        _path = path;
        return *this;
    }

    std::vector<entity_t> ParserJson::getEntities() const
    {
        return _entities;
    }

    static type_t getType(boost::property_tree::ptree &value)
    {
        try {
            value.get_value<int>();
            return type_t::INT;
        }
        catch (boost::property_tree::ptree_bad_data &e) {
            try {
                value.get_value<float>();
                return type_t::FLOAT;
            }
            catch (boost::property_tree::ptree_bad_data &e) {
                try {
                    value.get_value<std::string>();
                    return type_t::STRING;
                }
                catch (boost::property_tree::ptree_bad_data &e) {
                    return type_t::NONE;
                }
            }
        }
    }

    void ParserJson::parseEntity(boost::property_tree::ptree &root)
    {
        std::string typeEntities;
        std::vector<std::string> textures;
        entity_t newEntity;
        type_t type;

        for (auto &entity : root.get_child(PARSER_ALL_ENTITIES)) {
            typeEntities = entity.second.get<std::string>(PARSER_TYPE);
            textures = {};
            for (auto &texture : entity.second.get_child(PARSER_TEXTURES))
                textures.push_back(texture.second.get_value<std::string>());
            for (auto &instance : entity.second.get_child(PARSER_ENTITY_INSTANCE)) {
                newEntity = {
                    typeEntities,
                    textures,
                    {},
                };
                for (auto &value : instance.second) {
                    type = getType(value.second);
                    if (type == type_t::INT)
                        newEntity.instance[value.first] = value.second.get_value<int>();
                    else if (type == type_t::FLOAT)
                        newEntity.instance[value.first] = value.second.get_value<float>();
                    else if (type == type_t::STRING)
                        newEntity.instance[value.first] = value.second.get_value<std::string>();
                    newEntity.instanceType[value.first] = type;
                }
                _entities.push_back(newEntity);
            }
        }
    }

    void ParserJson::parseMap(boost::property_tree::ptree &root)
    {
        boost::property_tree::ptree tiles = root.get_child(PARSER_MAP).get_child(PARSER_MAP_TILES);
        boost::property_tree::ptree textures = root.get_child(PARSER_MAP).get_child(PARSER_TEXTURES);
        std::map<char, std::vector<std::string>> texturesMap;
        std::string line;
        entity_t newEntity;
        int tileSize = root.get_child(PARSER_MAP).get<int>(PARSER_MAP_TILESIZE);
        int y = 0;

        for (auto &texture : textures) {
            texturesMap[texture.first[0]] = {};
            for (auto &value : texture.second)
                texturesMap[texture.first[0]].push_back(value.second.get_value<std::string>());
        }
        for (auto &tile : tiles) {
            line = tile.second.get_value<std::string>();
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == ' ')
                    continue;
                if (texturesMap.find(line[i]) == texturesMap.end()) {
                    throw Parser::ParserException("Texture not found for char: '" + std::string(1, line[i]) + "' at x: " + std::to_string(i) + " y: " + std::to_string(y));
                }
                newEntity = {
                    "__tile__",
                    texturesMap[line[i]],
                    {}};
                newEntity.instance["x"] = i * tileSize;
                newEntity.instance["y"] = y * tileSize;
                newEntity.instanceType["x"] = type_t::INT;
                newEntity.instanceType["y"] = type_t::INT;
                _entities.push_back(newEntity);
            }
            y++;
        }
    }

    void ParserJson::displayEntities()
    {
        for (auto &entity : _entities) {
            std::cout << "┓\n┃ " << entity.type << std::endl;
            std::cout << "┃    Textures: " << std::endl;
            for (auto &texture : entity.textures)
                std::cout << "┃      " << texture << std::endl;
            std::cout << "┃    Instance: " << std::endl;
            for (auto &instance : entity.instance) {
                std::cout << "┃      " << instance.first << ": ";

                if (entity.instanceType[instance.first] == Parser::type_t::INT)
                    std::cout << "int = " << std::any_cast<int>(instance.second) << std::endl;
                else if (entity.instanceType[instance.first] == Parser::type_t::FLOAT)
                    std::cout << "float = " << std::any_cast<float>(instance.second) << std::endl;
                else if (entity.instanceType[instance.first] == Parser::type_t::STRING)
                    std::cout << "string = " << std::any_cast<std::string>(instance.second) << std::endl;
                else
                    std::cout << "unknown" << std::endl;
            }
            std::cout << "┛\n" << std::endl;
        }
    }

    ParserJson &ParserJson::parse(bool verbose)
    {
        if (_path == "__default__")
            throw Parser::ParserException("No path set");
        if (!std::filesystem::exists(_path))
            throw Parser::ParserException("File not found");

        boost::property_tree::ptree root;
        boost::property_tree::read_json(_path, root);

        try {
            parseEntity(root);
            parseMap(root);
        }
        catch (Parser::ParserException &e) {
            std::cout << e.what() << std::endl;
        }
        if (verbose)
            displayEntities();
        return *this;
    }

} // namespace Parser