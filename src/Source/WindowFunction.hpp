
#ifndef WINDOWFUNCTION_HPP
#define WINDOWFUNCTION_HPP

#include <vector>
#include <complex>

class WindowFunction {
public:
    static std::vector<std::complex<double>> Hanning(const float* sample, size_t N);
};

#endif // WINDOWFUNCTION_HPP