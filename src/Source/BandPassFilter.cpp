#include "BandPassFilter.hpp"

BandPassFilter::BandPassFilter(const FilterParameters& parameters)
    : Filter(parameters.id), _lowCutoff(parameters.parameters.at("lowCutoff")), _highCutoff(parameters.parameters.at("highCutoff"))
{
}

BandPassFilter::~BandPassFilter()
{
}

void BandPassFilter::process(std::vector<std::complex<double>>& data)
{
    size_t lowPassCutoff = static_cast<size_t>(data.size() * _lowCutoff);
    size_t highPassCutoff = static_cast<size_t>(data.size() * _highCutoff);
    for(size_t i = 0; i < lowPassCutoff; ++i)
    {
        data[i] = 0;
    }
    for(size_t i = highPassCutoff; i < data.size(); ++i)
    {
        data[i] = 0;
    }
}