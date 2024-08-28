#ifndef BANDPASSFILTER_HPP
#define BANDPASSFILTER_HPP

#include "Filter.hpp"

class BandPassFilter : public Filter
{
public:
    BandPassFilter(const FilterParameters& parameters);
    ~BandPassFilter() override;
    void process(std::vector<std::complex<double>>& data) override;

private:
    double _lowCutoff;
    double _highCutoff;
};

#endif