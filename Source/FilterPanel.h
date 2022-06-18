/*
  ==============================================================================

    FilterPanel.h
    Created: 16 Jun 2022 8:55:17am
    Author:  Tuğrul Akyüz

  ==============================================================================
*/
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeels.h"

#pragma once

using namespace juce;


class CurvePanel : public juce::Component , juce::Timer, AudioProcessorParameter::Listener
{
    public :
    int myline;
    CurvePanel(TugGlicentoAudioProcessor& p , int line_no) :   audioProcessor(p)
    {
        Control_1 = {0,0};
        addMouseListener(this, true);
        attack_time = 0;
        decay_time = 1.0f;
        sustain_value = 1.0;
        release_time = 0;;
        myline = line_no;

        
        const auto& params = audioProcessor.getParameters();
    
        
        for( auto param : params )
        {
            auto x = param->getName(1000);
            if(x ==  String (valueTreeNames[ATTACKNAME] + String(line_no))
               || x ==  String (valueTreeNames[DECAYNAME] + String(line_no))
               || x ==  String (valueTreeNames[SUSTAINNAME] + String(line_no))
               || x ==  String (valueTreeNames[RELEASENAME] + String(line_no)))
                param->addListener(this);
        }
           
        
        startTimer(50);
        
    
        
    }
    void parameterValueChanged (int parameterIndex, float newValue) override
    {
        attack_time = *audioProcessor.valueTreeState.getRawParameterValue(String(valueTreeNames[ATTACKNAME])+String(myline));
        decay_time = *audioProcessor.valueTreeState.getRawParameterValue(String(valueTreeNames[DECAYNAME])+String(myline));;
        sustain_value =  *audioProcessor.valueTreeState.getRawParameterValue(String(valueTreeNames[SUSTAINNAME])+String(myline));;
        release_time =  *audioProcessor.valueTreeState.getRawParameterValue(String(valueTreeNames[RELEASENAME])+String(myline));;
        filterChangedAtomic.set(true);
    }
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override { }
    void timerCallback()  override
    {
        if(filterChangedAtomic.compareAndSetBool(false, true))
            repaint();
    }
    float get_t_value(Point<float> P0, Point<float> P1, Point<float> P2, float x)
    {
        float a = P0.x  - 2 * P1.x + P2.x;
        float b = 2 * (P1.x-P0.x);
        float c = P0.x - x;
        if(a==0)
        {
            if(b == 0) return 0;
            return -c/b;
        }
        
        
        float v = b * b - 4 * a * c;
        if (v < 0)
            return 0;
        v = sqrt(v);
        float t;
        t = (-b + v) / (2 * a);
        if (t  > 0)
        {
           
            
            return t;

        }
            
        if (t < 0)
        {
             t = (-b - v) / (2 * a);
            return t;
        }
           
        return 0;
       

    }
    float tug_time = 0;
    
    void paint(juce::Graphics &g) override
    {
        
        auto area = getLocalBounds();
        
        
        
        g.fillAll(juce::Colours::white);
        
        juce::DropShadow ds(juce::Colours::black.withAlpha(0.8f), 2, {2, 2});
        ds.radius = 10;
        ds.offset = { 0, 0 };
        juce::Rectangle<int> r(area);
        
        
        ds.drawForRectangle(g, r);
        g.setColour(juce::Colours::black);
        g.drawRect(r,2);
        
        //g.setColour(juce::Colour(0xff4a4a4a));
        g.setColour(juce::Colour(0x998a8a8a));
        for (int x = 0; x < getWidth(); x += 16*1.618)
        g.drawLine(x, 0, x, getHeight());
        for (int y = 0; y < getHeight(); y += 16)
        g.drawLine(0, y, getWidth(), y);
        
        p.clear();
        juce::PathStrokeType stroke(3, juce::PathStrokeType::JointStyle::curved,
                                    juce::PathStrokeType::EndCapStyle::rounded);
        
        p.startNewSubPath(0, getHeight());
        // p.cubicTo(Control_1, Control_2,juce::Point<float>(getWidth(),getHeight()));
        // p.quadraticTo(Control_1,juce::Point<float>(getWidth(),getHeight()));
        
        //        for (auto x = 0;   x < getWidth() ; x = x + 4)
        //        {
        //            p.lineTo(x, getHeight()/2 + aa*(getHeight()/2)*sin(3.14*x*1.0/ getHeight()));
        //        }
        
        // attack
        int attack_pos  = attack_time*getWidth()/4;
        int decay_pos = attack_pos + decay_time*getWidth()/4;
        int release_pos =  decay_pos + release_time* getWidth()/4 + getWidth()/4;
        int sustain_pos = (1-sustain_value) * 4*getHeight()/5 + getHeight()/5;
        
        g.setColour(juce::Colours::yellow);
        g.drawVerticalLine(attack_pos, getHeight()/5, getHeight());
        g.drawVerticalLine(decay_pos , sustain_pos , getHeight());
        g.drawVerticalLine(decay_pos + getWidth()/4 , sustain_pos ,getHeight());
        
        //p.lineTo(attack_pos,1*getHeight()/5);
        p.quadraticTo(attack_pos/2, getHeight(), attack_pos, 1*getHeight()/5) ;
        float t  = get_t_value(Point<float>(0, getHeight()), Point<float>(attack_pos / 2, getHeight()), Point<float>(attack_pos,  1*getHeight()/5), tug_time);

        int y = (1 - t)* (1 - t) * getHeight() + 2 * t*(1 - t) * getHeight() + t * t * getHeight() / 5;
        //g.drawEllipse(tug_time, y, 10, 10, 2);
        g.drawEllipse(tug_time-2, y-2, 4, 4, 2);

        //p.lineTo(decay_pos,sustain_pos );
        p.quadraticTo((decay_pos + attack_pos)/2, sustain_pos, decay_pos, sustain_pos) ;
        p.lineTo(decay_pos + getWidth()/4, sustain_pos);
        //p.lineTo(release_pos,getHeight() );
        p.quadraticTo((release_pos + decay_pos + getWidth()/4)/2, getHeight(), release_pos, getHeight()) ;
        //p.closeSubPath();
        
        juce::ColourGradient cg(juce::Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 0.8f), getWidth()/2 , 0,
                                juce::Colour::fromFloatRGBA(0.0f, 0.0f, 0.0f, 0.0f), getWidth()/2,  getHeight() , false);
        
