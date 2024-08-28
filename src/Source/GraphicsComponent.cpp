#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(juce::AudioBuffer<float> *audioBuffer) : _audioBuffer(audioBuffer)
{
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> bounds (10, 100, getWidth() - 20, getHeight() - 120);
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);

    if (_audioBuffer->getNumSamples() > 0) {
        paintIfFileLoaded(g, bounds);
    }
    else {
        paintIfNoFileLoaded(g, bounds);
    }
}

void GraphicsComponent::resized()
{
}

void GraphicsComponent::render()
{
    repaint();
}

void GraphicsComponent::paintIfNoFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds)
{
    g.setColour (juce::Colours::darkgrey);
    g.fillRect (thumbnailBounds);
    g.setColour (juce::Colours::white);
    g.drawFittedText ("No file loaded", thumbnailBounds, juce::Justification::centred, 1);
}

void GraphicsComponent::paintIfFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& bounds)
{
    if (_audioBuffer->getNumSamples() > 0) {
        const int numChannels = _audioBuffer->getNumChannels();
        const int numSamples = _audioBuffer->getNumSamples();

        const float verticalZoom = 1.0f;

        auto h = bounds.getHeight() / numChannels;
        auto x_base = bounds.getX() + bounds.getWidth() / numSamples;

        auto channelHeight = h * 0.9;
        float verticalScale = 1.0f;

        for (int channel = 0; channel < numChannels; ++channel) {
            juce::Path channelPath;
            channelPath.startNewSubPath (bounds.getX(), static_cast<float>(bounds.getY() + h * channel + channelHeight / 2));
            
            auto channelData = _audioBuffer->getReadPointer(channel);
            for (int i = 1; i < numSamples; ++i) {
                auto x1 = x_base * (i - 1);
                auto x2 = x_base * i;

                // Apply verticalZoom and verticalScale
                auto y1 = bounds.getY() + h * channel + channelHeight * (1.0 + verticalZoom * verticalScale * channelData[i - 1]) / 2.0;
                auto y2 = bounds.getY() + h * channel + channelHeight * (1.0 + verticalZoom * verticalScale * channelData[i]) / 2.0;

                // Limit y1 and y2 to be within the bounds rectangle
                y1 = juce::jlimit(static_cast<double>(bounds.getY()), static_cast<double>(bounds.getBottom()), y1);
                y2 = juce::jlimit(static_cast<double>(bounds.getY()), static_cast<double>(bounds.getBottom()), y2);

                channelPath.lineTo (static_cast<float>(x1), static_cast<float>(y1));
                channelPath.lineTo (static_cast<float>(x2), static_cast<float>(y2));
            }

            g.setColour (juce::Colours::white);
            g.strokePath (channelPath, juce::PathStrokeType (2.0f));
        }
    }
}