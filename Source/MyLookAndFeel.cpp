/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 21 Jun 2022 2:57:45pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeels.h"


//==============================================================================
myLookAndFeelV1::myLookAndFeelV1()
{
    File knobImageFile1 = File::getSpecialLocation
    (File::SpecialLocationType::userDesktopDirectory).getChildFile("knob1.png");
    img1 = ImageCache::getFromFile(knobImageFile1);
}

//==============================================================================
void myLookAndFeelV1::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}

//==============================================================================
myLookAndFeelV2::myLookAndFeelV2()
{
}

//==============================================================================
void myLookAndFeelV2::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    float innerCircRatio = 0.1;
    
    const float radius = jmin(width / 2, height / 2) *0.85f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    float fwidth = (float)width;
    float fheight = (float)height;
    const float angle = rotaryStartAngle
        + sliderPos
        * (rotaryEndAngle - rotaryStartAngle);

    g.setColour(Colour(0xff39587a));
    Path filledArc;
    filledArc.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, rotaryEndAngle, 0.9);

    g.fillPath(filledArc);

    g.setColour(Colours::lightgreen);
    Path filledArc1;
    filledArc1.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, angle, 0.4);

    g.fillPath(filledArc1);

    Path p;
    const float pointerLength = radius * 0.93f;
    const float pointerThickness = radius * 0.2f;
    p.addRectangle(-pointerThickness * 0.5f, -radius - 1, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(Colour(0xff39587a));
    g.fillPath(p);

    const float dotradius = radius * (float)innerCircRatio;
    const float dotradius2 = rw * (float)innerCircRatio;
    g.setColour(Colour(0xff39587a));
    g.fillEllipse(centreX - (dotradius),
        centreY - (dotradius),
        dotradius2, dotradius2);
}

//==============================================================================
myLookAndFeelV3::myLookAndFeelV3()
{
    File knobImageFile2 = File::getSpecialLocation
    (File::SpecialLocationType::userDesktopDirectory).getChildFile("knob2.png");
    img2 = ImageCache::getFromFile(knobImageFile2);
}

//==============================================================================
void myLookAndFeelV3::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    if (img2.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img2.getHeight() / img2.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img2,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img2.getWidth(),
            img2.getWidth(),
            img2.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}


void IfwLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                       float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                       Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    if (radius > 0.1f)  // was 12.0f)
    {
        if (slider.isEnabled())
            //g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            g.setColour (slider.findColour (Slider::thumbColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));

        //const float thickness = isMouseOver? 0.8f : 0.85f;  //  was 0.7f;
        const float thickness = isMouseOver? 0.6f : 0.65f;

        {
            Path filledArc;
           // filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
            filledArc.addPieSegment (rx, ry, rw, rw, angle -0.1, angle + 0.1, thickness);
            g.fillPath (filledArc);
        }

        {
            /* Draw value text instead of needle
             const float innerRadius = radius * 0.2f;
             Path p;
             p.addTriangle (-innerRadius, 0.0f,
             0.0f, -radius * thickness * 1.1f,
             innerRadius, 0.0f);

             p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

             g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
            */
            //g.setColour(Colours::white);
            String valueText = slider.getTextFromValue(slider.getValue());
            int textWidth  = (int)(((float)width) * 0.55f);
            int textHeight = (int)(((float)height) * 0.25f);
            int textX = (width - textWidth) / 2;
            int textY = (height - textHeight) / 2;

            //g.setColour (slider.findColour (Slider::textBoxBackgroundColourId));
         //   g.setColour (Colour(0x40000000));
            g.setColour (Colour(0x40000000));
            g.fillEllipse(x, y, width, height);
            g.setFont (Font (slider.getTextBoxHeight(), Font::plain).withTypefaceStyle ("Regular"));
            g.setColour (slider.findColour (Slider::textBoxTextColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            g.drawText(valueText, textX, textY, textWidth, textHeight, Justification::centred);
        }

        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        else
            g.setColour (Colour (0x80808080));

        Path outlineArc;
        outlineArc.addArc(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
      //  outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
       // outlineArc.closeSubPath();

        g.strokePath (outlineArc, PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 2.2f) : 0.3f));
        //auto lineW = jmin (8.0f, radius * 0.5f);
        //g.strokePath (outlineArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
    else
    {
        if (slider.isEnabled())
            //g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            g.setColour (slider.findColour (Slider::thumbColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));

        Path p;
        p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
        PathStrokeType (rw * 0.1f).createStrokedPath (p, p);

        p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);

        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }

}
