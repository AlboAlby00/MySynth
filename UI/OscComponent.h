#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class OscComponent : public juce::Component
{    
public:

    OscComponent(juce::AudioProcessorValueTreeState& valueTree);

    void paint(juce::Graphics& g);
    void resized();

private:

    juce::ComboBox waveTypeSelector;
    juce::Slider fmDepthSlider;
    juce::Slider fmFrequencySlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFrequencyAttachment;

};