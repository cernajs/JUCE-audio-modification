#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>

#ifndef FILELOADER_HPP
#define FILELOADER_HPP

class FileLoader
{
    juce::File file;
    std::unique_ptr<juce::FileChooser> chooserP;

    juce::AudioTransportSource& _transportSource;
    juce::AudioThumbnail& _thumbnail;
    juce::AudioFormatManager& _formatManager;
public:
    bool loadFile();
    FileLoader(juce::AudioTransportSource& transportSource, juce::AudioThumbnail& thumbnail, juce::AudioFormatManager& formatManager);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileLoader)
};

#endif
