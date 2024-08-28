#include "SpectralShiftFilter.hpp"

SpectralShiftFilter::SpectralShiftFilter(const FilterParameters& parameters) : Filter(parameters.id)
{
    _shift = parameters.parameters.at("shift");
}

SpectralShiftFilter::~SpectralShiftFilter()
{
}

void SpectralShiftFilter::process(std::vector<std::complex<double>>& data)
{
    //int shiftAmount = data.size() * _shift;

    std::size_t shiftAmount = static_cast<std::size_t>(data.size() * _shift);
    auto it = data.begin();
    std::advance(it, shiftAmount);
    std::rotate(data.begin(), it, data.end());
}