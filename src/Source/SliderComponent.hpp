#ifndef SLIDERCOMPONENT_HPP
#define SLIDERCOMPONENT_HPP

#include <juce_gui_extra/juce_gui_extra.h>

class SliderComponent : public juce::Component
{
public:
    SliderComponent(const juce::String& name, double initialValue, double minValue, double maxValue);

    void resized() override;
    
    juce::Slider slider;

private:
    juce::Label label;
};

#endif