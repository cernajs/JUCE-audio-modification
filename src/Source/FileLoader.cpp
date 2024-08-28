#include "FileLoader.hpp"

FileLoader::FileLoader(juce::AudioTransportSource& transportSource, juce::AudioThumbnail& thumbnail, juce::AudioFormatManager& formatManager) :
 _transportSource(transportSource), _thumbnail(thumbnail), _formatManager(formatManager)  {
    chooserP = std::make_unique<juce::FileChooser>("Please select the audio file you want to load...",
                                    juce::File{},
                                    "*.wav;*.mp3;*.aiff",
                                    true);
}

/* 
selects a file from the file system and loads it into the transport source
*/
bool FileLoader::loadFile() {
    auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
    chooserP->launchAsync(folderChooserFlags, [this] (const juce::FileChooser& chooser) {
        file = chooser.getResult();
        
        if (file.existsAsFile()) {
            auto* reader = _formatManager.createReaderFor(file);

            if (reader != nullptr) {
                auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
                _transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                _thumbnail.setSource (new juce::FileInputSource (file));


                newSource.release();

                return true;
            }
        }
        return false;
    });
    return false;
}