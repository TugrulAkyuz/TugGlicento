/*
  ==============================================================================

    AllOtherEffectsPanel.h
    Created: 16 Jun 2022 5:47:51pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeels.h"
#pragma once
using namespace juce;

class ReverbePanel : public Component
{
public:
    ReverbePanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~ReverbePanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;
    Label effectLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbePanel)
};

class DelayPanel : public Component
{
public:
    DelayPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~DelayPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;
    
    Label effectLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPanel)
};


class ChorusPanel : public Component
{
public:
    ChorusPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~ChorusPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;

    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusPanel)
};



class DecimatorPanel : public Component
{
public:
    DecimatorPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~DecimatorPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;

    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DecimatorPanel)
};

class PitchShifterPanel : public Component
{
public:
    PitchShifterPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~PitchShifterPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;

    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchShifterPanel)
};

class DistortionPanel : public Component
{
public:
    DistortionPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~DistortionPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;

    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPanel)
};

class PhaserPanel : public Component
{
public:
    PhaserPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~PhaserPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
 
    
private:

    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;

    CustomRoratySlider cutofSlider;
    CustomRoratySlider qSlider;
    
    CustomRoratySlider attackSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider sustainSlider;
    CustomRoratySlider releaseSlider;
    CustomRoratySlider envSlider;

    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserPanel)
};
