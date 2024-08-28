#include "MicrophoneHandler.hpp"
#include "MainComponent.h"
#include "FFT.hpp"

MicrophoneHandler::MicrophoneHandler(
        juce::AudioDeviceManager& adm, juce::AudioTransportSource& _transportSource,
         MainComponent* _mainComponent, FFTFilterProcessor* _fftFilterProcessor,
         FileWriter* _fileWriter) : 
        deviceManager(adm), transportSource(_transportSource),
        mainComponent(_mainComponent), fftFilterProcessor(_fftFilterProcessor),
        fileWriter(_fileWriter)
{}

MicrophoneHandler::~MicrophoneHandler()
{
    deviceManager.removeAudioCallback(this);
}


/*
callback called when this class is registered as an audio callback
(called by JUCE)
*/
void MicrophoneHandler::audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
    int numInputChannels,
    float* const* outputChannelData,
    int numOutputChannels,
    int numSamples,
    const juce::AudioIODeviceCallbackContext& /*context*/)
{
    int smallerChannels = numInputChannels < numOutputChannels ? numInputChannels : numOutputChannels;

    if (micOutputEnabled)
    {

        if (numInputChannels > 0) {
            const float* input = inputChannelData[0];

            //resize if sample rate changes
            if (buffer.size() < numSamples) {
                buffer.resize(numSamples);
                outputBuffer.resize(numSamples);
                audioBuffer.setSize(1, numSamples);
            }

            //perform fft and filters
            if (fftEnabled) {

                for (int i = 0; i < numSamples; ++i) {
                    buffer[i] = std::complex<double>(input[i], 0.0);
                }

                FFT::fft(buffer, outputBuffer);

                fftFilterProcessor->process(outputBuffer);

                FFT::ifft(outputBuffer, buffer);
            }


            if (micOutputEnabled && numOutputChannels > 0) {
                float* output = outputChannelData[0];
                for (int i = 0; i < numSamples; ++i) {

                    //write audio back to output
                    output[i] = fftEnabled ? static_cast<float>(buffer[i].real()) : input[i];

                    if (saveToFile) {
                        audioBuffer.setSample(0, i, output[i]);
                    }
                }
                if (saveToFile) {
                    fileWriter->writeToFile(audioBuffer);
                }
            }
        }

        //set audio data in main component for visualization
        if (mainComponent && numInputChannels > 0)
        {
            const float* channelData = outputChannelData[0];

            mainComponent->setAudioData(channelData, numSamples);
        }
    }
}


void MicrophoneHandler::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    currentSampleRate = device->getCurrentSampleRate();
    transportSource.prepareToPlay(device->getCurrentBufferSizeSamples(), device->getCurrentSampleRate());
}


void MicrophoneHandler::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

}


void MicrophoneHandler::audioDeviceStopped()
{
    //transportSource.releaseResources();
    //transportSource.setSource(nullptr);
}

double MicrophoneHandler::getSampleRate()
{
    return currentSampleRate;
}

void MicrophoneHandler::startRecording()
{
    deviceManager.addAudioCallback(this);
}

void MicrophoneHandler::stopRecording()
{
    deviceManager.removeAudioCallback(this);
    audioDeviceStopped();
}

void MicrophoneHandler::setMicOutputEnabled(bool enabled)
{
    micOutputEnabled = enabled;
}

void MicrophoneHandler::setFFTEnabled(bool enabled)
{
    fftEnabled = enabled;
}

void MicrophoneHandler::setSaveToFile(bool enabled)
{
    saveToFile = enabled;
}