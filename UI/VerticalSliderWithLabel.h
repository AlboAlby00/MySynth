#pragma once

#include "juce_audio_processors/juce_audio_processors.h"

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class VerticalSliderWithLabel : public juce::Component
{
public:
    VerticalSliderWithLabel(juce::String labelText);
    ~VerticalSliderWithLabel();

    void setBackgroundColor(juce::Colour& colour){backgroundColor=colour;}
    void addAttachment(juce::AudioProcessorValueTreeState& valueTree, juce::String id);

    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    juce::Slider slider;
    juce::Label label;
    juce::Colour backgroundColor;
    std::unique_ptr<Attachment> attachment;


};


