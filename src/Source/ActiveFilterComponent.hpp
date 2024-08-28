#ifndef ACTIVEFILTERCOMPONENT_HPP
#define ACTIVEFILTERCOMPONENT_HPP

#include <juce_gui_extra/juce_gui_extra.h>

#include "FilterParameters.hpp"
#include "FFTFilterProcessor.hpp"
#include "MainComponent.h"

class MainComponent;

class ActiveFilterComponent : public juce::Component
{
public:
    ActiveFilterComponent(const FilterParameters& parameters, FFTFilterProcessor* processor, MainComponent* parent);
    ~ActiveFilterComponent() override;

    // void paint(juce::Graphics& g) override;
    void removeFilter();
    void resized() override;

private:
    FilterParameters parameters;
    juce::Label nameLabel, valueLabel;
    juce::TextButton removeButton;

    FFTFilterProcessor* _processor;
    MainComponent* _parent;
};

#endif