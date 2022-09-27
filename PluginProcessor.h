#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "DATA/SynthVoice.h"
#include "DATA/SynthSound.h"
#include "DATA/MySynth.h"

//==============================================================================
/**
*/
class TapSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TapSynthAudioProcessor();
    ~TapSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> createSynthParameters(int synth_index);
    MySynth& getSynth1(){return synth1;}
    MySynth& getSynth2(){return synth1;}  

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    juce::AudioProcessorValueTreeState valueTree;

private:

    MySynth synth1;
    MySynth synth2;
    const int numOscillators{2};
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapSynthAudioProcessor)
};