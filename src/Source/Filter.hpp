#include <unordered_map>
#include <vector>
#include <complex>

#include "FilterParameters.hpp"

#ifndef FILTER_HPP
#define FILTER_HPP

class Filter
{
public:
    Filter(std::size_t _id) : id(_id) {}
    virtual ~Filter() = default;
    virtual void process(std::vector<std::complex<double>>& data) = 0;

    //std::string name;
    std::size_t id;
};

#endif