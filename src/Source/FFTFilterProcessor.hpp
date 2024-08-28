#include <vector>
#include <complex>

#include "Filter.hpp"
#include "FilterParameters.hpp"

#ifndef FFTFILTERPROCESSOR_HPP
#define FFTFILTERPROCESSOR_HPP

#include <juce_core/juce_core.h>

class FFTFilterProcessor
{
public:
    FFTFilterProcessor();
    ~FFTFilterProcessor();

    void process(std::vector<std::complex<double>>& data);
    void addFilter(const FilterParameters& parameters);
    void removeFilter(std::size_t id);
private:
    std::vector<std::unique_ptr<Filter>> _filters;
    juce::CriticalSection lock;
};

#endif