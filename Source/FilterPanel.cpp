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

void drawHeaderPanel(Graphics &g, Label &l)
{
    int x = 4;
    
    g.setColour (juce::Colours::white);
    g.drawRoundedRectangle(l.getBounds().reduced(x, 2).toFloat(), 1.0f, 0.3f);
    g.setColour (juce::Colours::black.withAlpha(0.1f));
    g.fillRect(l.getBounds().reduced(x+2, 4));
    
}

FilterPanel::FilterPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no),freqResPanel(p,line_no),curvePanel(p,line_no)
{
    addAndMakeVisible(cutofSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySliader);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(envSlider);
    addAndMakeVisible(filterTypeCombo);

    addAndMakeVisible(freqResPanel);
    addAndMakeVisible(curvePanel);
    
    addAndMakeVisible(effectLabel);
    String l;
    l << "FILTER " << myLine + 1;
    effectLabel.setText(l, dontSendNotification);
    effectLabel.setColour(Label::ColourIds::textColourId,colourarray[line_no]);
    effectLabel.setJustificationType(Justification::centred);
    
    cutofSlider.setName("Cutoff");
    qSlider.setName("Q");
    attackSlider.setName("Attack");
    decaySliader.setName("Decay");
    sustainSlider.setName("Sustain");
    envSlider.setName("Env");
    
//    filterTypeCombo.setColour(int colourID, Colour newColour)
//    Colours::orange.withAlpha(0.3f)
    filterTypeCombo.setLookAndFeel(&myLookAndFeel);
    
    
//    cutofSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    qSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    decaySliader.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
//    envSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    
  
//    attackSlider.setSkewFactor(4);
    int i= 1;
   for(auto s: filterChoicesStr)
   {
       filterTypeCombo.addItem(s,i);
       i++;
   }
    filterTypeCombo.onChange = [this]()
    {
        audioProcessor.setFilterType(filterTypeCombo.getSelectedItemIndex(),myLine);
        repaint();
    };
    
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

    tmp_s.clear();
    tmp_s << valueTreeNames[ENVNAME]<<myLine;
    envAttachment =  std::make_unique <AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, tmp_s, envSlider);
    
    tmp_s.clear();
    tmp_s << valueTreeNames[FILTERTYPE]<<myLine;
    fTypeAttachment =  std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, tmp_s, filterTypeCombo);
    
     auto& params = audioProcessor.getParameters();

    
    for( auto param : params )
    {
        auto x = param->getName(1000);
        if(x ==  String (valueTreeNames[ATTACKNAME] + String(myLine))
           || x ==  String (valueTreeNames[DECAYNAME] + String(myLine))
           || x ==  String (valueTreeNames[SUSTAINNAME] + String(myLine))
           || x ==  String (valueTreeNames[RELEASENAME] + String(myLine))
           || x ==  String (valueTreeNames[FILTERTYPE] + String(myLine)))
            param->addListener(this);
    }
 
    cutofSlider.setRange (20, 20000, 2);
    cutofSlider.setSkewFactorFromMidPoint(1000);

}

FilterPanel::~FilterPanel()
{
    auto& params = audioProcessor.getParameters();

    for( auto param : params )
    {
        auto x = param->getName(1000);
        if(x ==  String (valueTreeNames[ATTACKNAME] + String(myLine))
           || x ==  String (valueTreeNames[DECAYNAME] + String(myLine))
           || x ==  String (valueTreeNames[SUSTAINNAME] + String(myLine))
           || x ==  String (valueTreeNames[RELEASENAME] + String(myLine))
           || x ==  String (valueTreeNames[FILTERTYPE] + String(myLine)))
            param->removeListener(this);
    }
    
}
void  FilterPanel::paint (juce::Graphics& g)
{
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (backgroundColor);
    String l = std::to_string(myLine) ;
    
    g.setColour (juce::Colours::orange);
    auto bounds = getLocalBounds().toFloat().reduced(2, 2);
    
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
    
    drawHeaderPanel(g,effectLabel);
    
//    g.setColour (juce::Colours::darkgrey);
//    g.drawRoundedRectangle(effectLabel.getBounds().reduced(0, 5).toFloat(), 1.0f, 1.0f);
//    g.setColour (juce::Colours::darkgrey.withAlpha(0.1f));
//    g.fillRect(effectLabel.getBounds().reduced(0, 4));
    
    
    
    //  g.fillAll ( ColorScheme::getSliderBorderColor());
}

