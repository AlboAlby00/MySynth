#pragma once

#include <juce_dsp/juce_dsp.h>


class OscData : public juce::dsp::Oscillator<float> {
    
    public:

        void setWaveType(const int waveType);
        void setWaveFrequency(int midiNoteNumber);
        void prepareToPlay(juce::dsp::ProcessSpec spec);
        void processNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
        void setFmParams(const float depth, const float freq);

    private:

        juce::dsp::Oscillator<float> fmOscillator {[](float x) {return std::sin(x);}};
        int lastMidiNote {0};
        float fmDepth {0.0};
        float fmMod;

};