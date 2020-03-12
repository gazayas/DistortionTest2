/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionTest2AudioProcessorEditor::DistortionTest2AudioProcessorEditor (DistortionTest2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
    
    driveKnob.setSliderStyle(Slider::SliderStyle::Rotary);
    driveKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(&driveKnob);
    
    rangeKnob.setSliderStyle(Slider::SliderStyle::Rotary);
    rangeKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(&rangeKnob);
    
    blendKnob.setSliderStyle(Slider::SliderStyle::Rotary);
    blendKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(&blendKnob);
    
    volumeKnob.setSliderStyle(Slider::SliderStyle::Rotary);
    volumeKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(&volumeKnob);
    
    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.state, "drive", driveKnob);
    rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.state, "range", rangeKnob);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.state, "blend", blendKnob);
    volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.state, "volume", volumeKnob);
}

DistortionTest2AudioProcessorEditor::~DistortionTest2AudioProcessorEditor()
{
}

//==============================================================================
void DistortionTest2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DistortionTest2AudioProcessorEditor::resized()
{
    driveKnob.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    rangeKnob.setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    blendKnob.setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    volumeKnob.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
}
