#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class FilterData
{
public:
    FilterData(/* args */);
    ~FilterData();

    void prepareToPlay(const int numChannels,
        const double sampleRate, const int blockSize);
    void updateFilter(const bool isActive, const int filterType, 
            const float freq, const float resonance);
    void processNextBlock(juce::dsp::AudioBlock<float> block);
    void reset(){filter.reset();}
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isActive;
};


