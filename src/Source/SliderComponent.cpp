#include "SliderComponent.hpp"

#include "MainComponent.h"
#include "FFT.hpp"
#include "WindowFunction.hpp"
#include "FilterParameters.hpp"
#include "FilterTypeEnum.hpp"

SliderComponent::SliderComponent(const juce::String& name, double initialValue, double minValue, double maxValue)
{
    label.setText(name, juce::dontSendNotification);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 50);
    slider.setRange(minValue, maxValue);
    slider.setValue(initialValue);
    addAndMakeVisible(label);
    addAndMakeVisible(slider);

    label.attachToComponent(&slider, true);

    setSize(300, 50);
}

void SliderComponent::resized()
{
    slider.setBounds(getLocalBounds());
}