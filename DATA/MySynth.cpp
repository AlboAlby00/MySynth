#include "MySynth.h"

MySynth::MySynth(juce::AudioProcessorValueTreeState& tree, int synth_index) :
    index{synth_index}, valueTree{tree}
{
    
}

MySynth::~MySynth()
{
}

std::vector<std::unique_ptr<juce::RangedAudioParameter>> MySynth::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
         "OSC_WAVE"+index,"osc_wave",   juce::StringArray{"Sine","Saw", "Square","Triangle"}, 0        
        ));

        //ADSR

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "ATTACK"+index,"Attack", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},0.1f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "DECAY"+index,"Decay", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},0.1f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "SUSTAIN"+index,"Sustain", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},1.0f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "RELEASE"+index,"Release", juce::NormalisableRange<float>{0.1f,3.0f,0.01f},0.4f        
        ));

        //FM 

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FM_FREQ"+index,"FM Frequency", juce::NormalisableRange<float>{0.1f,1000.0f,0.01f,0.2f},0.0f        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FM_DEPTH"+index,"FM Depth", juce::NormalisableRange<float>{0.0f,1000.0f,0.01f,0.2f},0.0f        
        ));

        //FILTER

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
            "FILTER_TYPE"+index,"Filter Type",   juce::StringArray{"LowPass","BandPass", "HighPass"}, 0        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FILTER_FREQ"+index,"Frequency", juce::NormalisableRange<float>{20.0f,20000.0f,0.1f,0.2f},0.0f        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FILTER_RES"+index,"Resonance", juce::NormalisableRange<float>{1.0f,10.0f,0.1f},1.0f        
        ));

    return params;
}

void MySynth::updateParameters()
{
    for(int voiceIndex=0; voiceIndex<getNumVoices(); voiceIndex++)
    {
        if(auto voice = dynamic_cast<SynthVoice*> (getVoice(voiceIndex)))
        {
            OscData& oscillator = voice->getOscillator();
            juce::dsp::Gain<float>& gain = voice->getGain();
            juce::dsp::Panner<float>& panner = voice->getPanner();

            //OSC

            auto waveType = valueTree.getRawParameterValue("OSC_WAVE"+index);
            int selectedWave = waveType->load();

            oscillator.setWaveType(selectedWave);

            float gainValue = valueTree.getRawParameterValue("GAIN"+index)->load();

            gain.setGainLinear(gainValue);

            auto pan = valueTree.getRawParameterValue("PAN"+index);
            float panValue = pan->load();
            //std::cout << panValue << " "<<std::endl;
            panner.setPan(panValue);

            //ADSR

            auto attack = valueTree.getRawParameterValue("ATTACK"+index);
            auto decay = valueTree.getRawParameterValue("DECAY"+index);
            auto sustain = valueTree.getRawParameterValue("SUSTAIN"+index);
            auto release = valueTree.getRawParameterValue("RELEASE"+index);

            float attackValue = attack->load();
            float decayValue = decay->load();
            float sustainValue = sustain->load();
            float releaseValue = release->load();

            voice->updateAdsr(attackValue,decayValue,sustainValue,releaseValue);

            //FM

            auto frequency = valueTree.getRawParameterValue("FM_FREQ"+index);
            float frequencyValue = frequency->load();
            auto depth = valueTree.getRawParameterValue("FM_DEPTH"+index);
            float depthValue = depth->load();
            
            oscillator.setFmParams(depthValue,frequencyValue);     

            //Filter

            FilterData& filter = voice->getFilter();

            auto filterType = valueTree.getRawParameterValue("FILTER_TYPE"+index);
            int filterTypeValue = filterType->load();
            auto filterFreq = valueTree.getRawParameterValue("FILTER_FREQ"+index);
            float filterFreqValue = filterFreq->load();
            auto resonance = valueTree.getRawParameterValue("FILTER_RES"+index);
            float resValue = resonance->load();
            bool isActive = valueTree.getRawParameterValue("FILTER_ACTIVE"+index)->load();

            filter.updateFilter(isActive,filterTypeValue,filterFreqValue,resValue);

        }
    }
}

void MySynth::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    setCurrentPlaybackSampleRate (sampleRate);
    for(int voiceIndex=0; voiceIndex<getNumVoices(); voiceIndex++){
       if( auto voice = dynamic_cast<SynthVoice*>(getVoice(voiceIndex))){
           voice->prepareToPlay(sampleRate,samplesPerBlock,numOutputChannels);
           OscData& oscillator = voice->getOscillator();
           oscillator.setWaveType(3);
        
       }
    }
}
