#include "HarmonicExciterFilter.hpp"

HarmonicExciterFilter::HarmonicExciterFilter(const FilterParameters& parameters) : Filter(parameters.id)
{
}

HarmonicExciterFilter::~HarmonicExciterFilter()
{
}

void HarmonicExciterFilter::process(std::vector<std::complex<double>>& data)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        data[i] *= 1.0 + i / static_cast<double>(data.size());
    }
}