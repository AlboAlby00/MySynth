#include "WaveComponent.h"

WaveComponent::WaveComponent(juce::AudioProcessorValueTreeState& valueTree, int index) :
    fmDepthSlider{"FM Depth"}, fmFreqSlider{"FM Freq"}, gainSlider{"V"}, panSlider{"P"}
{

    juce::StringArray choices {"Sine","Saw","Square","Triangle"};
    waveTypeSelector.addItemList(choices,1);
    waveTypeAttachment = 
        std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
                            (valueTree,"OSC_WAVE"+index,waveTypeSelector);
    waveTypeLabel.setFont(15.0f);
    waveTypeLabel.setColour(juce::Label::ColourIds::textColourId,juce::Colours::white);
    waveTypeLabel.setJustificationType(juce::Justification::centred);

    fmDepthSlider.addAttachment(valueTree,"FM_DEPTH"+index);
    fmFreqSlider.addAttachment(valueTree,"FM_FREQ"+index);
    gainSlider.addAttachment(valueTree,"GAIN"+index);
    panSlider.addAttachment(valueTree,"PAN"+index);

    addAndMakeVisible(waveTypeSelector);
    addAndMakeVisible(waveTypeLabel);
    
    addAndMakeVisible(fmDepthSlider);
    addAndMakeVisible(fmFreqSlider);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(panSlider);
}

void WaveComponent::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().reduced(10).toFloat();
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds,0.6f,0.7f);
}

void WaveComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10).toFloat();
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()/3 -padding ;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto componentStartX = 20;
    const auto componentStartY = bounds.getHeight()/2-50;

    waveTypeSelector.setBounds(componentStartX,getHeight()/4,getWidth()/3-2*padding,20);
    waveTypeLabel.setBounds(waveTypeSelector.getX(),waveTypeSelector.getY()-20,waveTypeSelector.getWidth(),15);

    fmDepthSlider.setBounds(waveTypeSelector.getRight()+padding,componentStartY,sliderWidth,sliderHeight);
    fmFreqSlider.setBounds(fmDepthSlider.getRight()+padding,componentStartY,sliderWidth,sliderHeight);
    gainSlider.setBounds(11,getHeight()/2-padding,getWidth()/3,getHeight()/4-padding);
    panSlider.setBounds(11,3*getHeight()/4-padding,getWidth()/3,getHeight()/4-padding);

}




