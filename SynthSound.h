#pragma once

#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
    
};