#ifndef HIGHPASSFILTER_HPP
#define HIGHPASSFILTER_HPP

#include <vector>
#include <complex>
#include "Filter.hpp"

class HighPassFilter : public Filter
{
public:
    HighPassFilter(const FilterParameters& parameters);
    ~HighPassFilter() override;

    void process(std::vector<std::complex<double>>& data) override;

private:
    double _cutoff;
};

#endif