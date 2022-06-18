/*
  ==============================================================================

    Grids.h
    Created: 12 Jun 2022 8:35:40am
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#pragma once
#include "Grids.h"
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeels.h"
 
#pragma once
using namespace juce;

const std::string midiNotes[]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

class Grids : public juce::Component,  public juce::Timer
{
public:
    Grids(TugGlicentoAudioProcessor&,int line);
    ~Grids()
    {
        setLookAndFeel (nullptr);
    }
    void  paint (juce::Graphics& g) override;
    void resized() override;

    void setEnable(bool r)
    {
        gridVolSlider.setEnabled(r);
    }
    
    void mouseDown (const MouseEvent& e) override;

private:
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;
    juce::OwnedArray<juce::TextButton> buttons;
    CustomRoratySlider gridNumberSlider;
    CustomRoratySlider gridVolSlider;
    juce::ComboBox gridSpeedCombo;
    juce::ComboBox gridDurationCombo;
    juce::ComboBox gridEffectCombo;
    juce::ArrowButton stepArrow;
    
    juce::TextButton midiInNote;
  
    juce::Label myLineLabel;
    
    bool dirt = false;
    int step;
    int myLine;
    int myMidiNote;
    void timerCallback() override
    {
  
        int st = audioProcessor.getSteps(myLine);
        if(step != st)
        {
            step = st;
            resized();
        }


  
    }
    
    void setMidiName(int m)
    {
        if(m ==  -1)
        {
          midiInNote.setButtonText("");
            
           // midiInNote.setColour(juce::Text);
            auto x = getLookAndFeel().findColour(juce::TextButton::ColourIds::buttonColourId);
            midiInNote.setColour(juce::TextButton::ColourIds::buttonColourId, x);
        }
        else
        {
            int i = m / 12;
            m %= 12;
            
            midiInNote.setButtonText(midiNotes[m] + std::to_string(i));
           // midiInNote.setColour(juce::TextButton::ColourIds::buttonColourId, colourarray[myLine]);
            midiInNote.setColour(juce::TextButton::ColourIds::buttonColourId,Colours::lightgreen);
        }
    }
    
    bool stepArray [32];
   juce::OwnedArray    <juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentArray;
    std::unique_ptr < AudioProcessorValueTreeState::ComboBoxAttachment>  comBoxSpeedAtaachment;
    std::unique_ptr < AudioProcessorValueTreeState::ComboBoxAttachment>  comBoxDurationAtaachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> gridNumberSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> gridVolSliderAttachment;

    std::unique_ptr  <AudioProcessorValueTreeState::ComboBoxAttachment> effectAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Grids)
    
};
