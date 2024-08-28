#ifndef REVERBFILTER_HPP
#define REVERBFILTER_HPP

#include "Filter.hpp"

class ReverbFilter : public Filter
{
public:
    ReverbFilter(const FilterParameters& parameters);
    ~ReverbFilter() override;
    void process(std::vector<std::complex<double>>& data) override;

private:
    double _delay;
    double _decay;
};

#endif