#include "ReverbFilter.hpp"

ReverbFilter::ReverbFilter(const FilterParameters& parameters)
    : Filter(parameters.id), _delay(parameters.parameters.at("delay")), _decay(parameters.parameters.at("decay"))
{
}

ReverbFilter::~ReverbFilter()
{
}

void ReverbFilter::process(std::vector<std::complex<double>>& data)
{
    //int delay = data.size() * _delay;
    std::size_t delay = static_cast<std::size_t>(data.size() * _delay);
    for(size_t i = delay; i < data.size(); ++i)
    {
        data[i] = data[i] * _decay;
    }
}