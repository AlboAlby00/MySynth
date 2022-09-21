#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), 
        adsrComponent (audioProcessor.valueTree), oscComponent(audioProcessor.valueTree)
{
    setSize (400, 300);


    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(oscComponent);

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
    adsrComponent.setBounds(getWidth()/2,0,getWidth()/2,getHeight());
    oscComponent.setBounds(0,0,getWidth()/2,getHeight());
}

