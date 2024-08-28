#include "WindowFunction.hpp"

#include <cmath> // M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
Apply Hanning window to the input sample
*/
std::vector<std::complex<double>> WindowFunction::Hanning(const float* sample, size_t N) {
    std::vector<std::complex<double>> windowedSample;
    windowedSample.reserve(N);
    for (size_t i = 0; i < N; i++) {
        windowedSample.push_back(sample[i] * (0.5 * (1 - cos(2 * M_PI * i / (N - 1)))));
    }
    return windowedSample;
}