#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessor::TapSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
                valueTree{*this,nullptr,"VALUE_TREE",createParameters()},synth1{valueTree,1},synth2{valueTree,2}
#endif
    
{
    synth1.addSound (new SynthSound());
    synth2.addSound (new SynthSound());
    for(int i=0; i<8; i++)
    {
        synth1.addVoice (new SynthVoice());
        synth2.addVoice(new SynthVoice());
    }
    
    
    //std::cout<<"n channels: "<<getTotalNumOutputChannels()<<std::endl;
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
    synth1.prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
    synth2.prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
}

void TapSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


bool TapSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const juce::AudioChannelSet& mainInput  = layouts.getMainInputChannelSet();
    const juce::AudioChannelSet& mainOutput = layouts.getMainOutputChannelSet();

    return true;
}

void TapSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, 
                                juce::MidiBuffer& midiMessages)
{
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    //std::cout<<" buffer size: "<<buffer.getNumChannels();
    //std::cout<<"n in channels after: "<<totalNumInputChannels<<std::endl;
    //std::cout<<"n out channels after: "<<totalNumOutputChannels<<std::endl;
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples()); 

    synth1.updateParameters();
    synth2.updateParameters();

    synth1.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());
    synth2.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());
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
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> synth1params = createSynthParameters(1);
    layout.add(synth1params.begin(),synth1params.end());

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> synth2params = createSynthParameters(2);
    layout.add(synth2params.begin(),synth2params.end());

    return layout;

}

std::vector<std::unique_ptr<juce::RangedAudioParameter>> TapSynthAudioProcessor::createSynthParameters(int synth_index)
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //WAVE

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
         "OSC_WAVE"+synth_index,"osc_wave",   juce::StringArray{"Sine","Saw", "Square","Triangle"}, 0        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "GAIN"+synth_index,"Gain", juce::NormalisableRange<float>{0.0f,1.0f,0.001f,0.3f},0.1f        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "PAN"+synth_index,"Pan", juce::NormalisableRange<float>{-1.0f,1.0f,0.01f},0.0f        
        ));

        //ADSR

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "ATTACK"+synth_index,"Attack", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},0.1f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "DECAY"+synth_index,"Decay", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},0.1f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "SUSTAIN"+synth_index,"Sustain", juce::NormalisableRange<float>{0.1f,1.0f,0.01f},1.0f        
        ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "RELEASE"+synth_index,"Release", juce::NormalisableRange<float>{0.1f,3.0f,0.01f},0.4f        
        ));

        //FM 

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FM_FREQ"+synth_index,"FM Frequency", juce::NormalisableRange<float>{0.1f,1000.0f,0.01f,0.2f},0.0f        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FM_DEPTH"+synth_index,"FM Depth", juce::NormalisableRange<float>{0.0f,1000.0f,0.01f,0.2f},0.0f        
        ));


        //FILTER

    params.push_back(std::make_unique<juce::AudioParameterBool>(
            "FILTER_ACTIVE"+synth_index,"Filter Active",   false        
        ));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
            "FILTER_TYPE"+synth_index,"Filter Type",   juce::StringArray{"LowPass","BandPass", "HighPass"}, 0        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FILTER_FREQ"+synth_index,"Frequency", juce::NormalisableRange<float>{20.0f,20000.0f,0.1f,0.2f},0.0f        
        ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "FILTER_RES"+synth_index,"Resonance", juce::NormalisableRange<float>{1.0f,10.0f,0.1f},1.0f        
        ));

    return params;
}




