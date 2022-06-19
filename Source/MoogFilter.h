/*
  ==============================================================================

    SourceCode.h
    Created: 18 Jun 2022 11:16:33pm
    Author:  Tuğrul Akyüz

  ==============================================================================
*/

#pragma once

#pragma once

#ifndef __Synthesis__Filter__
#define __Synthesis__Filter__

#include <cmath>
 

class Filter {
public:
    enum FilterMode {
        FILTER_MODE_LOWPASS = 0,
        FILTER_MODE_BANDPASS,
        FILTER_MODE_HIGHPASS,
        kNumFilterModes
    };
    Filter() :
    mycutoff(0.99),
    resonance(0.3),
    cutoffMod(0.0),
    mode(FILTER_MODE_LOWPASS),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0)
    {
 
        calculateFeedbackAmount();
    };
    double process(double inputValue);
    inline void setCutoff(double newCutoff) {
 
         //newCutoff =  pow(10, 2*newCutoff) / 100;
        if(newCutoff > 0.001)
            mycutoff = newCutoff;
        else
            newCutoff = 0.001;
        calculateFeedbackAmount();
       
    };
     void setResonance(double newResonance) {
         resonance = newResonance;
         calculateFeedbackAmount();
       
    };
     void setFilterMode(FilterMode newMode) { mode = newMode; }
      void setFilterMode2(int newMode) { mode = newMode; }
     void setCutoffMod(double newCutoffMod) {
       // if(cutoffMod == 0)
        cutoffMod = newCutoffMod;
        calculateFeedbackAmount();
    }
    float getFreqResponce(float freq)
    {
        freq = freq/22000;
        freq =  freq/mycutoff;
        switch (mode) {
            case FILTER_MODE_LOWPASS:
                return calculateFreqRespoce(freq);
            case FILTER_MODE_HIGHPASS:
                return calculateFreqRespoce(1.0/freq);
            case FILTER_MODE_BANDPASS:
                return sqrt(calculateFreqRespoce(freq) * calculateFreqRespoce(1.0/freq));
                break;
            default:
                return 0.0;
        }
        
        return 0.0;

    };
    float calculateFreqRespoce(float freq)
    {
        float tmp = 1 - freq*freq; //(1-F^2)^2
        float first_tmp = 4*resonance + tmp*tmp -4*freq*freq;
        float second_tmp =  4*freq*tmp;
        float result = first_tmp*first_tmp + second_tmp*second_tmp;
        
        result =  sqrt(1.0f/result);
        return result;
        
    }
    int getFilterMode2()
    {
        return mode;
    }
    
private:
    double mycutoff;
    double resonance;
    double cutoffMod;
    int mode;
    double feedbackAmount;
    inline void calculateFeedbackAmount() {
        feedbackAmount = resonance + resonance/(1.0 - getCalculatedCutoff());
      //  calculate_coefficient();
    }
    
    double buf0;
    double buf1;
    double buf2;
    double buf3;
    

    
     double getCalculatedCutoff() const {
        return fmax(fmin(mycutoff + cutoffMod, 0.99), 0.01);
    };
//    void calculate_coefficient()
//    {
//
//        float res = resonance*10;
//          auto w = M_PI*mycutoff;
//        float K = tan(w/2);
//        float W = K*K;
//        auto alpha = 1 + K/res +W;
//
//        a0 = W/alpha;
//        a1 = 2*W/alpha;
//        a2 = a0;
//
//        float b0 = 1;
//        b1 = 2*(W-1)/alpha;
//        b2 =(1-K/res+W)/alpha;
//
//    }
    float a0 = 0  ;
    float a1  = 0;
    float a2 = 0 ;
    float b1 = 0 ;
    float b2 = 0;
    
    double inbuff0 = 0;
    double inbuff1 = 0;
    double inbuff2 = 0;
    double outbuff0 = 0;
    double outbuff1 = 0;
    double outbuff2 = 0;
    
    
};

#endif /* defined(__Synthesis__Filter__) */
