#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "VerticalSliderWithLabel.h"

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class AdsrComponent : public juce::Component
{   
    public:

        AdsrComponent(juce::AudioProcessorValueTreeState& valueTree, int index);
        ~AdsrComponent() override;

        void paint(juce::Graphics&) override;
        void resized() override;

    private:
        VerticalSliderWithLabel attackSlider{"A"};
        VerticalSliderWithLabel decaySlider{"D"};
        VerticalSliderWithLabel sustainSlider{"S"};
        VerticalSliderWithLabel releaseSlider{"R"};





        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};