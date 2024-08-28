#include "LowPassFilter.hpp"

LowPassFilter::LowPassFilter(const FilterParameters& parameters)
    : Filter(parameters.id), _cutoff(parameters.parameters.at("cutoff"))
{
}

LowPassFilter::~LowPassFilter()
{
}

void LowPassFilter::process(std::vector<std::complex<double>>& data)
{
    size_t lowPassCutoff = static_cast<size_t>(data.size() * _cutoff);
    for(size_t i = lowPassCutoff; i < data.size(); ++i)
    {
        data[i] = 0;
    }
}