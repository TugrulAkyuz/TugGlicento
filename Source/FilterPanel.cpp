/*
 ==============================================================================
 
 FilterPanel.cpp
 Created: 16 Jun 2022 8:55:17am
 Author:  Tuğrul Akyüz
 
 ==============================================================================
 */

#include "FilterPanel.h"

using namespace juce;
//namespace ColorScheme
//{
//    inline juce::Colour getSliderBorderColor()
//    {
//        return colorHelper(juce::Colours::blue);
//    }
//}

FilterPanel::FilterPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no),freqResPanel(p,line_no),curvePanel(p,line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    
    addAndMakeVisible(freqResPanel);
    addAndMakeVisible(curvePanel);
    
    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    
    juce::String  tmp_s;
    tmp_s.clear();
    tmp_s << valueTreeNames[CUTOFF]<<myLine;
    cutofAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, cutofSlider);
    
    tmp_s.clear();
    tmp_s << valueTreeNames[Q]<<myLine;
    qAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, qSlider);
 
    

    tmp_s.clear();
    tmp_s << valueTreeNames[ATTACKNAME]<<myLine;
    attackAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, attackSlider);
    
    tmp_s.clear();
    tmp_s << valueTreeNames[DECAYNAME]<<myLine;
    decayAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, decaySliader);

    tmp_s.clear();
    tmp_s << valueTreeNames[SUSTAINNAME]<<myLine;
    sustainAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, sustainSlider);
    
    tmp_s.clear();
    tmp_s << valueTreeNames[RELEASENAME]<<myLine;
    releaseAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, releaseSlider);

    
}

FilterPanel::~FilterPanel()
{
    
}
void  FilterPanel::paint (juce::Graphics& g)
{
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (Colours::black);
    String l = std::to_string(myLine) ;
    
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
    
    
    
    //  g.fillAll ( ColorScheme::getSliderBorderColor());
}





void FilterPanel::resized()
{
    auto allArea =  getLocalBounds();
    allArea.removeFromTop(20);
    auto right = allArea.removeFromRight(allArea.getWidth()/2);
    right.reduce(10, 10);
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
    
    
    freqResPanel.setBounds(right.removeFromTop(2*h));
    curvePanel.setBounds(right);
    
}

FreqResPanel::FreqResPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
    const auto& params = audioProcessor.getParameters();
    String n;
    n << valueTreeNames[CUTOFF] << myLine;
    
    for( auto param : params )
    {
        auto x = param->getName(1000);
        if(x ==  String (valueTreeNames[CUTOFF] + String(myLine))
           || x ==  String (valueTreeNames[Q] + String(myLine)))
            param->addListener(this);
    }
       
    
    startTimer(50);
    
}



void  FreqResPanel::paint (juce::Graphics& g)
{
    auto sampleRate = audioProcessor.getSampleRate();
    auto   responseArea =   getLocalBounds();
    auto w =  getLocalBounds().getWidth();
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(responseArea.toFloat(), 2.0f, 1.0f);
    int grid_x = 10;
    int grid_y = 5;
    float dashPattern[3];
    dashPattern[0] = 4.0;
    dashPattern[1] = 4.0;
    //            dashPattern[2] = 6.0;
    
    for(int i = 0 ; i < getWidth()/grid_x ; i++)
    {
        g.drawDashedLine(Line<float>(i*getWidth()/grid_x, 0, i*getWidth()/grid_x ,getHeight()), dashPattern,2, 0.5);
    }
    for(int i = 0 ; i < getHeight()/grid_y ; i++)
    {
        g.drawDashedLine(Line<float>(0,  i*getHeight()/grid_y, getWidth() , i*getHeight()/grid_y), dashPattern,2, 0.5);
        
    }
    
    std::vector <double> mags;
    mags.resize(w);
    for(int i = 0 ; i < w ;i++)
    {
      
        auto freq =  mapToLog10(double(i) / double(w) , 20.0,20000.0 );
        
        double mag = audioProcessor.bandpassfilter[myLine].state->getMagnitudeForFrequency(freq, sampleRate);
        mags[i] = Decibels::gainToDecibels(mag);
       
    }
    double outMin = responseArea.getBottom();
    double outMMax = responseArea.getY();
    Path freqResponse;
    
    g.setColour(Colours::yellow);
    
    
    auto map = [outMin,outMMax](double input)
    {
        return jmap(input, -24.0, 24.0,outMin,outMMax);
    };
    double m =  map(mags[0]);
    if(m < outMin)
        freqResponse.startNewSubPath(- 20,outMin);
    else  freqResponse.startNewSubPath(juce::Point<float>(0,m ));
    
    for(int i = 0 ; i < w ;i++)
    {
        double m =  map(mags[i]);
        freqResponse.lineTo(responseArea.getX() + i,m);
    }
    freqResponse.lineTo(juce::Point<float>(getWidth()+10, getHeight()));
    
    g.strokePath(freqResponse, PathStrokeType(2.0f));
    Colour colour;
    colour = Colours::yellow.withAlpha(0.10f);
    DropShadow ds(colour, 1, {0, 1});
    ds.drawForPath(g, freqResponse);
        
   
       
}

void FreqResPanel::resized()
{
    
}
