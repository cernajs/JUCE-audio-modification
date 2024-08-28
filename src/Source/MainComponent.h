#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>

#include <juce_audio_utils/juce_audio_utils.h>

#include <juce_audio_formats/juce_audio_formats.h>

#include <juce_audio_devices/juce_audio_devices.h>

//#include <juce_AudioIODevice.h>

//#include <juce_core/juce_core.h>

#include "TransportStateC.hpp"
#include "MicrophoneHandler.hpp"
#include "FileLoader.hpp"
#include "GraphicsComponent.hpp"
#include "FFTFilterProcessor.hpp"
#include "ActiveFilterController.hpp"
#include "ActiveFilterComponent.hpp"
#include "FileWriter.hpp"

#include <complex>
#include <vector>


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
// typedef enum TransportStateC
// {
//     Stopped,
//     Starting,
//     Playing,
//     Stopping,
//     MicrophonePlaying
// } TransportStateC;


class ActiveFilterComponent;

class ActiveFilterController;

class MainComponent final : public juce::AudioAppComponent,
                            public juce::ChangeListener,
                            public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    //void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* uploadButton);

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;

    void transportSourceChanged();
    void changeState (TransportStateC newState);
    void thumbnailChanged();

    void timerCallback() override;

    void setAudioData(const float* data, int size);

    void showFilterParameterDialog(const std::string& filterType);

    void removeActiveFilterComponent(ActiveFilterComponent* component);

    juce::AudioDeviceManager customDeviceManager;
    juce::AudioFormatManager formatManager;

    TransportStateC state;
    juce::AudioThumbnailCache thumbnailCache;
    juce::AudioThumbnail thumbnail;
    juce::AudioDeviceSelectorComponent deviceSelector;

    juce::AudioTransportSource transportSource;
    // TransportStateC state;


private:
    //==============================================================================
    // Your private member variables go here...

    double microphoneSamplerate();

    MicrophoneHandler micHandler;
    FileLoader fileLoader;
    GraphicsComponent graphicsComponent;
    FFTFilterProcessor fftFilterProcessor;
    ActiveFilterController activeFilterController;
    FileWriter fileWriter;

    juce::TextButton uploadButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton micButton;
    juce::ToggleButton fftButton;
    juce::TextButton filterMenuButton;
    juce::ToggleButton fileOutputButton;


    juce::AudioBuffer<float> audioBuffer = juce::AudioBuffer<float>(2, 512);

    std::size_t _id = 1;

    bool micOutputEnabled = false;

    double currentSampleRate = 0.0;

    std::vector<std::complex<double>> outputBuffer {};
    std::vector<std::complex<double>> buffer {};

    juce::OwnedArray<ActiveFilterComponent> activeFilters;

    juce::CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
