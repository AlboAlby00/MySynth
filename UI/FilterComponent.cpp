#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& valueTree, int index) :
     freqSlider{"Freq"}, resonanceSlider{"Res"} ,toggleFilter{"Active"}
{

    juce::StringArray choices {"Low","Band","High"};
    filterTypeSelector.addItemList(choices,1);
    filterTypeAttachment = 
        std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
                            (valueTree,"FILTER_TYPE"+index,filterTypeSelector);

    filterTypeLabel.setFont(15.0f);
    filterTypeLabel.setColour(juce::Label::ColourIds::textColourId,juce::Colours::white);
    filterTypeLabel.setJustificationType(juce::Justification::centred);

    freqSlider.addAttachment(valueTree,"FILTER_FREQ"+index);
    resonanceSlider.addAttachment(valueTree,"FILTER_RES"+index);

    filterActiveAttachment = 
        std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
                            (valueTree,"FILTER_ACTIVE"+index,toggleFilter);

    addAndMakeVisible(filterTypeSelector);
    addAndMakeVisible(filterTypeLabel);
    
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(resonanceSlider);

    addAndMakeVisible(toggleFilter);
}

void FilterComponent::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().reduced(10).toFloat();
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds,0.6f,0.7f);
}

void FilterComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10).toFloat();
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()/3 -padding ;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto componentStartX = 20;
    const auto componentStartY = bounds.getHeight()/2-50;

    filterTypeSelector.setBounds(componentStartX,getHeight()/3,getWidth()/3-2*padding,25);
    filterTypeLabel.setBounds(filterTypeSelector.getX(),filterTypeSelector.getY()-30,filterTypeSelector.getWidth(),25);

    toggleFilter.setBounds(componentStartX, 2*getHeight()/3,getWidth()/3,25);

    freqSlider.setBounds(filterTypeSelector.getRight()+padding,componentStartY,sliderWidth,sliderHeight);
    resonanceSlider.setBounds(freqSlider.getRight()+padding,componentStartY,sliderWidth,sliderHeight);


}