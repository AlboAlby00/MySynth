#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "RotarySliderWithLabel.h"

class FilterComponent : public juce::Component
{    
public:

    FilterComponent(juce::AudioProcessorValueTreeState& valueTree, int index);

    void paint(juce::Graphics& g);
    void resized();

private:

    juce::ComboBox filterTypeSelector;
    juce::Label filterTypeLabel{"Filter Type","Filter Type"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    RotarySliderWithLabel freqSlider;
    RotarySliderWithLabel resonanceSlider;

    juce::ToggleButton toggleFilter;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filterActiveAttachment;

};