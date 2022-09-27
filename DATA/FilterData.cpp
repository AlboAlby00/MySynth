#include "FilterData.h"

FilterData::FilterData(/* args */)
{
}

FilterData::~FilterData()
{
}

void FilterData::prepareToPlay(const int numChannels,
    const double sampleRate, const int blockSize)
{   
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.numChannels=numChannels;
    spec.sampleRate=sampleRate;
    spec.maximumBlockSize=blockSize;
    filter.prepare(spec);
}

void FilterData::updateFilter(const bool isActive, const int filterType, 
            const float freq, const float resonance)
{
    switch(filterType)
    {
        case 0:
            filter.setType(
                juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(
                juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType(
                juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    filter.setCutoffFrequency(freq);
    filter.setResonance(resonance);
    this->isActive=isActive;
}

void FilterData::processNextBlock(juce::dsp::AudioBlock<float> block)
{
    if(isActive)
    {
        juce::dsp::ProcessContextReplacing<float> context{block};
        filter.process(context);
    }
}

