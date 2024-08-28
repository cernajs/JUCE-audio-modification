#ifndef ACTIVEFILTERCONTROLLER_HPP
#define ACTIVEFILTERCONTROLLER_HPP

#include <string>
#include <unordered_map>

#include "FFTFilterProcessor.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

class ActiveFilterController {
public:
    ActiveFilterController(FFTFilterProcessor* processor);
    void showFilterParameterDialog(const std::string& filterType, std::size_t id, std::function<void(FilterParameters)> callback);
    void deleteSliders();
private:
    FilterType parseSliders(const std::string& filterType);

    std::unique_ptr<juce::AlertWindow> parameterDialog;
    std::unordered_map<std::string, juce::Slider*> parameterSliders;

    FFTFilterProcessor* processor;
};

#endif