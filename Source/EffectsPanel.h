/*
  ==============================================================================

    EffectsPanel.h
    Created: 13 Jun 2022 9:00:32pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeels.h"
#include "FilterPanel.h"
#include "AllOtherEffectsPanel.h"

using namespace juce;

class EffectPanel : public Component
{
public:
    EffectPanel(TugGlicentoAudioProcessor& p);
   
    ~EffectPanel();
    void  paint (juce::Graphics& g) override;
    void resized() override;
    void setFilterPanel(int lineNo);
    
private:

    juce::OwnedArray< FilterPanel > lineFilterPanel;
    int selectedlineFilterPanel = 0;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;
    juce::OwnedArray< ReverbePanel > reverbePanel;
    juce::OwnedArray< DelayPanel > delayPanel;
    juce::OwnedArray< ChorusPanel > chorusPanel;
    juce::OwnedArray< DecimatorPanel > decimatorPanel;
 
    juce::OwnedArray< PitchShifterPanel > pitchShifterPanel;
    juce::OwnedArray< DistortionPanel > distortionPanel;
    juce::OwnedArray< PhaserPanel > phaserPanel;
    
    juce::OwnedArray< RepeaterPanel > repeaterPanel;
    juce::OwnedArray< CombFilterPanel > combFilterPanel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectPanel)
};
