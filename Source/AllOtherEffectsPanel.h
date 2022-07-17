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


    
    CustomRoratySlider roomSizeSlider;
    CustomRoratySlider dampingSlider;
    
    CustomRoratySlider wetLevelSlider;
    CustomRoratySlider dryLevelSlider;
    CustomRoratySlider widthSlider;
    
    
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> widthrAttachment;

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



    CustomRoratySlider dreywetdelaySlider;
    CustomRoratySlider timedelaySlider;
    
    CustomRoratySlider timedelaysyncSlider;
    CustomRoratySlider feedbackdelaySlider;
    CustomRoratySlider delaysyncSlider;

    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> dreywetdelayAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> timedelayAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> timedelaysyncAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> feedbackdelayAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> delaysyncAttachment;

    
    
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


    CustomRoratySlider  rateSlider;
    CustomRoratySlider depthSlider;
    CustomRoratySlider centreDelaySlider;
    CustomRoratySlider feedbackSlider;
    CustomRoratySlider mixSlider;
    
    
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> rateSliderutofAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> centreDelaySliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
 
    
    
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

    CustomRoratySlider pitchSlider;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> pitchSliderAttachment;
    

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

    ComboBox modeCombo;
    CustomRoratySlider driveSlider;
    CustomRoratySlider mixSliader;
    CustomRoratySlider distthresholdSliader;
    CustomRoratySlider denemeSliader;

    std::unique_ptr  <AudioProcessorValueTreeState::ComboBoxAttachment> modeComboAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> mixSliaderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> distthresholdSliaderAttachment;
    
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> denemeSliaderAttachment;
    
    
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

    CustomRoratySlider depthSlider;
    CustomRoratySlider feedbackSlider;
    
    CustomRoratySlider mixSlider;
    CustomRoratySlider decaySliader;
    CustomRoratySlider rateSlider;


    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> decaySliaderAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    
    Label effectLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserPanel)
};



