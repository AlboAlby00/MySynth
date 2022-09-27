#include "RotarySliderWithLabel.h"

RotarySliderWithLabel::RotarySliderWithLabel(juce::String labelText) :
    label{labelText,labelText}
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,50,20);

    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    label.setColour(juce::Label::ColourIds::textColourId,juce::Colours::white);

    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}

RotarySliderWithLabel::~RotarySliderWithLabel()
{
}

void RotarySliderWithLabel::addAttachment(juce::AudioProcessorValueTreeState& valueTree, juce::String id)
{
    attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                            (valueTree,id,slider);
}

void RotarySliderWithLabel::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColor);
}

void RotarySliderWithLabel::resized()
{
    slider.setBounds(0,20,getWidth(),getHeight()-40);
    label.setBounds(slider.getX(),slider.getY()-15,slider.getWidth(),20);
}

