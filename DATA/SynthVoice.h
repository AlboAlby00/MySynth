#pragma once

#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"
#include "FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void prepareToPlay(double sampleRate,int samplesPerBlock, int outputChannels);
    void updateAdsr(const float attack, const float decay, 
            const float sustain, const float release);

    OscData& getOscillator(){ return this->oscillator;}
    FilterData& getFilter(){ return this->filter;}
    juce::dsp::Gain<float>& getGain(){return this->gain;}
    juce::dsp::Panner<float>& getPanner(){return this->panner;}

private:

    juce::AudioBuffer<float> synthBuffer;

    AdsrData adsrData;
    OscData oscillator;
    FilterData filter;
    juce::dsp::Gain<float> gain;
    juce::dsp::Panner<float> panner;

    bool isPrepared{false};

};

