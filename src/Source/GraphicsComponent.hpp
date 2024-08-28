#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

class GraphicsComponent : public juce::Component
{
public:
    GraphicsComponent(juce::AudioBuffer<float> *audioBuffer);
    ~GraphicsComponent() override;

    void render();

private:
    juce::AudioBuffer<float> *_audioBuffer;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void paintIfNoFileLoaded (juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
    void paintIfFileLoaded (juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphicsComponent)
};

#endif