#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class AdsrComponent : public juce::Component
{   
    public:

        AdsrComponent(juce::AudioProcessorValueTreeState& valueTree);
        ~AdsrComponent() override;

        void paint(juce::Graphics&) override;
        void resized() override;

    private:
    
        juce::Slider attackSlider;
        juce::Slider decaySlider;
        juce::Slider sustainSlider;
        juce::Slider releaseSlider;

        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
        std::unique_ptr<SliderAttachment> attackAttachment;
        std::unique_ptr<SliderAttachment> decayAttachment;
        std::unique_ptr<SliderAttachment> sustainAttachment;
        std::unique_ptr<SliderAttachment> releaseAttachment;

        void setSliderParams(juce::Slider& slider);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};