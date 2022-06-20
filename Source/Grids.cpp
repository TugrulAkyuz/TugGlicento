/*
  ==============================================================================

    Grids.cpp
    Created: 12 Jun 2022 8:35:40am
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#include "Grids.h"
#include "EffectsPanel.h"
#include "PluginEditor.h"
 


Grids::Grids(TugGlicentoAudioProcessor& p,int line)  : audioProcessor (p) , stepArrow("",
                                                                                   0.0f,
                                                                                   juce::Colours::orange)
{
    
    addAndMakeVisible(midiInNote);
    addAndMakeVisible(myLineLabel);
    addAndMakeVisible(stepArrow);
    addAndMakeVisible(gridNumberSlider);
    addAndMakeVisible(gridSpeedCombo);
    addAndMakeVisible(gridDurationCombo);
    addAndMakeVisible(gridVolSlider);
    addAndMakeVisible(gridEffectCombo);
    gridNumberSlider.setInterceptsMouseClicks(true, false) ;
    
    addMouseListener(this, true);
    myLine = line;
    step = 0;
    myLineLabel.setText(std::to_string(myLine + 1), juce::NotificationType::dontSendNotification);
    myLineLabel.setColour(juce::Label::ColourIds::textColourId, colourarray[myLine]);
    myLineLabel.setJustificationType(Justification::right);
    
    midiInNote.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
 
    //octaveSlider.gette
 

    gridSpeedCombo.setLookAndFeel(&myLookAndFeel);
    gridSpeedCombo.getLookAndFeel().setColour (ComboBox::textColourId, Colours::orange);
    gridDurationCombo.setLookAndFeel(&myLookAndFeel);
    gridDurationCombo.getLookAndFeel().setColour (ComboBox::textColourId, Colours::orange);
    gridEffectCombo.setLookAndFeel(&myLookAndFeel);
    gridEffectCombo.getLookAndFeel().setColour (ComboBox::textColourId, Colours::orange);

    gridNumberSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    gridVolSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);

    int i= 1;
    for(auto s: myNotetUnit)
    {
        gridSpeedCombo.addItem(s,i);
        i++;
    }

    
     i= 1;
    for(auto s: myNotetUnit)
    {
        gridDurationCombo.addItem(s,i);
        i++;
    }

     i= 1;
    for(auto s: effectChoicesStr)
    {
        gridEffectCombo.addItem(s,i);
        i++;
    }
    
    
    juce::String  tmp_s;
    for (int i = 0; i < numOfStep; ++i)
    {
        addAndMakeVisible (buttons.add (new juce::TextButton ()));
        buttons.getLast()->setClickingTogglesState(true);
        buttons.getLast()->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::grey);
        buttons.getLast()->setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::orange);
        buttons.getLast()->setConnectedEdges(30);
        buttons.getLast()->onClick = [this]()
        {
            int i = 0;
            for(juce::TextButton * b : buttons)
            {
                stepArray[i] = (b->getToggleState());
                i++;
            }
        };
        tmp_s.clear();
        tmp_s << "block" << line << i;
        juce::TextButton *  st = buttons.getLast();
        buttonAttachmentArray.add (new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.valueTreeState, tmp_s,*st));

   
    }

    tmp_s.clear();
    tmp_s << "GridNum"<<line;
    gridNumberSliderAttachment = std::make_unique  <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, gridNumberSlider);
    tmp_s.clear();
    tmp_s << "Speed"<<line;
    comBoxSpeedAtaachment = std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, tmp_s, gridSpeedCombo);
    tmp_s.clear();
    tmp_s << "Dur"<<line;
    comBoxDurationAtaachment =  std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, tmp_s, gridDurationCombo);
    
    tmp_s.clear();
    tmp_s << valueTreeNames[LINEVOL]<<line;
    gridVolSliderAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, gridVolSlider);
    
    
    tmp_s.clear();
    tmp_s << valueTreeNames[EFFECT] << line;
    effectAttachment =  std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, tmp_s, gridEffectCombo);

    

    
    gridNumberSlider.onValueChange = [this]()
    {
        resized();
    };

    startTimer(20);
    gridNumberSlider.setRange(1, numOfStep,1);
    gridVolSlider.setRange(0, 1,0.01f);
    

    gridEffectCombo.onChange = [this]()
    {
        audioProcessor.setEffectType( myLine , gridEffectCombo.getSelectedItemIndex());
        auto lightbox = dynamic_cast<TugGlicentoAudioProcessorEditor*>(getParentComponent());
        if (lightbox)
            lightbox->setLineForFilterPanel(myLine);
       
        
    };
    midiInNote.onClick = [this]()
    {
        auto lightbox = dynamic_cast<TugGlicentoAudioProcessorEditor*>(getParentComponent());
        if (lightbox)
            lightbox->setLineForFilterPanel(myLine);
    };
    
}
void Grids::paint (juce::Graphics& g)
{
   
    g.fillAll (  Colour(0xff101010));
    auto y = getLocalBounds().getHeight();
    auto x = getLocalBounds().getWidth();
    g.setColour(juce::Colours::orange);
    g.drawLine(0, y, x, y, 1);
}
void Grids::resized()
{
    int marjin =  1;
 
    auto area = getLocalBounds();
    gridEffectCombo.setBounds(area.removeFromRight(80).reduced(5)/*.withHeight(area.getHeight()-)*/);
    gridVolSlider.setBounds( area.removeFromRight(50));
    gridDurationCombo.setBounds(area.removeFromRight(70).reduced(5)/*.withHeight(area.getHeight()-10)*/);
    gridSpeedCombo.setBounds(area.removeFromRight(70).reduced(5)/*.withHeight(area.getHeight()-)*/);
    gridNumberSlider.setBounds( area.removeFromRight(50)/*.withHeight(area.getHeight()+5)*/);
    
    myLineLabel.setBounds(area.removeFromLeft(25));
    midiInNote.setBounds(area.removeFromLeft(60).reduced(10));
 
    
    auto griidbounds =  area.reduced(10, 2);
    juce::FlexBox fb;
   fb.flexWrap = juce::FlexBox::Wrap::wrap;

    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.flexWrap= juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
 
    int n = gridNumberSlider.getValue() ;
    auto w = (griidbounds.toFloat().getWidth()   /(n)) ;
    for ( auto *b : buttons) b->setVisible(false);
    stepArrow.setVisible(false);

    for ( int i = 0; i < n;i++)
    {
        if(step != i || step == -1)
        {
        buttons[i]->setVisible(true);
        buttons[i]->setColour(juce::TextButton::ColourIds::buttonColourId, buttonsDefaultColours);
        buttons[i]->setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::orange);
        buttons[i]->setButtonText("");
        fb.items.add (juce::FlexItem (*buttons[i]).withMinWidth (w-2*marjin).withMinHeight ((float) griidbounds.getHeight() -2 ).withMargin(marjin));
        }
        else{
            buttons[i]->setVisible(true);
            buttons[step]->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black.withAlpha(0.90f));
            buttons[step]->setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::cyan.withAlpha(0.90f));
            buttons[step]->setButtonText(">");
            buttons[step]->setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::darkgrey);
            buttons[step]->setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::darkgrey);
            fb.items.add (juce::FlexItem (*buttons[i]).withMinWidth (w-2*marjin).withMinHeight ((float) griidbounds.getHeight() -2 ).withMargin(marjin));
        }
    }
     
    
    fb.performLayout (griidbounds.toFloat());


}


void Grids::mouseDown (const MouseEvent& e) 
{
   // DBG(myLine);
    auto lightbox = dynamic_cast<TugGlicentoAudioProcessorEditor*>(getParentComponent());
    if (lightbox)
        lightbox->setLineForFilterPanel(myLine);
}

