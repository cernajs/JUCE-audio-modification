
#ifndef FFT_HPP
#define FFT_HPP

#include <vector>
#include <complex>

class FFT {
public:
    // static std::vector<std::complex<double>> fft(const std::vector<std::complex<double>>& input);

    // static std::vector<std::complex<double>> ifft(const std::vector<std::complex<double>>& input);

    static void fft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output);

    static void ifft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output);

private:
    static size_t reverse(size_t b, int n);

    static std::vector<std::complex<double>> reorder(const std::vector<std::complex<double>>& input);

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FFT);
};

#endif // FFT_HPP