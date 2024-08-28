#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <juce_audio_formats/juce_audio_formats.h>

class FileWriter
{
public:
    FileWriter();
    ~FileWriter();
    void writeToFile(juce::AudioBuffer<float>& buffer);
    void createNewFile(double sampleRate);
    void saveFile();
private:
    juce::File outputFile;
    std::unique_ptr<juce::FileOutputStream> outputStream;
    std::unique_ptr<juce::AudioFormatWriter> writer;
    juce::WavAudioFormat wavFormat;

    juce::CriticalSection lock;

    std::size_t fileCounter = 0;
};

#endif