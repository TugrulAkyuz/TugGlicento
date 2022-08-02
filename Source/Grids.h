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
enum  {
    GETDURATION,
    GETSPEED,
    GETNUMOF,
    GETCOORDOFBUTTON
};
const Colour buttonsDefaultColours  (25,25,25);

class Grids;

class SubGrids: public juce::Component,   public juce::Timer
{
public:
    SubGrids(Grids& g, TugGlicentoAudioProcessor& p ,int line) : ownerGrid(g), audioProcessor(p),myLine(line)
    {
         startTimer(20);
    }
    ~SubGrids()
    {
        
    }
    void  paint (juce::Graphics& g) override; 
    void rP()
    {
        repaint();
    }
    void timerCallback()  override
    {
       
        ratio = audioProcessor.getGridContinousData(myLine);
        //if(ratio == -1 ) return;
        repaint();
        
    }
private:
    
  TugGlicentoAudioProcessor& audioProcessor;
  Grids& ownerGrid;
    int myLine;
    float ratio = 0;
};



class SimpleVueMeter : public juce::Component,  public juce::Timer
{
public:
    SimpleVueMeter(TugGlicentoAudioProcessor& p,int line)  : audioProcessor(p){
        startTimer(20);
        
        myLine = line;
        
    }
    ~SimpleVueMeter()
    {
        
    }
    void  paint (juce::Graphics& g) override
    {
        g.setColour (Colours::limegreen);
        
        auto  x = audioProcessor.getLineVolDB(myLine);
       
        int  level = (int)jmap(x, 0.0f, 1.0f, 0.0f, (float)getHeight() - 1);
        if(level < 0 || level > getHeight() - 1) return;
        g.fillRect(0, getHeight() -level, getWidth(),level);
    }
    void resized() override
    {
        
    }
    void timerCallback()  override
    {

            repaint();
    }
    TugGlicentoAudioProcessor& audioProcessor;
    int myLine;
};

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
    
    std::vector<int> getButtonsCoord()
    {
        std::vector<int> b;
        for(int i = 0 ; i <  gridNumberSlider.getValue()  ; i++)
        {
            if(buttons[i]->getToggleState() == true)
              b.push_back(buttons[i]->getX());
        }
        return b;
        
    }
    int getParam(int type, int index = -1)
    {
        int x;
        if(type== GETDURATION)
            x = gridDurationCombo.getSelectedId();
     
        if(type==  GETSPEED)
            x = gridSpeedCombo.getSelectedId();
        
        if(type==  GETNUMOF)
            x = gridNumberSlider.getValue();
        if(type==  GETCOORDOFBUTTON)
            x = buttons[index]->getX();
        return x;
        
    }
    int step;
private:
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;
    juce::OwnedArray<juce::TextButton> buttons;
    CustomRoratySlider gridNumberSlider;
    CustomRoratySlider gridVolSlider;
    SimpleVueMeter  simpleVueMeter;
    juce::ComboBox gridSpeedCombo;
    juce::ComboBox gridDurationCombo;
    juce::ComboBox gridEffectCombo;
    juce::ArrowButton stepArrow;
    
    juce::TextButton soloButton;
  
    juce::Label myLineLabel;
    
    std::unique_ptr  <SubGrids> subGrids;
 
    
    bool dirt = false;
   
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
            soloButton.setButtonText("");
            
           // midiInNote.setColour(juce::Text);
            auto x = getLookAndFeel().findColour(juce::TextButton::ColourIds::buttonColourId);
            soloButton.setColour(juce::TextButton::ColourIds::buttonColourId, x);
        }
        else
        {
            int i = m / 12;
            m %= 12;
            
            soloButton.setButtonText(midiNotes[m] + std::to_string(i));
           // midiInNote.setColour(juce::TextButton::ColourIds::buttonColourId, colourarray[myLine]);
            soloButton.setColour(juce::TextButton::ColourIds::buttonColourId,Colours::lightgreen);
        }
    }
    Rectangle <int>  griidbounds;
    bool stepArray [32] = {};
   juce::OwnedArray    <juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachmentArray;
    std::unique_ptr < AudioProcessorValueTreeState::ComboBoxAttachment>  comBoxSpeedAtaachment;
    std::unique_ptr < AudioProcessorValueTreeState::ComboBoxAttachment>  comBoxDurationAtaachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> gridNumberSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> gridVolSliderAttachment;

    std::unique_ptr  <AudioProcessorValueTreeState::ComboBoxAttachment> effectAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Grids)
    
};
