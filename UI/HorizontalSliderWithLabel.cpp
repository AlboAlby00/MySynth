#include "HorizontalSliderWithLabel.h"

HorizontalSliderWithLabel::HorizontalSliderWithLabel(juce::String labelText) :
    label{labelText,labelText}, backgroundColor{juce::Colours::black}
{
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::NoTextBox,true,50,25);

    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}

HorizontalSliderWithLabel::~HorizontalSliderWithLabel()
{
}

void HorizontalSliderWithLabel::addAttachment(juce::AudioProcessorValueTreeState& valueTree, juce::String id)
{
    attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                            (valueTree,id,slider);
}

void HorizontalSliderWithLabel::resized()
{
    slider.setBounds(20, 0, getWidth() - 20, getHeight());
    label.setBounds(0,0,20,getHeight());
}

void HorizontalSliderWithLabel::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColor);
}