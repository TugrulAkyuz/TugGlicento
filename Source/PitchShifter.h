/*
  ==============================================================================

    PitchShifter.h
    Created: 24 Jun 2022 11:44:29am
    Author:  Tuğrul Akyüz

  ==============================================================================
*/


class MyPitchShifterPhasor
{
    public :
    MyPitchShifterPhasor(float sampleRate) : mySampleRate(sampleRate)
    {
        
    };
    ~MyPitchShifterPhasor(){};
    double getPhasorSample(float freq , int w)
    {
        double incr = freq/mySampleRate;
        if(incr == 0) return 0;
        phasor_phase[w] = phasor_phase[w] + incr;
        if(phasor_phase[w]  > 1.0f)  phasor_phase[w]  = phasor_phase[w]  - 1.0f;
        if(phasor_phase[w]  < 0.0f)  phasor_phase[w]  = phasor_phase[w]  + 1.0f;
        return  phasor_phase[w] ;
    }
private:
    double phasor_phase[2] = {0.0f,0.5f};
  //  float delayWindow = 100 ;//ms
    float mySampleRate;
    
};
