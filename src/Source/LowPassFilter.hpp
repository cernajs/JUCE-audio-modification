#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP

#include <vector>
#include <complex>
#include "Filter.hpp"

class LowPassFilter : public Filter
{
public:
    LowPassFilter(const FilterParameters& parameters);
    ~LowPassFilter() override;

    void process(std::vector<std::complex<double>>& data) override;

private:
    double _cutoff;
};

#endif