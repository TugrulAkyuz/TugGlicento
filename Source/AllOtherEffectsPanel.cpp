/*
  ==============================================================================

    AllOtherEffectsPanel.cpp
    Created: 16 Jun 2022 5:47:51pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#include "AllOtherEffectsPanel.h"


ReverbePanel::ReverbePanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);

    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    
    addAndMakeVisible(effectLabel);
    String l;
    l << "REVERB " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId, colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

ReverbePanel::~ReverbePanel()
{
    
}
void  ReverbePanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void ReverbePanel::resized()
{
    auto allArea = getLocalBounds();
 
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 0);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 
   


}





DelayPanel::DelayPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    
    addAndMakeVisible(effectLabel);
    String l;
    l << "DELAY " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId, colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

DelayPanel::~DelayPanel()
{
    
}
void  DelayPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void DelayPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}


ChorusPanel::ChorusPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    
    addAndMakeVisible(effectLabel);
    String l;
    l << "CHORUS " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId,colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

ChorusPanel::~ChorusPanel()
{
    
}
void  ChorusPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void ChorusPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}

DecimatorPanel::DecimatorPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(effectLabel);
    String l;
    l << "DECIMATOR " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId, colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

DecimatorPanel::~DecimatorPanel()
{
    
}
void  DecimatorPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void DecimatorPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}

PitchShifterPanel::PitchShifterPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);

    
    addAndMakeVisible(effectLabel);
    String l;
    l << "PITCH SHIFT " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId,colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

PitchShifterPanel::~PitchShifterPanel()
{
    
}
void  PitchShifterPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void PitchShifterPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}


DistortionPanel::DistortionPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);

    
    addAndMakeVisible(effectLabel);
    String l;
    l << "DISTORTION " << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId,colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

DistortionPanel::~DistortionPanel()
{
    
}
void  DistortionPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void DistortionPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}

PhaserPanel::PhaserPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);

    
    addAndMakeVisible(effectLabel);
    String l;
    l << "PAHSER" << myLine;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId,colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
}

PhaserPanel::~PhaserPanel()
{
    
}
void  PhaserPanel::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
     
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
    
    
    
  //  g.fillAll ( ColorScheme::getSliderBorderColor());
}
void PhaserPanel::resized()
{
    auto allArea = getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    allArea.reduce(10, 10);
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    qSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    decaySliader.setBounds(area);
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
    releaseSlider.setBounds(area);
    area = allArea.removeFromTop( h);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2));
 

    

}

