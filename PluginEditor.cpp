#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), 
        osc1{audioProcessor.valueTree,1},
        osc2{audioProcessor.valueTree,2}
{
    setSize (900, 500);
    setResizable(true,true);

    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);

}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
}

void TapSynthAudioProcessorEditor::resized()
{
    osc1.setBounds(0,0,getWidth(),getHeight()/3);
    osc2.setBounds(0,getHeight()/3,getWidth(),getHeight()/3);
}

