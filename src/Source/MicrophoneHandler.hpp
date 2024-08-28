#include <juce_audio_devices/juce_audio_devices.h>
//#include "MainComponent.h"

#ifndef MICROPHONEHANDLER_HPP
#define MICROPHONEHANDLER_HPP

#include "FFTFilterProcessor.hpp"
#include "FileWriter.hpp"

class MainComponent;

class MicrophoneHandler : public juce::AudioIODeviceCallback
{
public:
    MicrophoneHandler(
        juce::AudioDeviceManager& adm, juce::AudioTransportSource& transportSource,
         MainComponent* mainComponent, FFTFilterProcessor* fftFilterProcessor,
         FileWriter* fileWriter);
    ~MicrophoneHandler() override;

    void audioDeviceIOCallbackWithContext (const float* const* inputChannelData,
                                                   int numInputChannels,
                                                   float* const* outputChannelData,
                                                   int numOutputChannels,
                                                   int numSamples,
                                                   const juce::AudioIODeviceCallbackContext& context) override;
    void audioDeviceAboutToStart(juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;

    void startRecording();
    void stopRecording();

    void setMicOutputEnabled(bool enabled);
    void setFFTEnabled(bool enabled);
    void setSaveToFile(bool enabled);

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    double getSampleRate();
private:
    juce::AudioDeviceManager& deviceManager;
    juce::AudioTransportSource& transportSource;
    MainComponent* mainComponent;
    FFTFilterProcessor* fftFilterProcessor;
    FileWriter* fileWriter;

    std::vector<std::complex<double>> buffer;
    std::vector<std::complex<double>> outputBuffer;

    bool micOutputEnabled = false;
    bool fftEnabled = false;
    bool saveToFile = false;

    double currentSampleRate = 0;

    juce::AudioBuffer<float> audioBuffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MicrophoneHandler)
};

#endif