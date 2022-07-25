/*
  ==============================================================================

    EffectsPanel.cpp
    Created: 13 Jun 2022 9:00:32pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/


#include "EffectsPanel.h"

#define USE_LIVE_CONSTANT true
#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define  colorHelper(c) c;
#endif
namespace ColorScheme
{
    inline juce::Colour getColorHelper()
    {
        return colorHelper(juce::Colours::blue);
    }
}

EffectPanel::EffectPanel(TugGlicentoAudioProcessor& p) : audioProcessor(p)
{
    for(auto i =  0; i < numOfLine ; i++ )
    {
        lineFilterPanel.add(new FilterPanel(audioProcessor,i));
        reverbePanel.add(new ReverbePanel(audioProcessor,i));
        delayPanel.add(new DelayPanel(audioProcessor,i));
        chorusPanel.add(new ChorusPanel(audioProcessor,i));
        decimatorPanel.add(new DecimatorPanel(audioProcessor,i));
        
        pitchShifterPanel.add(new PitchShifterPanel(audioProcessor,i));
        distortionPanel.add(new DistortionPanel(audioProcessor,i));
        phaserPanel.add(new PhaserPanel(audioProcessor,i));
        combFilterPanel.add(new CombFilterPanel(audioProcessor,i));
        repeaterPanel.add(new RepeaterPanel(audioProcessor,i));
        
        
        addAndMakeVisible(lineFilterPanel.getLast());
        addAndMakeVisible(reverbePanel.getLast());
        addAndMakeVisible(delayPanel.getLast());
        addAndMakeVisible(chorusPanel.getLast());
        addAndMakeVisible(decimatorPanel.getLast());
        
        addAndMakeVisible(pitchShifterPanel.getLast());
        addAndMakeVisible(distortionPanel.getLast());
        addAndMakeVisible(phaserPanel.getLast());
        addAndMakeVisible(combFilterPanel.getLast());
        addAndMakeVisible(repeaterPanel.getLast());
        
        
 
    }
 
}

EffectPanel::~EffectPanel()
{
    
}
void  EffectPanel::paint (juce::Graphics& g)
{
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
 // g.fillAll ( ColorScheme::getColorHelper());
    g.fillAll (Colours::darkturquoise);
}
void EffectPanel::resized()
{
/*
    for(auto i =  0; i < numOfLine ; i++ )
    {
        auto allArea =  getLocalBounds();
        auto area = allArea.removeFromLeft(100);
        lineFilterPanel.getUnchecked(i)->setBounds(area);
        lineFilterPanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        reverbePanel.getUnchecked(i)->setBounds(area);
        reverbePanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        delayPanel.getUnchecked(i)->setBounds(area);
        delayPanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        chorusPanel.getUnchecked(i)->setBounds(area);
        chorusPanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        decimatorPanel.getUnchecked(i)->setBounds(area);
        decimatorPanel.getUnchecked(i)->setVisible(false);
 
        area = allArea.removeFromLeft(100);
        pitchShifterPanel.getUnchecked(i)->setBounds(area);
        pitchShifterPanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        distortionPanel.getUnchecked(i)->setBounds(area);
        distortionPanel.getUnchecked(i)->setVisible(false);
        area = allArea.removeFromLeft(100);
        phaserPanel.getUnchecked(i)->setBounds(area);
        phaserPanel.getUnchecked(i)->setVisible(false);
        

    }
 */

   /*
    lineFilterPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == REVERB)
       reverbePanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == DELAY)
        delayPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == CHORUS)
       chorusPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == DECIMATOR)
      decimatorPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    
    pitchShifterPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == DISTORTION)
        distortionPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    if(audioProcessor.selectedEffect[selectedlineFilterPanel] == PHASER)
       phaserPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    
 */
    auto allArea =  getLocalBounds();
    auto area = allArea.removeFromLeft(300);
    for(auto i =  0; i < numOfLine ; i++ )
    {
        lineFilterPanel.getUnchecked(i)->setBounds(area);
        lineFilterPanel.getUnchecked(i)->setVisible(false);
         
       
        reverbePanel.getUnchecked(i)->setVisible(false);
        delayPanel.getUnchecked(i)->setVisible(false);
        chorusPanel.getUnchecked(i)->setVisible(false);
        decimatorPanel.getUnchecked(i)->setVisible(false);
        phaserPanel.getUnchecked(i)->setVisible(false);
        distortionPanel.getUnchecked(i)->setVisible(false);
        pitchShifterPanel.getUnchecked(i)->setVisible(false);
        combFilterPanel.getUnchecked(i)->setVisible(false);
        repeaterPanel.getUnchecked(i)->setVisible(false);
        
        
    }
    lineFilterPanel.getUnchecked(selectedlineFilterPanel)->setVisible(true);
    Component *x ;
    for(auto i =  0; i < numOfLine ; i++ )
    {
        area = allArea.removeFromLeft(100);
        if(audioProcessor.selectedEffect[i] == REVERB) x = reverbePanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == DELAY) x = delayPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == CHORUS) x = chorusPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == DECIMATOR) x = decimatorPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == PHASER) x = phaserPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == DISTORTION) x = distortionPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == FLANGER) x = distortionPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == PITCHSHIFTER) x = pitchShifterPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == COMBFILTER) x = combFilterPanel.getUnchecked(i);
        if(audioProcessor.selectedEffect[i] == REPEATER) x = repeaterPanel.getUnchecked(i);
        
        
        
        x->setBounds(area);
        x->setVisible(true);
        
    }
    
    
    
//    for(auto i =  0; i < numOfLine ; i++ )
//    {
//        area = allArea.removeFromLeft(100);
//        if(audioProcessor.selectedEffect[i] == REVERB)
//           {
//
//            reverbePanel.getUnchecked(i)->setBounds(area);
//           reverbePanel.getUnchecked(i)->setVisible(true);
//           }
//        if(audioProcessor.selectedEffect[i] == DELAY)
//            {
//                delayPanel.getUnchecked(i)->setBounds(area);
//                delayPanel.getUnchecked(i)->setVisible(true);
//
//            }
//        if(audioProcessor.selectedEffect[i] == CHORUS)
//           {
//               chorusPanel.getUnchecked(i)->setBounds(area);
//               chorusPanel.getUnchecked(i)->setVisible(true);
//
//           }
//        if(audioProcessor.selectedEffect[i] == DECIMATOR)
//          {
//              decimatorPanel.getUnchecked(i)->setBounds(area);
//              decimatorPanel.getUnchecked(i)->setVisible(true);
//
//          }
//        if(audioProcessor.selectedEffect[i] == PHASER)
//          {
//              phaserPanel.getUnchecked(i)->setBounds(area);
//              phaserPanel.getUnchecked(i)->setVisible(true);
//
//          }
//
//        if(audioProcessor.selectedEffect[i] == DISTORTION)
//          {
//              distortionPanel.getUnchecked(i)->setBounds(area);
//              distortionPanel.getUnchecked(i)->setVisible(true);
//
//          }
//        if(audioProcessor.selectedEffect[i] == PITCHSHIFTER)
//          {
//              pitchShifterPanel.getUnchecked(i)->setBounds(area);
//              pitchShifterPanel.getUnchecked(i)->setVisible(true);
//
//          }
//
//    }
    
}

void EffectPanel::setFilterPanel(int lineNo)
{
    selectedlineFilterPanel = lineNo;

    resized();
}
