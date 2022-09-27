#include "OscData.h"

void OscData::setWaveType(const int waveType)
{
    switch (waveType)
    {
    case 0:
    //sine wave
        initialise([](float x) {return std::sin(x);});
        break;
    case 1:
    //saw wave
        initialise([](float x) {return x/juce::MathConstants<float>::pi;});
        break;
    case 2:
    //square wave
        initialise([](float x) {return x<0.0f ? -1.0f : 1.0f;});
        break;
    case 3:
    //triangle wave
        initialise([](float x) {return x<0.0f ? -x : x;});
        break;
    default:
         jassertfalse;
    }
}

void OscData::setWaveFrequency(int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)+fmMod);
    lastMidiNote=midiNoteNumber;
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    prepare(spec);
    fmOscillator.prepare(spec);
}

void OscData::processNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{

    for(int channel=0; channel<audioBlock.getNumChannels(); channel++)
    {
        for(int sample=0; sample<audioBlock.getNumSamples(); sample++)
        {   
            fmMod = fmOscillator.processSample(audioBlock.getSample(channel,sample))*fmDepth;
        }
    }

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::setFmParams(const float depth, const float freq)
{
    fmDepth=depth;
    fmOscillator.setFrequency(freq);
    auto noteFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote)+fmMod;
    setFrequency(noteFreq>0 ? noteFreq : -noteFreq);
}