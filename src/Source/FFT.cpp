#include "FFT.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void FFT::fft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output) {
    auto log2n = static_cast<int>(std::log2(input.size()));
    auto n = static_cast<size_t>(1 << log2n);

    if(output.size() < n)
        output.resize(n);
    
    for (size_t i = 0; i < n; ++i)
    {
        output[reverse(i, log2n)] = input[i];
    }
 
    // Cooley-Tukey FFT
    for (int s = 1; s <= log2n; ++s)
    {
        auto m = static_cast<size_t>(1 << s);
        auto m2 = m >> 1;
        std::complex<double> w(1, 0);
        std::complex<double> wm = std::exp(std::complex<double>(0, -2 * M_PI / m));
        for (size_t j = 0; j < m2; ++j)
        {
            for (size_t k = j; k < n; k += m)
            {
                std::complex<double> t = w * output[k + m2];
                std::complex<double> u = output[k];
                output[k] = u + t;
                output[k + m2] = u - t;
            }
            w *= wm;
        }
    }
}

void FFT::ifft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output) {
    auto log2n = static_cast<int>(std::log2(input.size()));
    auto n = static_cast<size_t>(1 << log2n);
    if(output.size() < n)
        output.resize(n);
    
    // Bit-reverse copy
    for (size_t i = 0; i < n; ++i)
    {
        output[reverse(i, log2n)] = input[i];
    }
 
    // Cooley-Tukey IFFT
    for (int s = 1; s <= log2n; ++s)
    {
        auto m = static_cast<size_t>(1 << s);
        auto m2 = m >> 1;
        std::complex<double> w(1, 0);
        std::complex<double> wm = std::exp(std::complex<double>(0, 2 * M_PI / m));
        for (size_t j = 0; j < m2; ++j)
        {
            for (size_t k = j; k < n; k += m)
            {
                std::complex<double> t = w * output[k + m2];
                std::complex<double> u = output[k];
                output[k] = u + t;
                output[k + m2] = u - t;
            }
            w *= wm;
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        output[i] /= n;
    }

}

size_t FFT::reverse(size_t b, int n) {
    size_t result = 0;
    for(int i = 0; i < n; i++) {
        result = (result << 1) | (b & 1);
        b >>= 1;
    }
    return result;
}