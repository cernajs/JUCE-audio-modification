#ifndef HARMOICEXCITERFILTER_HPP
#define HARMOICEXCITERFILTER_HPP

#include "Filter.hpp"
#include <vector>
#include <complex>

class HarmonicExciterFilter : public Filter
{
public:
    HarmonicExciterFilter(const FilterParameters& parameters);
    ~HarmonicExciterFilter() override;
    void process(std::vector<std::complex<double>>& data) override;
};

#endif