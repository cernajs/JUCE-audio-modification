## Project Specification and Documentation

# Voice Analysis / Modification Project

## Overview
This project involves developing a C++ application for analyzing and modifying voice in real-time using Fourier transformations. The application will capture audio from a microphone, apply various audio processing techniques, and output the processed audio to a speaker or headphones.

## Objectives
- Capture live audio input.
- Process the audio using Fast Fourier Transform (FFT) and inverse FFT.
- Implement real-time audio effects and modifications.
- Output the processed audio in real time.

## Tools and Technologies
- **Programming Language:** C++
- **Build System:** CMake
- **Audio Processing Library:** JUCE
- **GUI Library:** JUCE
- **Supported Platforms:** Windows, macOS, Linux

## Features
1. **Audio Capture:**
   - Capture audio in real-time from the microphone.

2. **Audio Output:**
   - Output processed audio to speakers or headphones.

3. **FFT-Based Processing:**
   - Apply FFT to convert audio to the frequency domain.
   - Implement voice modification algorithms (e.g., pitch shifting, filtering).
   - Use inverse FFT to convert the processed audio back to the time domain.

4. **Real-Time Audio Effects:**
   - Implement various effects like reverb, echo, or modulation.

5. **GUI for Control:**
   - Create a user interface for adjusting audio effect parameters.
   - Include real-time visual feedback (e.g., waveform display, frequency spectrum).

6. **Performance Optimization:**
   - Ensure low-latency audio processing for real-time performance.
   - (optimally improve performance of FFT using SIMD)

## Detailed Description
1. **Initialization:**
   - Set up JUCE AudioDeviceManager for handling audio devices.
   - Configure audio stream parameters (sample rate, buffer size).

2. **Audio Processing Loop:**
   - Use JUCE’s AudioIODeviceCallback for capturing and outputting audio.
   - In each callback, perform FFT on the input buffer.
   - Apply desired audio processing algorithms.
   - Perform inverse FFT and send the output to the audio buffer for playback.

3. **User Interface:**
   - Develop a GUI using JUCE’s component library.
   - Implement controls for adjusting audio effect parameters.

4. **Testing and Debugging:**
   - Test the application for various scenarios and audio conditions.
   - Optimize for minimal latency and efficient CPU usage.


## Detailed implementation

1. **MainComponent**
   - main component is the main part of application holding and connecting other components
   - it servers as playback device processing audio trought **getNextAudioBlock()**
   - it has timer callback which is used to render wave form of audio every 40ms
   - there is some boilerplate for button state managing

2. **Filters**
   - filters to audio are added by **filter button** in main class
   - this button calls **ActiveFilterComponent** which creates new filter and new component representing the filter
   - filters are separated in representation and visualization. Filtre itself is held in **FFTFilterProcessor** and 
      the visual representation is held separately as **ActiveFilterComponent** in **MainComponent**
   - **Filter.hpp** implemented as polymorphic class with one virtual method **process**, this method is overrided in all 
      filters that inherit from **Filter.hpp**
   - **FFTFilterProcessor** holds different instances of filters. It uses them by simply looping trough them and calling process
      on each one.
   - **FilterComponent** is just visual representation of filters that are used. It serves mainly as visualisation and for deleting
      given filter. When filters are deleted, **FilterComponent** tells it to **MainComponent** and **FFTFilterProcessor**.
   - different filters are implemented in files ending ***Filter.cpp** 

3. **FFT**
   - fft is implemented in files **FFT.cpp** and **FFT.hpp**
   - it uses in-memory implementation of **Cooley-Tukey IFFT** algorithm, which calculated FFT iteratively, without recursion.
      FFT implementation using recursion is too slow for this app use case and caused a lot of white noise.

4. **Component Classes**
   - for separating the responsibility there are numerous classes encapsulating different behaviour
   - **MicrophoneHandler** serves as audio playback devic when microphone is used, it also sends audio data from microphone to
      MainComponent for visualization
   - **FileLoader** hold pointer to **FileChooser** which is used for selecting files from filesystem. When file is selected it
      modifies **transportationSource** to use this audio and **thumbnail** to display this audio
   - **GraphicsComponent** is responsible for redrawing waveform of audio data each time the main component callback is executed.
      For each audio buffer incoming it calculated **chanelHeight** and the draws line between every two samples of audio
   - **FFTFilterProcessor** and **ActiveFilterController** are described in [Filters section](#2-filters)
   - **FileWriter** created new file every time **fileOutputButton** is clicked, when the button is clicked again, it saves
      given file to current directory

5. **Custom Viusal Components**
   - **SliderComponent** is used when creating new Filters. Simple juce::Slider isnt used because it is not compatible with
      juce::Popupmenu
   - **ActiveFilterComponent** is visualization of [Filter](#2-filters)