cmake_minimum_required(VERSION 3.22)

project(BASIC_APP VERSION 0.0.1)

# add_compile_options(-fno-pie)
# add_link_options(-no-pie)

juce_add_gui_app(${PROJECT_NAME}
    PRODUCT_NAME "BasicApp"
    COMPANY_NAME "MyCompany"
    VERSION "${PROJECT_VERSION}"
    DOCUMENT_EXTENSIONS "txt;pdf"
    PRODUCT_NAME "TestApp"
    MICROPHONE_PERMISSION_ENABLED TRUE
    MICROPHONE_PERMISSION_TEXT "Amazing Audio App needs access to your audio interface"
    HARDENED_RUNTIME_ENABLED TRUE
    HARDENED_RUNTIME_OPTIONS com.apple.security.device.audio-input
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TransportStateC.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/WindowFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WindowFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FFT.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FFT.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MicrophoneHandler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MicrophoneHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileLoader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FFTFilterProcessor.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FFTFilterProcessor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Filter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FilterParameters.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LowPassFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LowPassFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ActiveFilterComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ActiveFilterComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HighPassFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HighPassFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BandPassFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BandPassFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReverbFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReverbFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HarmonicExciterFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HarmonicExciterFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FilterTypeEnum.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SpectralShiftFilter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SpectralShiftFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SliderComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SliderComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ActiveFilterController.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ActiveFilterController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileWriter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileWriter.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_gui_extra
        juce::juce_audio_utils
        juce::juce_audio_formats
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_definitions(${PROJECT_NAME}
PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:BASIC_APP,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:BASIC_APP,JUCE_VERSION>")

