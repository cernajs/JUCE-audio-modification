#include "ActiveFilterComponent.hpp"

/*
creates a visual representation of a filter with the given parameters
*/
ActiveFilterComponent::ActiveFilterComponent(const FilterParameters& _parameters, FFTFilterProcessor* processor, MainComponent* parent)
        : parameters(_parameters), _processor(processor), _parent(parent)
{
    nameLabel.setText(parameters.name, juce::dontSendNotification);
    std::string valueText;
    for (const auto& [name, value] : parameters.parameters)
    {
        valueText += name + " : " + std::to_string(value) + "\n";
    }
    valueLabel.setText(valueText, juce::dontSendNotification);

    removeButton.setButtonText("X");
    removeButton.onClick = [this] { this->removeFilter(); };

    addAndMakeVisible(nameLabel);
    addAndMakeVisible(valueLabel);
    addAndMakeVisible(removeButton);
    setSize(300, 50);
}

ActiveFilterComponent::~ActiveFilterComponent()
{
}

void ActiveFilterComponent::removeFilter()
{
    if(_processor != nullptr)
    {
        _processor->removeFilter(parameters.id);
    }
    if(_parent != nullptr)
    {
        _parent->removeActiveFilterComponent(this);
    }
}

void ActiveFilterComponent::resized()
{
    nameLabel.setBounds(0, 0, 100, 50);
    valueLabel.setBounds(100, 0, 100, 50);
    removeButton.setBounds(200, 0, 100, 50);
}