#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessor::TapSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), 
                       valueTree(*this,nullptr,"VALUE_TREE",createParameters())
#endif
{
    synth.addSound (new SynthSound());
    synth.addVoice (new SynthVoice());
}

TapSynthAudioProcessor::~TapSynthAudioProcessor()
{
    
}

//==============================================================================
const juce::String TapSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TapSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TapSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TapSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TapSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TapSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TapSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TapSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TapSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TapSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TapSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    for(int voiceIndex=0; voiceIndex<synth.getNumVoices(); voiceIndex++){
       if( auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(voiceIndex))){
           voice->prepareToPlay(sampleRate,samplesPerBlock,getNumOutputChannels());
           OscData& oscillator = voice->getOscillator();
           oscillator.setWaveType(1);
       }
    }
}

void TapSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TapSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TapSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, 
                                juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for(int voiceIndex=0; voiceIndex<synth.getNumVoices(); ++voiceIndex)
    {
        if(auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(voiceIndex)))
        {
            OscData& oscillator = voice->getOscillator();

            //ADSR

            auto attack = valueTree.getRawParameterValue("ATTACK");
            auto decay = valueTree.getRawParameterValue("DECAY");
            auto sustain = valueTree.getRawParameterValue("SUSTAIN");
            auto release = valueTree.getRawParameterValue("RELEASE");

            float attackValue = attack->load();
            float decayValue = decay->load();
            float sustainValue = sustain->load();
            float releaseValue = release->load();

            voice->updateAdsr(attackValue,decayValue,sustainValue,releaseValue);

            //OSC

            auto waveType = valueTree.getRawParameterValue("OSC_WAVE");
            int selectedWave = waveType->load();

            oscillator.setWaveType(selectedWave);

            //FM

            auto frequency = valueTree.getRawParameterValue("FM_FREQ");
            float frequencyValue = frequency->load();
            auto depth = valueTree.getRawParameterValue("FM_DEPTH");
            float depthValue = depth->load();
            
            oscillator.setFmParams(depthValue,frequencyValue);     
        }
    }
    synth.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());
}

//==============================================================================
bool TapSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TapSynthAudioProcessor::createEditor()
{
    return new TapSynthAudioProcessorEditor (*this);
}

//==============================================================================
void TapSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TapSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TapSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout TapSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
         "OSC_WAVE","osc_wave",   juce::StringArray{"Sine","Saw", "Square","Triangle"}, 0        
    ));

    //ADSR

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "ATTACK","Attack", juce::NormalisableRange<float>{0.1f,1.0f},0.1f        
    ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "DECAY","Decay", juce::NormalisableRange<float>{0.1f,1.0f},0.1f        
    ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "SUSTAIN","Sustain", juce::NormalisableRange<float>{0.1f,1.0f},1.0f        
    ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "RELEASE","Release", juce::NormalisableRange<float>{0.1f,3.0f},0.4f        
    ));

    //FM 

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "FM_FREQ","FM Frequency", juce::NormalisableRange<float>{0.1f,1000.0f},50.0f        
    ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
         "FM_DEPTH","FM Depth", juce::NormalisableRange<float>{0.0f,1000.0f},500.0f        
    ));

    return {params.begin(), params.end()};
}
