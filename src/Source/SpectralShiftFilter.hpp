#ifndef SPECRALSHIFTFILTER_HPP
#define SPECRALSHIFTFILTER_HPP

#include "Filter.hpp"

class SpectralShiftFilter : public Filter
{
public:
    SpectralShiftFilter(const FilterParameters& parameters);
    ~SpectralShiftFilter() override;
    void process(std::vector<std::complex<double>>& data) override;
private:
    double _shift;
};

#endif