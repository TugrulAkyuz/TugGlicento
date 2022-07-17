/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 12 Jun 2022 8:39:21am
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#pragma once
using namespace juce;
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once


const juce::Colour colourarray [] = {
    juce::Colours::red,
    juce::Colours::lightgreen,
    juce::Colours::yellow,
    juce::Colours::magenta,
    juce::Colours::lightblue,
    juce::Colours::lightblue,
    juce::Colours::lightblue,
    juce::Colours::lightblue
    
};

class IfwLookAndFeel : public LookAndFeel_V4
{
public:
    IfwLookAndFeel() {}
    ~IfwLookAndFeel() {}

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;
};

//==============================================================================
class myLookAndFeelV1 : public LookAndFeel_V4
{
public:
    myLookAndFeelV1();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
    Image img1;

};

//==============================================================================
class myLookAndFeelV2 : public LookAndFeel_V4
{

public:
    myLookAndFeelV2();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    Label* createSliderTextBox (Slider& slider) override
    {
        auto* l = LookAndFeel_V2::createSliderTextBox (slider);

        if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
                                                                                   || slider.getSliderStyle() == Slider::LinearBarVertical))
        {
            l->setColour (Label::textColourId, Colours::orange.withAlpha (0.7f));
        }
        auto f = l->getFont();
        f.setHeight(10);
        l->setFont(f);
        return l;
    }

};

//==============================================================================
class myLookAndFeelV3 : public LookAndFeel_V4
{

public:
    myLookAndFeelV3();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
    Image img2;

};


class KnobLookAndFeel : public LookAndFeel_V4
{
public:
    Image myStrip;
    KnobLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::red);
        myStrip = ImageCache::getFromMemory(BinaryData::untitled222_38_png, BinaryData::untitled222_38_pngSize);
        //  bests : KNIGHT_png
        //        : doc_png  green stabel not good
        //         : mashine_png
        //  MS20_png ehh
        // oo_png antialising !!
        // Pink_png make more brillant
        //  untitled_png  , untitled222_png  more brillant
        // _808_Vol_pngSize 32 is mot enough
        // Blac_Plastic_png
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {


        const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
        const int nFrames = myStrip.getHeight() / myStrip.getWidth(); // number of frames for vertical film strip
        const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius - 1.0f;
        const float ry = centreY - radius /* - 1.0f*/;

        g.drawImage(myStrip, // image
            (int)rx, (int)ry, myStrip.getWidth(), myStrip.getWidth(),   // dest
            0, frameIdx*myStrip.getWidth(), myStrip.getWidth(), myStrip.getWidth()); // source



    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;

        buttonArea.removeFromLeft(edge);
        buttonArea.removeFromTop(edge);

        // shadow
        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRect(buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate(offset, offset);

        g.setColour(backgroundColour);
        g.fillRect(buttonArea);
    }

    void drawButtonText(Graphics& g, TextButton& button, bool, bool isButtonDown) override
    {
        auto font = getTextButtonFont(button, button.getHeight());
        g.setFont(font);
        g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
            : TextButton::textColourOffId)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        auto yIndent = jmin(4, button.proportionOfHeight(0.3f));
        auto cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;

        auto fontHeight = roundToInt(font.getHeight() * 0.6f);
        auto leftIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        auto rightIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        auto textWidth = button.getWidth() - leftIndent - rightIndent;

        auto edge = 4;
        auto offset = isButtonDown ? edge / 2 : 0;

        if (textWidth > 0)
            g.drawFittedText(button.getButtonText(),
                leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                Justification::centred, 2);
    }
    float fontSize = 3;
    Font getLabelFont(Label& label) override
        {
            label.getFont().setHeight(fontSize);
            return label.getFont();
        }
    void setFontSize(float size)
        {
            fontSize = size;
        }

};


class MyLookAndFeel : public juce::LookAndFeel_V4
{
private:
 
