#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class HorizontalSliderWithLabel : public juce::Component
{
private:

    juce::Label label;
    juce::Slider slider;
    juce::Colour backgroundColor;
    std::unique_ptr<Attachment> attachment;
    
public:

    HorizontalSliderWithLabel(juce::String labelText);
    ~HorizontalSliderWithLabel();

    void setBackgroundColor(juce::Colour& colour){backgroundColor=colour;}
    void addAttachment(juce::AudioProcessorValueTreeState& valueTree, juce::String id);

    void resized() override;
    void paint(juce::Graphics& g) override;

};