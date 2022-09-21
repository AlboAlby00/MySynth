#include "OscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& valueTree) 
{
    juce::StringArray choices {"Sine","Saw","Square","Triangle"};
    waveTypeSelector.addItemList(choices,1);
    waveTypeAttachment = 
        std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
                            (valueTree,"OSC_WAVE",waveTypeSelector);

    fmDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,getWidth()/2,20);
    fmDepthAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                            (valueTree,"FM_DEPTH",fmDepthSlider);

    fmFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,getWidth()/2,20);
    fmFrequencyAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                            (valueTree,"FM_FREQ",fmFrequencySlider);

    addAndMakeVisible(waveTypeSelector);
    addAndMakeVisible(fmDepthSlider);
    addAndMakeVisible(fmFrequencySlider);
}

void OscComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    const int waveTypeSelectorHeight = getHeight()/10;
    const int sliderLenght = getWidth()/2;
    waveTypeSelector.setBounds(0,0,100,waveTypeSelectorHeight);
    fmDepthSlider.setBounds(0,waveTypeSelectorHeight,sliderLenght,sliderLenght);
    fmFrequencySlider.setBounds(sliderLenght,waveTypeSelectorHeight,sliderLenght,sliderLenght);

}




