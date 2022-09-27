#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "AdsrComponent.h"
#include "WaveComponent.h"
#include "FilterComponent.h"


//==============================================================================
/**
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent (juce::AudioProcessorValueTreeState& valueTree, int index);
    ~OscComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    AdsrComponent adsrComponent;
    WaveComponent waveComponent;
    FilterComponent filterComponent;

};