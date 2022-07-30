/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginProcessor.h"
#include "Grids.h"
#include "EffectsPanel.h"
#include "PluginEditor.h"

//==============================================================================
TugGlicentoAudioProcessorEditor::TugGlicentoAudioProcessorEditor (TugGlicentoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), effectPanel(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    for(auto i =  (numOfLine - 1); i >= 0 ; i-- )
    {
        auto g = new Grids(audioProcessor,i);
        grids.add(g);
        addAndMakeVisible(g);
    }
    //addAndMakeVisible(globalPanel);
    addAndMakeVisible(effectPanel);
    setSize (900, 420);
}

TugGlicentoAudioProcessorEditor::~TugGlicentoAudioProcessorEditor()
{
}

//==============================================================================
void TugGlicentoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::crimson);
    g.setFont (15.0f);

}

void TugGlicentoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto allarea = getLocalBounds();
  
    auto area = allarea.removeFromTop(200);
    auto h = area.getHeight()/numOfLine;
    for(auto g :grids )
    {
        g->setBounds(area.removeFromTop (h));
        
    }
    effectPanel.setBounds(allarea);
    
}

void TugGlicentoAudioProcessorEditor::setLineForFilterPanel(int lineNo)
{
 
     effectPanel.setFilterPanel(lineNo);
}

void TugGlicentoAudioProcessorEditor::setSoloLine(int lineNo,bool state)
{
 
    soloLineVec[lineNo] = state;
    int array [numOfLine] = {};
    bool tmp_s =  false;
    for(int i = 0 ; i < numOfLine  ; i++)
    {
        if(soloLineVec[i] == 0 ) continue;
        array[i] = 1;
        tmp_s = true;
    }
    if(tmp_s ==  true)
    {
        audioProcessor.setPlayLine(array);
        return;
    }
    for(int i = 0 ; i < numOfLine  ; i++)
       array[i] = 1;
    audioProcessor.setPlayLine(array);
    
}