        g.setGradientFill(cg);;
        g.fillPath(p);
        
        
        
        //        juce::DropShadow ds(juce::Colours::white.withAlpha(0.85f), 2, {2, 2});
        //        ds.radius = 30;
        //        ds.offset = { 0, 10 };
        //        ds.drawForPath(g, p);
        g.setColour (juce::Colours::orange);
        juce::Rectangle<int> rp (0,0,6,6);
        rp.translate(attack_pos-3,1*getHeight()/5 -3);
        g.drawRect(rp);
        rp =  {0,0,6,6};
        rp.translate(decay_pos -3, sustain_pos -3);
        g.drawRect(rp);
        rp =  {0,0,6,6};
        rp.translate( release_pos -3, getHeight() -3 );
        g.drawRect(rp);
        
        
        
        g.setColour (juce::Colours::yellow);
        g.strokePath(p,stroke);
        g.setColour (juce::Colours::blue);
        
//        g.setColour (juce::Colours::white);
//        juce::Line<float> l(xx,0,xx,getHeight());
//        g.drawLine(l, 2);
        
//        float m = ms*(getWidth()/4)*1.0/5000;
//        float slope = 4*(getHeight()/(attack_pos +0.1))/5;
//        float x = m*t;
//        float y = x*slope;
//
//        float time_in_point =  sqrt (x*x + y*y);
//        if(time_in_point < sqrt(attack_pos*attack_pos + m*m*attack_pos*attack_pos))
//        {
//            juce::Point <float> pt =  p.getPointAlongPath(time_in_point);
//            g.drawEllipse(pt.getX(), pt.getY(), 5, 5, 2);
//        }
//        else
//        {
//            m = 1;
//        }


   
 
        
    }
    void resized() override
    {
       // myAyriRect.setBounds(getLocalBounds());
        
    }
    void mouseDown(const juce::MouseEvent& ev) override
    {
        //        if(Control_1.getDistanceFrom(ev.position) < Control_2.getDistanceFrom(ev.position))
        //            selected_point = 0;
        //        else
        //            selected_point = 1;
        
    }
    void mouseDrag(const juce::MouseEvent& ev) override
    {
        //       if(selected_point == 0)
        Control_1 = ev.position;
        //       else
        //           Control_2 = ev.position;
        
        repaint();
        
    }
    
    void mouseMove(const juce::MouseEvent& ev) override
    {
        
        
        p.getNearestPoint(ev.position,pointOnPath);
        
        pointOnPath2 = p.getPointAlongPath(ev.position.getX());
        
        xx = ev.position.getX();
        
        DBG("X:" << pointOnPath.getX()<<" Y:" << pointOnPath.getY());
        
        repaint();
        
    }
    
    void setAmp(float a)
    {
        aa = a;
        repaint();
    }
    void setADSF(int type, float value)
    {
        switch(type)
        {
            case  ATTACK  :
                attack_time = value;
                break;
            case  DECAY  :
                decay_time = value;
                break;
            case  SUSTAIN  :
                sustain_value =  value;
                break;
            case  RELEASE  :
                release_time =  value;
                break;
        }
        
        repaint();
    }
    juce::Atomic <bool>filterChangedAtomic {false};
    TugGlicentoAudioProcessor& audioProcessor;
    int t;
    float aa;
    juce:: Point<float> Control_1;
    juce:: Point<float> Control_2;
    int selected_point;
    juce::Path p;
    juce::Point<float> pointOnPath;
    juce::Point<float> pointOnPath2;
    int xx;
    
    float attack_time;
    float decay_time;
    float sustain_value;
    float release_time;
    int ms = 50;
  
private:
    
};


class FreqResPanel : public Component, public Timer,juce::AudioProcessorParameter::Listener
{
public:
    FreqResPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~FreqResPanel()
    {
       
    };
    void timerCallback() override
    {
        if(filterChangedAtomic.compareAndSetBool(false, true))
            repaint();
       
    }
    void parameterValueChanged (int parameterIndex, float newValue) override
    {
        filterChangedAtomic.set(true);
    }
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override { }
    void  paint (juce::Graphics& g) override;
    void resized() override;
    juce::Atomic <bool>filterChangedAtomic {false};
private:
    int myLine;
    MyLookAndFeel myLookAndFeel;
    TugGlicentoAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqResPanel)
    
    
};



class FilterPanel : public Component
{
public:
    FilterPanel(TugGlicentoAudioProcessor& p , int line_no);
   
    ~FilterPanel();
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

    FreqResPanel freqResPanel;
    CurvePanel   curvePanel;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> cutofAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> qAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr  <AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterPanel)
};


