#ifndef FILTERPARAMETERS_HPP
#define FILTERPARAMETERS_HPP

#include "FilterTypeEnum.hpp"

#include <unordered_map>
#include <string>

struct FilterParameters {
    FilterParameters() : id(0) {}
    // FilterParameters(std::size_t id) : id(id) {
    //     parameters.reserve(2);
    // }

    FilterParameters(std::size_t _id, FilterType _type, const std::string& _name)
     : id(_id), type(_type), name(_name) {
        parameters.reserve(2);
    }

    std::size_t id;
    FilterType type;
    std::string name;
    std::unordered_map<std::string, double> parameters;
};

#endif