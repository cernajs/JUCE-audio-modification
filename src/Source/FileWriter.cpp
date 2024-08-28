
#include <juce_gui_basics/juce_gui_basics.h>

#include "FileWriter.hpp"

FileWriter::FileWriter() {
}

FileWriter::~FileWriter() {

    const juce::ScopedLock sl(lock);
    if (writer != nullptr) {
        writer->flush();
    }
}

void FileWriter::writeToFile(juce::AudioBuffer<float>& buffer) {
    const juce::ScopedLock sl(lock);
    if (writer != nullptr) {
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
}

void FileWriter::createNewFile(double sampleRate) {
    const juce::ScopedLock sl(lock);

    writer.reset();
    outputStream.reset();


    juce::File currentDirectory = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getParentDirectory();
    juce::File newFile = currentDirectory.getNonexistentChildFile("Recording_" + std::to_string(fileCounter), ".wav");

    if (!newFile.exists()) {
        newFile.create();
    }

    outputStream = std::make_unique<juce::FileOutputStream>(newFile);


    if (outputStream != nullptr && outputStream->openedOk()) {
        writer.reset(wavFormat.createWriterFor(outputStream.get(), sampleRate, 2, 16, {}, 0));

        if (writer != nullptr) {
            // writer owns the outputStream, relase it to avoid double deletion
            outputStream.release();
        }
        else {
            juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::AlertIconType::WarningIcon, "Error", "Failed to create writer");
        }
    }
    else {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::AlertIconType::WarningIcon, "Error", "Failed to create output stream");
    }
}

void FileWriter::saveFile() {
    const juce::ScopedLock sl(lock);

    // close the writer if its open
    if (writer != nullptr) {
        writer->flush();
        writer.reset();
    }

    ++fileCounter;
}
