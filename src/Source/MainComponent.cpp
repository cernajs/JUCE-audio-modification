#include "MainComponent.h"
#include "FFT.hpp"
#include "WindowFunction.hpp"
#include "FilterParameters.hpp"
#include "FilterTypeEnum.hpp"
#include "SliderComponent.hpp"
#include "ActiveFilterController.hpp"

//==============================================================================
MainComponent::MainComponent() : state(Stopped), thumbnailCache(5),
                                thumbnail(512, formatManager, thumbnailCache),
                                deviceSelector(deviceManager, 0, 2, 0, 2, false, false, true, false),
                                fileLoader(transportSource, thumbnail, formatManager),
                                graphicsComponent(&audioBuffer),
                                fftFilterProcessor(),
                                activeFilterController(&fftFilterProcessor),
                                fileWriter(),
                                micHandler(customDeviceManager, transportSource, this, &fftFilterProcessor, &fileWriter)
{
    addAndMakeVisible(uploadButton);
    uploadButton.setBounds(10, 10, 80, 20);
    uploadButton.setButtonText("Upload");
    uploadButton.onClick = [this] { buttonClicked(&uploadButton); };

    addAndMakeVisible(playButton);
    playButton.setBounds(100, 10, 80, 20);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { buttonClicked(&playButton); };

    addAndMakeVisible(stopButton);
    stopButton.setBounds(190, 10, 80, 20);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { buttonClicked(&stopButton); };

    addAndMakeVisible(micButton);
    micButton.setBounds(280, 10, 80, 20);
    micButton.setButtonText("Mic");
    micButton.onClick = [this] { buttonClicked(&micButton); };

    addAndMakeVisible(fftButton);
    fftButton.setBounds(370, 10, 80, 20);
    fftButton.setButtonText("FFT");
    fftButton.onClick = [this] { buttonClicked(&fftButton); };

    addAndMakeVisible(filterMenuButton);
    filterMenuButton.setBounds(460, 10, 80, 20);
    filterMenuButton.setButtonText("Filters");
    filterMenuButton.onClick = [this] {
        juce::PopupMenu m;
        m.addItem("Low-pass filter", [this] { showFilterParameterDialog("Low-pass filter"); });
        m.addItem("High-pass filter", [this] { showFilterParameterDialog("High-pass filter"); });
        m.addItem("Band-pass filter", [this] { showFilterParameterDialog("Band-pass filter"); });
        m.addItem("Reverb", [this] { showFilterParameterDialog("Reverb"); });
        m.addItem("Spectral shift", [this] { showFilterParameterDialog("Spectral shift"); });
        m.addItem("Harmonic exciter", [this] { showFilterParameterDialog("Harmonic exciter"); });
        m.showMenuAsync(juce::PopupMenu::Options());
    };

    addAndMakeVisible(fileOutputButton);
    fileOutputButton.setBounds(550, 10, 80, 20);
    fileOutputButton.setButtonText("File output");
    fileOutputButton.onClick = [this] { buttonClicked(&fileOutputButton); };

    addAndMakeVisible(graphicsComponent);
    graphicsComponent.setBounds(10, 100, getWidth() - 20, getHeight() - 120);
    graphicsComponent.render();

    addAndMakeVisible(deviceSelector);
    deviceSelector.setBounds(10, 40, 400, 200);

    customDeviceManager.initialise(2, 2, nullptr, true);

    setAudioChannels (2, 2);

    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);

    thumbnail.addChangeListener(this);

    startTimer(40);

    outputBuffer.reserve(512);
    buffer.reserve(512);

    setSize (1200, 800);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    graphicsComponent.setBounds(10, 100, getWidth() - 20, getHeight() - 120);


    int rightMargin = 10;
    int verticalSpacing = 10;
    int componentWidth = 300;
    int componentHeight = 50;

    int xPosition = getWidth() - componentWidth - rightMargin;
    int yPosition = 10;

    for (auto* filterComponent : activeFilters)
    {
        filterComponent->setBounds(xPosition, yPosition, componentWidth, componentHeight);
        yPosition += componentHeight + verticalSpacing;
    }
}

/*
called when creating new audio filter
*/
void MainComponent::showFilterParameterDialog(const std::string& filterType) {
    ++_id;
    activeFilterController.showFilterParameterDialog(filterType, _id, [this](FilterParameters filterParameters) {
        if(filterParameters.id != 0) {
            fftFilterProcessor.addFilter(filterParameters);
            auto activeFilterComponent = new ActiveFilterComponent(filterParameters, &fftFilterProcessor, this);
            activeFilters.add(activeFilterComponent);
            addAndMakeVisible(activeFilterComponent);
            resized();
        }
    });
}

void MainComponent::removeActiveFilterComponent(ActiveFilterComponent* component)
{
    activeFilters.removeObject(component);
    resized();
}

