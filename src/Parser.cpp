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
        _lastId = 1;
        _background_1 = {};
        _background_2 = {};
        _background_3 = {};
        _nbr_players = 1;
    }

    ParserJson::ParserJson()
    {
        _path = "__default__";
        _entities = {};
        _lastId = 1;
        _background_1 = {};
        _background_2 = {};
        _background_3 = {};
        _nbr_players = 1;
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
        catch (...) {
            try {
                value.get_value<float>();
                return type_t::FLOAT;
            }
            catch (...) {
                try {
                    value.get_value<std::string>();
                    return type_t::STRING;
                }
                catch (...) {
                    return type_t::NONE;
                }
            }
        }
    }

    void ParserJson::parseEntity(boost::property_tree::ptree &root)
    {
        std::string typeEntities;
        std::vector<std::string> textures;
        std::vector<int> indexes;
        entity_t newEntity;
        type_t type;

        if (root.count(PARSER_ALL_ENTITIES) == 0) {
            throw ParserException("key " + static_cast<std::string>(PARSER_ALL_ENTITIES) + " not found");
        }
        for (auto &entity : root.get_child(PARSER_ALL_ENTITIES)) {
            typeEntities = entity.second.get<std::string>(PARSER_TYPE);
            textures = {};
            if (entity.second.count(PARSER_TEXTURES) != 0)
                for (auto &texture : entity.second.get_child(PARSER_TEXTURES))
                    textures.push_back(texture.second.get_value<std::string>());
            if (entity.second.count(PARSER_INDEX_TEXTURES) != 0)
                for (auto &index : entity.second.get_child(PARSER_INDEX_TEXTURES))
                    indexes.push_back(index.second.get_value<int>());
            if (entity.second.count(PARSER_ENTITY_INSTANCE) != 0) {
                for (auto &instance : entity.second.get_child(PARSER_ENTITY_INSTANCE)) {
                    newEntity = {
                        _lastId++,
                        typeEntities,
                        {textures, indexes},
                    };
                    if (typeEntities == "__background_1__" || typeEntities == "__background_2__" || typeEntities == "__background_3__") {
                        for (int i = 0; i < ((int)textures.size() * 2) - 1; i++) {
                            _entities.push_back(
                                {_lastId++,
                                 "__void__",
                                 {{},
                                  {}},
                                 {}});
                        };
                    }
                    for (auto &value : instance.second) {
                        type = getType(value.second);
                        if (type == type_t::INT)
                            newEntity.instance.insert({value.first, Any(value.second.get_value<int>())});
                        else if (type == type_t::FLOAT)
                            newEntity.instance.insert({value.first, Any(value.second.get_value<float>())});
                        else if (type == type_t::STRING)
                            newEntity.instance.insert({value.first, Any(value.second.get_value<std::string>())});
                    }
                    _entities.push_back(newEntity);
                }
            }
        }
    }

    void ParserJson::parseMap(boost::property_tree::ptree &root)
    {
        boost::property_tree::ptree tiles;
        boost::property_tree::ptree textures;
        boost::property_tree::ptree indexes;
        std::map<char, std::vector<std::string>> texturesMap;
        std::map<char, std::vector<int>> indexesMap;
        std::string line;
        entity_t newEntity;
        int y = 0;

        if (root.count(PARSER_MAP) == 0) {
            throw ParserException("key " + static_cast<std::string>(PARSER_MAP) + " not found");
        }

        if (root.get_child(PARSER_MAP).count(PARSER_MAP_TILESIZE) == 0)
            _tileSize = 64;
        else
            _tileSize = root.get_child(PARSER_MAP).get<int>(PARSER_MAP_TILESIZE);

        if (root.get_child(PARSER_MAP).count(PARSER_TEXTURES) != 0) {
            textures = root.get_child(PARSER_MAP).get_child(PARSER_TEXTURES);
            for (auto &texture : textures) {
                texturesMap[texture.first[0]] = {};
                for (auto &value : texture.second)
                    texturesMap[texture.first[0]].push_back(value.second.get_value<std::string>());
            }
        }

        if (root.get_child(PARSER_MAP).count(PARSER_INDEX_TEXTURES) != 0) {
            indexes = root.get_child(PARSER_MAP).get_child(PARSER_INDEX_TEXTURES);
            for (auto &index : indexes) {
                indexesMap[index.first[0]] = {};
                for (auto &value : index.second)
                    indexesMap[index.first[0]].push_back(value.second.get_value<int>());
            }
        }
        if (root.get_child(PARSER_MAP).count(PARSER_MAP_TILES) != 0) {
            tiles = root.get_child(PARSER_MAP).get_child(PARSER_MAP_TILES);
            for (auto &tile : tiles) {
                line = tile.second.get_value<std::string>();
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                        continue;
                    if (texturesMap.find(line[i]) == texturesMap.end()) {
                        throw Parser::ParserException("Texture not found for char: '" + std::string(1, line[i]) + "' at x: " + std::to_string(i) + " y: " + std::to_string(y));
                    }
                    newEntity = {
                        _lastId++,
                        "__tile__",
                        {texturesMap[line[i]], indexesMap[line[i]]},
                    };
                    newEntity.instance.insert({"x", Any((i * _tileSize) * 1.0f)});
                    newEntity.instance.insert({"y", Any((y * _tileSize) * 1.0f)});
                    _entities.push_back(newEntity);
                }
                y++;
            }
        }
    }

    void ParserJson::displayEntities()
    {
        std::cout << "Nbr of entities: " << _entities.size() << std::endl;
        std::cout << "Tile Size: " << _tileSize << std::endl;
        for (auto &entity : _entities) {
            std::cout << "┓\n┃ " << entity.type << std::endl;
            std::cout << "┃    ID: " << entity.id << std::endl;
            std::cout << "┃    Textures: " << std::endl;
            std::cout << "┃      Indexes:" << std::endl;
            for (auto &index : entity.textures.second)
                std::cout << "┃        " << index << std::endl;
            std::cout << "┃      Textures:" << std::endl;
            for (auto &texture : entity.textures.first)
                std::cout << "┃        " << texture << std::endl;
            std::cout << "┃    Instance: " << std::endl;
            for (auto &instance : entity.instance) {
                std::cout << "┃      " << instance.first << ": ";
                if (instance.second.getType() == Parser::type_t::INT)
                    std::cout << "int = " << instance.second.getInt() << std::endl;
                else if (instance.second.getType() == Parser::type_t::FLOAT)
                    std::cout << "float = " << instance.second.getFloat() << std::endl;
                else if (instance.second.getType() == Parser::type_t::STRING)
                    std::cout << "string = " << instance.second.getString() << std::endl;
                else
                    std::cout << "unknown" << std::endl;
            }
            std::cout << "┛\n"
                      << std::endl;
        }
    }

    ParserJson &ParserJson::parse(bool verbose)
    {
        if (_path == "__default__") {
            throw Parser::ParserException("No path set");
        }
        if (!std::filesystem::exists(_path)) {
            throw Parser::ParserException("File not found");
        }

        boost::property_tree::ptree root;
        boost::property_tree::read_json(_path, root);

        parseEntity(root);
        parseMap(root);
        if (verbose)
            displayEntities();
        return *this;
    }

    int ParserJson::getTileSize() const
    {
        return _tileSize;
    }

    int ParserJson::addId()
    {
        _lastId++;
        return _lastId - 1;
    }

    int ParserJson::getLastId() const
    {
        return _lastId;
    }

    Any::Any(int i)
        : _i(i), _f(0.0), _s(""), _type(type_t::INT)
    {
    }

    Any::Any(float f)
        : _i(0), _f(f), _s(""), _type(type_t::FLOAT)
    {
    }

    Any::Any(std::string s)
        : _i(0), _f(0.0), _s(s), _type(type_t::STRING)
    {
    }

    Any::Any(double d)
        : _i(0), _f(d), _s(""), _type(type_t::FLOAT)
    {
    }

    Any::Any()
        : _i(0), _f(0), _s(""), _type(type_t::NONE)
    {
    }

    Parser::type_t Any::getType() const
    {
        return _type;
    }

    int Any::getInt() const
    {
        int i = 0;

        if (_type == Parser::type_t::INT)
            i = _i;
        if (_type == Parser::type_t::FLOAT)
            i = static_cast<int>(_f);
        if (_type == Parser::type_t::STRING) {
            try {
                i = std::stoi(_s);
            }
            catch (...) {
                std::cout << "Could not convert string '" << _s << "' to int" << std::endl;
                i = std::numeric_limits<int>::infinity();
            }
        }
        return i;
    }

    float Any::getFloat() const
    {
        float f = 0.0;

        if (_type == Parser::type_t::INT)
            f = static_cast<float>(_i);
        if (_type == Parser::type_t::FLOAT)
            f = _f;
        if (_type == Parser::type_t::STRING) {
            try {
                f = std::stof(_s);
            }
            catch (...) {
                std::cout << "Could not convert string '" << _s << "' to float" << std::endl;
                f = std::numeric_limits<float>::infinity();
            }
        }
        return f;
    }

    std::string Any::getString() const
    {
        std::string s = "";

        if (_type == Parser::type_t::INT)
            s = std::to_string(_i);
        if (_type == Parser::type_t::FLOAT)
            s = std::to_string(_f);
        if (_type == Parser::type_t::STRING)
            s = _s;
        return s;
    }

    int setValue(std::unordered_map<std::string, Parser::Any> &umap, std::string key, int value)
    {
        Any newValue = Any(value);

        if (keyExists(umap, key)) {
            umap.emplace(key, newValue).first->second = newValue;
            return 1;
        }
        else {
            umap.insert({key, newValue});
            return 0;
        }
    }

    int setValue(std::unordered_map<std::string, Parser::Any> &umap, std::string key, float value)
    {
        Any newValue = Any(value);

        if (keyExists(umap, key)) {
            umap.emplace(key, newValue).first->second = newValue;
            return 1;
        }
        else {
            umap.insert({key, newValue});
            return 0;
        }
    }

    int setValue(std::unordered_map<std::string, Parser::Any> &umap, std::string key, std::string value)
    {
        Any newValue = Any(value);

        if (keyExists(umap, key)) {
            umap.emplace(key, newValue).first->second = newValue;
            return 1;
        }
        else {
            umap.insert({key, newValue});
            return 0;
        }
    }

    int setValue(std::unordered_map<std::string, Parser::Any> &umap, std::string key, double value)
    {
        Any newValue = Any(value);

        if (keyExists(umap, key)) {
            umap.emplace(key, newValue).first->second = newValue;
            return 1;
        }
        else {
            umap.insert({key, newValue});
            return 0;
        }
    }

    int setValue(std::unordered_map<std::string, Parser::Any> &umap, std::string key, Any value)
    {

        if (keyExists(umap, key)) {
            umap.emplace(key, value).first->second = value;
            return 1;
        }
        else {
            umap.insert({key, value});
            return 0;
        }
    }

    bool keyExists(std::unordered_map<std::string, Parser::Any> &umap, std::string key)
    {
        if (umap.find(key) == umap.end())
            return false;
        return true;
    }

} // namespace Parser