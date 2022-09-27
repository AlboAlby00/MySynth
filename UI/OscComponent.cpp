#include "OscComponent.h"

OscComponent::OscComponent (juce::AudioProcessorValueTreeState& valueTree, int index) :
    waveComponent{valueTree,index},adsrComponent{valueTree,index},filterComponent{valueTree,index}
{
    addAndMakeVisible(waveComponent);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(filterComponent);
}

OscComponent::~OscComponent()
{

}

void OscComponent::paint (juce::Graphics& g)
{
    
}

void OscComponent::resized()
{
    waveComponent.setBounds(0,0,getWidth()/3,getHeight());
    adsrComponent.setBounds(getWidth()/3,0,getWidth()/3,getHeight());  
    filterComponent.setBounds(2*getWidth()/3,0,getWidth()/3,getHeight());
}