/*
change state of app when transportation source is changed
transportation source = audio file
*/
void MainComponent::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &transportSource) {
        if (transportSource.isPlaying()) {
            changeState(Playing);
        } else {
            changeState(Stopped);
        }
    }
    if (source == &thumbnail) {
        thumbnailChanged();
    }
}

/*
button state management
*/
void MainComponent::changeState(TransportStateC newState)
{
    const juce::ScopedLock sl(lock);
    if (state != newState)
    {
        auto oldState = state;
        state = newState;

        switch (state)
        {
            case Stopped:
                playButton.setEnabled(true);
                stopButton.setEnabled(false);
                micButton.setEnabled(true);
                transportSource.setPosition(0.0);
                break;

            case Playing:
                playButton.setEnabled(false);
                stopButton.setEnabled(true);
                break;

            case Starting:
                playButton.setEnabled(false);
                stopButton.setEnabled(true);
                micButton.setEnabled(false);
                transportSource.start();
                break;

            case Stopping:
                if(oldState == MicrophonePlaying) {
                    micHandler.stopRecording();
                    micHandler.setMicOutputEnabled(false);
                }
                if(oldState == Playing) {
                    transportSource.stop();
                }
                graphicsComponent.repaint();

                playButton.setEnabled(true);
                stopButton.setEnabled(false);
                micButton.setEnabled(true);
                break;

            case MicrophonePlaying:
                playButton.setEnabled(false);
                stopButton.setEnabled(true);
                micHandler.startRecording();
                micHandler.setMicOutputEnabled(true);
                break;
        }
    }
}

/*
sets auddio data used by graphics component for drawing waveform
*/
void MainComponent::setAudioData(const float* data, int size)
{
    audioBuffer.setSize(1, size);
    for (int i = 0; i < size; i++) {
        audioBuffer.setSample(0, i, data[i]);
    }
}


void MainComponent::thumbnailChanged()
{
    graphicsComponent.repaint();
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

/*
function called when audio is processed from file (almost all the time)
(called by JUCE)
*/
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    if (state == MicrophonePlaying) {
        return;
    }

    // get next audio block from file
    transportSource.getNextAudioBlock(bufferToFill);

    // resize buffer if there was change in number of samples
    size_t size = static_cast<size_t>(bufferToFill.numSamples);
    if (outputBuffer.size() < size)
    {
        outputBuffer.resize(size);
    }

    // perform fft and apply filters
    if (fftButton.getToggleState()) {
        int numChannels = bufferToFill.buffer->getNumChannels();

        for (int channel = 0; channel < numChannels; ++channel)
        {

            if(buffer.size() < size)
            {
                buffer.resize(size);
            }
            for (size_t i = 0; i < size; ++i)
            {
                buffer[i] = bufferToFill.buffer->getSample(channel, i);
            }

            FFT::fft(buffer, outputBuffer);

            fftFilterProcessor.process(outputBuffer);

            FFT::ifft(outputBuffer, buffer);

            for (size_t i = 0; i < size; ++i)
            {
                bufferToFill.buffer->setSample(channel, i, static_cast<float>(buffer[i].real()));
            }

        }
    }

    // write to file if file output is enabled
    if(fileOutputButton.getToggleState() && state == Playing) {
        fileWriter.writeToFile(*bufferToFill.buffer);
    }

    // set audio data for graphics component
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
        setAudioData(bufferToFill.buffer->getReadPointer(0), size);
    }
}

/*
repaints graphics every time callback is called
in this case 40ms - primarily for unnecessary repaints
*/
void MainComponent::timerCallback()
{
    if(state == MicrophonePlaying || state == Playing) {
        graphicsComponent.repaint();
    }
}

/*
boilerplate for preparing audio to play (called by JUCE)
*/
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MainComponent::releaseResources()
{
}

double MainComponent::microphoneSamplerate() {
    return micHandler.getSampleRate();
}

/*
button click event handling
*/
void MainComponent::buttonClicked(juce::Button* button)
{
    if(button == &uploadButton) {
       if(fileLoader.loadFile()) {
           changeState(Stopped);
       }
    }
    else if (button == &playButton) {
        if (!micOutputEnabled) {
            changeState(Starting);
        }
    }
    else if (button == &stopButton) {
        changeState(Stopping);
    }

    else if (button == &micButton) {
        if (state == MicrophonePlaying) {
            changeState(Stopping);
        } else {
            changeState(MicrophonePlaying);
        }
    }
    else if(button == &fftButton) {
        micHandler.setFFTEnabled(fftButton.getToggleState());
    }
    else if(button == &fileOutputButton) {
        micHandler.setSaveToFile(fileOutputButton.getToggleState());
        if(fileOutputButton.getToggleState()) {
            double sampleRate = state == MicrophonePlaying ? microphoneSamplerate() : currentSampleRate;
            fileWriter.createNewFile(sampleRate);
        } else {
            fileWriter.saveFile();
        }
    }
}
