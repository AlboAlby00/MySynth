#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "OscData.h"
#include "SynthVoice.h"


class MySynth : public juce::Synthesiser
{
public:
    MySynth(juce::AudioProcessorValueTreeState& tree, int synth_index);
    ~MySynth();

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> createParameters();
    void updateParameters();
    void prepareToPlay(double sampleRate, int samplesPerBlock,int numOutputChannels);
    juce::AudioProcessorValueTreeState& getValueTree(){return valueTree;}

private:
    const int index;
    juce::AudioProcessorValueTreeState& valueTree;
    
};


