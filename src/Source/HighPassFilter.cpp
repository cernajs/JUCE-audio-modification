#include "HighPassFilter.hpp"

HighPassFilter::HighPassFilter(const FilterParameters& parameters)
    : Filter(parameters.id), _cutoff(parameters.parameters.at("cutoff"))
{
}

HighPassFilter::~HighPassFilter()
{
}

void HighPassFilter::process(std::vector<std::complex<double>>& data)
{
    std::size_t highPassCutoff = static_cast<std::size_t>(data.size() * _cutoff);
    for(size_t i = 0; i < highPassCutoff; ++i)
    {
        data[i] = 0;
    }
}