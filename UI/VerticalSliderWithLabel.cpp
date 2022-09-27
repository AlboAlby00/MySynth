#include "VerticalSliderWithLabel.h"

VerticalSliderWithLabel::VerticalSliderWithLabel(juce::String labelText) :
    label{labelText,labelText}, backgroundColor{juce::Colours::black}
{
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,50,25);

    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}

VerticalSliderWithLabel::~VerticalSliderWithLabel()
{
}

void VerticalSliderWithLabel::addAttachment(juce::AudioProcessorValueTreeState& valueTree, juce::String id)
{
    attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                            (valueTree,id,slider);
}

void VerticalSliderWithLabel::resized()
{
    slider.setBounds(0, 15, getWidth(), getHeight()-15);
    label.setBounds(0,0,getWidth(),15);
}

void VerticalSliderWithLabel::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColor);
}