    Label* createSliderTextBox (Slider& slider) override
    {
        auto* l = LookAndFeel_V2::createSliderTextBox (slider);

        if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
                                                                                   || slider.getSliderStyle() == Slider::LinearBarVertical))
        {
            l->setColour (Label::textColourId, Colours::orange.withAlpha (0.7f));
        }
        auto f = l->getFont();
        f.setHeight(12);
        l->setFont(f);
        return l;
    }
    void drawRotarySlider(juce::Graphics & g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider & slider) override
    {
    
        auto outline = juce::Colours::grey;
        auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);
        
        auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (5);
        
        auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin (2.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;
        
    
        
        juce::Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);
        
        g.setColour (outline);
        g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    toAngle,
                                    true);
            
            g.setColour (fill);
            g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
        
        auto thumbWidth = lineW * 2.0f;
        juce::Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - 1) * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                                       bounds.getCentreY() + (arcRadius - 1) * std::sin (toAngle - juce::MathConstants<float>::halfPi));
        
        g.setColour (slider.findColour (juce::Slider::thumbColourId));
        // g.fillEllipse (juce::Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(),lineW);
        

        // ...
    }
    Font getComboBoxFont (ComboBox& box) override
    {
        //return getCommonMenuFont();
        return { jmin (12.0f, (float) box.getHeight() * 0.85f) };
    }
    
    Font getPopupMenuFont() override
    {
        return Font (12.0f);
        //return getCommonMenuFont();
        //return { jmin (16.0f, (float) box.getHeight() * 0.85f) };
    }
    void drawComboBox (Graphics& g, int width, int height, bool,
                                       int, int, int, int, ComboBox& box) override
    {
        auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
        Rectangle<int> boxBounds (0, 0, width, height);

        //g.setColour (box.findColour (ComboBox::backgroundColourId));
        g.setColour (Colour(25,25,25));
        g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

        g.setColour (juce::Colours::orange.withAlpha(0.3f));
        g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);

        Rectangle<int> arrowZone (width - 15, 0, 15, height);
        Path path;
        path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
        path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
        path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

        g.setColour (juce::Colours::orange);
        g.strokePath (path, PathStrokeType (2.0f));
    }
    void  positionComboBoxText (ComboBox& box, Label& label) override
    {
        label.setBounds (1, 1,
                         box.getWidth() - 20,
                         box.getHeight() - 2);

        label.setFont (getComboBoxFont (box));
    }

private:
    Font getCommonMenuFont()
    {
        return Font ("Times", "Regular", 10.f);
    }
    void  drawButtonBackground (Graphics& g,
                                               Button& button,
                                               const Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown) override
    {
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

        auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                          .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

        g.setColour (baseColour);

        auto flatOnLeft   = button.isConnectedOnLeft();
        auto flatOnRight  = button.isConnectedOnRight();
        auto flatOnTop    = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();

        if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
        {
            Path path;
            path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                      bounds.getWidth(), bounds.getHeight(),
                                      cornerSize, cornerSize,
                                      ! (flatOnLeft  || flatOnTop),
                                      ! (flatOnRight || flatOnTop),
                                      ! (flatOnLeft  || flatOnBottom),
                                      ! (flatOnRight || flatOnBottom));

            g.fillPath (path);

            g.setColour (button.findColour (ComboBox::outlineColourId));
           // g.setColour (Colours::orange);
            g.strokePath (path, PathStrokeType (1.0f));
        }
        else
        {
            g.fillRoundedRectangle (bounds, cornerSize);

            g.setColour (Colours::orange);
            g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
        }
    }

    
};
class CustomRoratySlider :public juce::Slider{
public:
    CustomRoratySlider()
    {
        
        setLookAndFeel(&myLookAndFeel);
        //        auto rotaryparams = getRotaryParameters();
        //        rotaryparams.startAngleRadians = juce::MathConstants<float>::pi *1.5;
        //        rotaryparams.endAngleRadians = juce::MathConstants<float>::pi *3.0;
        //        setRotaryParameters(rotaryparams);
        setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        //
        setRange(0.0f, 100.0f,1);
        setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 11);
        
        //
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightgreen);
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::lightgreen);
        setColour(Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour(Slider::rotarySliderOutlineColourId, Colours::orange.withAlpha(0.3f));
        
    }
    ~CustomRoratySlider(){
        setLookAndFeel(nullptr);
        
    }
    void setName(String n)
      {
          name = n;
      }
private:
    //juce:

    void paint(juce::Graphics & g) override
    {
        auto sBounds = getLocalBounds();
       
        
        getLookAndFeel().drawRotarySlider(g,
                                          sBounds.getX(),
                                          sBounds.getY(),
                                          sBounds.getWidth(),
                                          sBounds.getHeight(),
                                          juce::jmap(getValue(),getRange().getStart(),getRange().getEnd(),0.0,1.0),
                                          juce::MathConstants<float>::pi *1.25,
                                          juce::MathConstants<float>::pi *2.75,
                                          *this);
        
        g.setFont(11);
      // g.drawFittedText(juce::String(getRange().getStart()), sBounds, juce::Justification::centredLeft, 0.1);
     //  g.drawFittedText(juce::String(getRange().getEnd()), sBounds.removeFromLeft(sBounds.getWidth()/2), juce::Justification::bottomRight, 0.1);
     //   g.drawFittedText(juce::String(getValue()), sBounds, juce::Justification::topRight, 0.1);
   
        g.setColour(Colours::white);
        g.drawFittedText(name, sBounds.removeFromBottom(sBounds.getHeight()/4), juce::Justification::centred, 0.1);
        
        
        
    }
    

   // myLookAndFeelV2 myLookAndFeel;
    IfwLookAndFeel myLookAndFeel;
    //Label name;
    String name = "";
    //KnobLookAndFeel myLookAndFeel;

};

 
