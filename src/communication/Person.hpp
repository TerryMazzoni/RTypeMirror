/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Person
*/

#pragma once

#include <iostream>

class Person
{
public:
    Person(std::string name, int age) : _name(name), _age(age)
    {
    }
    Person()
    {
    }
    std::string getName() const
    {
        return _name;
    }
    int getAge() const
    {
        return _age;
    }
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void) version;
        ar& _name;
        ar& _age;
    }

private:
    std::string _name;
    int _age;
};