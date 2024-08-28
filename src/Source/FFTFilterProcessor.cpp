#include "FFTFilterProcessor.hpp"
#include "LowPassFilter.hpp"
#include "HighPassFilter.hpp"
#include "BandPassFilter.hpp"
#include "ReverbFilter.hpp"
#include "SpectralShiftFilter.hpp"
#include "HarmonicExciterFilter.hpp"

#include "FilterTypeEnum.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

FFTFilterProcessor::FFTFilterProcessor()
{
}

FFTFilterProcessor::~FFTFilterProcessor()
{
}

void FFTFilterProcessor::process(std::vector<std::complex<double>>& data)
{
    const juce::ScopedLock sl(lock);
    for(auto&& filter : _filters)
    {
        filter->process(data);
    }
}

void FFTFilterProcessor::addFilter(const FilterParameters& parameters)
{
    const juce::ScopedLock sl(lock);
    switch (parameters.type)
    {
    case FilterType::LowPass:
        _filters.push_back(std::make_unique<LowPassFilter>(parameters));
        break;
    case FilterType::HighPass:
        _filters.push_back(std::make_unique<HighPassFilter>(parameters));
        break;
    case FilterType::BandPass:
        _filters.push_back(std::make_unique<BandPassFilter>(parameters));
        break;
    case FilterType::Reverb:
        _filters.push_back(std::make_unique<ReverbFilter>(parameters));
        break;
    case FilterType::SpectralShift:
        _filters.push_back(std::make_unique<SpectralShiftFilter>(parameters));
        break;
    case FilterType::HarmonicExciter:
        _filters.push_back(std::make_unique<HarmonicExciterFilter>(parameters));
        break;
    case FilterType::Unknown:
        break;
    default:
        jassertfalse;
    }
}

void FFTFilterProcessor::removeFilter(std::size_t id)
{
    const juce::ScopedLock sl(lock);
    _filters.erase(std::remove_if(_filters.begin(), _filters.end(), [id](const std::unique_ptr<Filter>& filter)
    {
        return filter->id == id;
    }), _filters.end());
}