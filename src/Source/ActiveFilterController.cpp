#include "ActiveFilterController.hpp"
#include "FilterTypeEnum.hpp"
#include "SliderComponent.hpp"

ActiveFilterController::ActiveFilterController(FFTFilterProcessor* _processor)
    : processor(_processor)
{
}

/*
parse the filter parameters from Sliders into struct FilterParameters

then filter is added to the processor with callback function
*/

void ActiveFilterController::showFilterParameterDialog(const std::string& filterType, std::size_t id,
                                                                    std::function<void(FilterParameters)> callback) {
    /*
    delete any previous sliders that were created since in method parseSliders
    we create new sliders and add them to the parameterDialog using addCustomComponent
    which doesnt take ownership
    */
    deleteSliders();

    parameterDialog = std::make_unique<juce::AlertWindow>("Filter Parameters",
                                                          "Please enter parameters for the " + filterType,
                                                          juce::AlertWindow::NoIcon);

    FilterType type = parseSliders(filterType);

    parameterDialog->addButton("OK", 1);
    parameterDialog->addButton("Cancel", 0);

    parameterDialog->enterModalState(true, juce::ModalCallbackFunction::create([this, filterType, type, id, callback](int result) {
        FilterParameters filterParameters {id, type, filterType};
        if(result == 0) { // Cancel was pressed
                if (parameterDialog != nullptr) {
                parameterDialog->exitModalState(0);
                parameterDialog.reset();
            }
            return;
        }
        if (result == 1) { // OK was pressed

            for (auto&& [name, slider] : parameterSliders)
            {
                auto value = slider->getValue();
                filterParameters.parameters[name] = value;
            }

            processor->addFilter(filterParameters);

        }

        

        parameterDialog.reset();

        callback(filterParameters);

        parameterSliders.clear();

    }), false);

}

void ActiveFilterController::deleteSliders() {
    for (auto&& [name, slider] : parameterSliders)
    {
		if(slider != nullptr)
			delete slider;
	}
}


/*
create sliders for filter parameters and store pointer to them for later use
*/
FilterType ActiveFilterController::parseSliders(const std::string& filterType) {
    if (filterType == "Low-pass filter" || filterType == "High-pass filter") {
        auto cutoffSlider = new SliderComponent("Cutoff Frequency:", 0.5, 0.0, 1.0);
        parameterSliders["cutoff"] = &cutoffSlider->slider;

        parameterDialog->addCustomComponent(cutoffSlider);

        return filterType == "Low-pass filter" ? FilterType::LowPass : FilterType::HighPass;
    }
    else if (filterType == "Band-pass filter") {
		auto lowCutoffSlider = new SliderComponent("Low Cutoff Frequency:", 0.5, 0.0, 1.0);
		auto highCutoffSlider = new SliderComponent("High Cutoff Frequency:", 0.5, 0.0, 1.0);
		parameterSliders["lowCutoff"] = &lowCutoffSlider->slider;
		parameterSliders["highCutoff"] = &highCutoffSlider->slider;

		parameterDialog->addCustomComponent(lowCutoffSlider);
		parameterDialog->addCustomComponent(highCutoffSlider);

		return FilterType::BandPass;
	}
    else if (filterType == "Reverb") {
		auto decayTimeSlider = new SliderComponent("Decay Time:", 0.5, 0.0, 1.0);
		auto delaySlider = new SliderComponent("Delay:", 0.5, 0.0, 1.0);
		parameterSliders["decay"] = &decayTimeSlider->slider;
		parameterSliders["delay"] = &delaySlider->slider;

		parameterDialog->addCustomComponent(decayTimeSlider);
		parameterDialog->addCustomComponent(delaySlider);

		return FilterType::Reverb;
	}
    else if (filterType == "Spectral shift") {
		auto shiftAmountSlider = new SliderComponent("Shift Amount:", 0.5, 0.0, 1.0);
		parameterSliders["shift"] = &shiftAmountSlider->slider;

		parameterDialog->addCustomComponent(shiftAmountSlider);

		return FilterType::SpectralShift;
	}
    else if (filterType == "Harmonic exciter") {
		return FilterType::HarmonicExciter;
	}
    return FilterType::Unknown;
}