void FilterPanel::resized()
{
    auto allArea =  getLocalBounds();
    effectLabel.setBounds(allArea.removeFromTop(30));
    auto right = allArea.removeFromRight(3*allArea.getWidth()/5);
    right.reduce(10, 0);
    allArea.reduce(10, 0);
 
    
    auto h =  allArea.getHeight()/4;
    auto area = allArea.removeFromTop( h);
    cutofSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2).reduced(3));
    qSlider.setBounds(area.reduced(3));
    area = allArea.removeFromTop( h);
    
    filterTypeCombo.setBounds(area.reduced(0, 13));
    area = allArea.removeFromTop( h);
    
    attackSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2).reduced(3));
    decaySliader.setBounds(area.reduced(3));
    area = allArea.removeFromTop( h);
    sustainSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2).reduced(3));
  //  releaseSlider.setBounds(area);
    envSlider.setBounds(area.removeFromLeft(allArea.getWidth()/2).reduced(3));
    area = allArea.removeFromTop( h);
   
  
    
    freqResPanel.setBounds(right.removeFromTop(2*h).reduced(0, 7));
    curvePanel.setBounds(right.reduced(0, 7));

    
}

FreqResPanel::FreqResPanel(TugGlicentoAudioProcessor& p ,int line_no) : audioProcessor(p) , myLine(line_no)
{
     auto& params = audioProcessor.getParameters();
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
    responseArea.reduce(1, 1);
    auto w =  responseArea.getWidth();
    g.setColour (Colours::black);
    //g.fillRect(responseArea);
    ColourGradient cg(Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 0.2f), getWidth()/2 , 0,
                      Colour::fromFloatRGBA(0.0f, 0.0f, 0.0f, 0.2f), getWidth()/2,  (getHeight() ), true);
    
    g.setGradientFill(cg);
    g.fillAll();
    
    g.setColour (Colours::orange.withAlpha(0.6f));
    g.drawRoundedRectangle(responseArea.toFloat(), 2.0f, 1.0f);

    int grid_x = 10;
    int grid_y = 5;
    float dashPattern[3];
    dashPattern[0] = 4.0;
    dashPattern[1] = 4.0;
    //            dashPattern[2] = 6.0;
    int inc = responseArea.getWidth()/grid_x;
    for(int i = 0 ; i < grid_x ; i++)
    {
        
        Point<float>  start(responseArea.getX() +  i*inc, responseArea.getY() );
        Point<float>  end(responseArea.getX() + i*inc,  responseArea.getBottom() );
       
        g.drawDashedLine(Line<float>(start,end), dashPattern,2, 0.5);
    }
     inc = responseArea.getHeight()/grid_y;
    for(int i = 0 ; i < grid_y ; i++)
    {
            Point<float>  start(responseArea.getX() , responseArea.getY() +  i*inc);
            Point<float>  end(responseArea.getRight() ,  responseArea.getY()+ i*inc);
  
   g.drawDashedLine(Line<float>(start,end), dashPattern,2, 0.5);
        
    }
    
    std::vector <double> mags;
    mags.resize(w);
   // int ftype  =  audioProcessor.myFilter[0][myLine].getFilterMode2();
    for(int i = 0 ; i < w ;i++)
    {
      
        auto freq =  mapToLog10(double(i) / double(w) , 20.0,20000.0 );
        
        //double mag = audioProcessor.bandpassfilter[myLine].state->getMagnitudeForFrequency(freq, sampleRate);
        
        double mag = audioProcessor.myFilter[0][myLine].getFreqResponce(freq);
        mags[i] = Decibels::gainToDecibels(mag);
        //mags[i] = log10(mag);
       
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
    PathStrokeType stroke(2.0f, PathStrokeType::JointStyle::curved, PathStrokeType::EndCapStyle::rounded);
    freqResponse.lineTo(juce::Point<float>(responseArea.getWidth()+10, responseArea.getHeight()));
    g.strokePath(freqResponse,stroke);
    Colour colour;
    colour = Colours::yellow.withAlpha(0.10f);
    DropShadow ds(colour, 1, {0, 1});
    ds.drawForPath(g, freqResponse);
        

}

void FreqResPanel::resized()
{
    
}
