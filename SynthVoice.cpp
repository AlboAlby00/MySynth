#include "SynthVoice.h"


bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                                                 int currentPitchWheelPosition)
{
    oscillator.setWaveFrequency(midiNoteNumber);
    adsrData.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsrData.noteOff();
    if(!allowTailOff || ! adsrData.isActive()){
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}



void SynthVoice::prepareToPlay(double sampleRate,int samplesPerBlock, int outputChannels){

    adsrData.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    oscillator.prepareToPlay(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.1f);

    isPrepared = true;

}

void SynthVoice::updateAdsr(const float attack, const float decay, 
            const float sustain, const float release)
{
    adsrData.updateAdsr(attack,release,sustain,release);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, 
                                            int numSamples)
{
    jassert(isPrepared);

    if(!isVoiceActive()){
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(),numSamples,false,false,true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{synthBuffer};
    oscillator.processNextBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsrData.applyEnvelopeToBuffer(synthBuffer,0,synthBuffer.getNumSamples());

    for(int channel = 0; channel<outputBuffer.getNumChannels(); channel++)
    {
         outputBuffer.addFrom(channel,startSample,synthBuffer,channel,0,numSamples);
         if(!adsrData.isActive()){
             clearCurrentNote();
         }
    }

}


