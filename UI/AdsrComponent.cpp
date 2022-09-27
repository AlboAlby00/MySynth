#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& valueTree, int index) 
{  
    attackSlider.addAttachment(valueTree,"ATTACK"+index);
    decaySlider.addAttachment(valueTree,"DECAY"+index);
    sustainSlider.addAttachment(valueTree,"SUSTAIN"+index);
    releaseSlider.addAttachment(valueTree,"RELEASE"+index);

    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}
AdsrComponent::~AdsrComponent()
{

}

void AdsrComponent::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().reduced(10).toFloat();
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds,0.6f,0.7f);
}

void AdsrComponent::resized()
{
    const auto padding = 10;
    const auto bounds = getLocalBounds().reduced(10);
    const auto sliderWidth = bounds.getWidth()/4 -padding;
    const auto sliderHeight = bounds.getHeight() - 2*padding;
    const auto sliderStartX = 2*padding;
    const auto sliderStartY = bounds.getHeight()/2 - sliderHeight/2 + padding;

    attackSlider.setBounds(sliderStartX,sliderStartY,sliderWidth,sliderHeight);
    decaySlider.setBounds(attackSlider.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight()+padding,sliderStartY,sliderWidth,sliderHeight);
}
