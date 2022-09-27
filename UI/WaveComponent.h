#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "RotarySliderWithLabel.h"
#include "HorizontalSliderWithLabel.h"

class WaveComponent : public juce::Component
{    
public:

    WaveComponent
(juce::AudioProcessorValueTreeState& valueTree, int index);

    void paint(juce::Graphics& g);
    void resized();

private:

    juce::ComboBox waveTypeSelector;
    juce::Label waveTypeLabel{"Wave Type","Wave Type"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeAttachment;

    RotarySliderWithLabel fmDepthSlider;
    RotarySliderWithLabel fmFreqSlider;

    HorizontalSliderWithLabel gainSlider;
    HorizontalSliderWithLabel panSlider;

};