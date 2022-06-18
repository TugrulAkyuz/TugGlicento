/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>



//==============================================================================
/**
*/
class TugGlicentoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TugGlicentoAudioProcessorEditor (TugGlicentoAudioProcessor&);
    ~TugGlicentoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setLineForFilterPanel(int lineNo);
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TugGlicentoAudioProcessor& audioProcessor;
    juce::OwnedArray< Grids> grids;
    //Satellite satellite;
    //GlobalPanel globalPanel;
    juce::OwnedArray< juce::Label > topInLabel;
    EffectPanel effectPanel;
    int selectedEffect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TugGlicentoAudioProcessorEditor)
};
