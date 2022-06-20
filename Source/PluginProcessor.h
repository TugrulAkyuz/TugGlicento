/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MoogFilter.h"
using namespace juce;
#define numOfStep  32
#define numOfLine  5

#define MAX_DELAY_TIME   5

const Colour backgroundColor  (25,25,25);

const double  syncValues[8]= {
    1.0/32,
    1.0/16,
    1.0/8,
    1.0/4,
    1.0/2,
    2.0/3,
    3.0/4,
    1.0
};


const std::vector <juce::String> myNotetUnit =
{ "1nd","1n", "1nt",
    "2nd","2n","2nt",
    "4nd","4n","4nt",
    "8nd","8n","8nt",
    "16nd","16n","16nt",
    "32nd","32n","32nt",
    "64nd","64n","64nt",
    "128nd","128n","128nt" };

const StringArray myNotetUnitSA  = { "1nd","1n", "1nt",
    "2nd","2n","2nt",
    "4nd","4n","4nt",
    "8nd","8n","8nt",
    "16nd","16n","16nt",
    "32nd","32n","32nt",
    "64nd","64n","64nt",
    "128nd","128n","128nt" };




enum valueTreeNamesEnum
{
    BLOCK,SPEEED,DUR,GRIDNUM,LINEVOL,EFFECT,GLOBALRESTBAR,CUTOFF,Q,ATTACKNAME,DECAYNAME,SUSTAINNAME,RELEASENAME,ENVNAME,FILTERTYPE,
    CHORUSRATE,CHORUSDEPTH,CHORUSDELAY,CHORUSFEEDBACK,CHORUSMIX,REVERBROOMSIZE,REVERBDAMPING,REVERBWETLEVEL,REVERBDRYLEVEL,REVERBWIDTH,
    DELAYDREYWETDELAY,DELAYTIMEDELAY,DELAYTIMEDELAYSYNC,DELAYFEEDBACKDELAY,DELAYSYNC
};
enum processFunctionEnum
{
    REVERB,DELAY,CHORUS,DISTORTION,DECIMATOR,WAVESHAPER,FLANGER,PHASER
};

enum
{
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
    
};
const StringArray filterChoicesStr = {"LowPass","BandPass","HighPass"};
const StringArray effectChoicesStr = {"REVERB","DELAY","CHORUS","DISTORTION","DECIMATOR","WAVESHAPER","FLANGER","PHASER"};

struct filter_coeff_s
{
    float freq;
    float q;
    float gain;
};

const juce::StringArray valueTreeNames =
{
    "block","Speed","Dur","GridNum","LineVol","EFFECT","GlobalRestncBar","CutOff","Q","ATTACKNAME","DECAYNAME","SUSTAINNAME","RELEASENAME","ENVNAME","FILTERTYPE","CHORUSRATE","CHORUSDEPTH","CHORUSDELAY","CHORUSFEEDBACK","CHORUSMIX","REVERBROOMSIZE","REVERBDAMPING","REVERBWETLEVEL","REVERBDRYLEVEL","REVERBWIDTH","DELAYDREYWETDELAY","DELAYTIMEDELAY","DELAYTIMEDELAYSYNC","DELAYFEEDBACKDELAY","DELAYSYNC"};
//==============================================================================
/**
*/
class TugGlicentoAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TugGlicentoAudioProcessor();
    ~TugGlicentoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    int getSteps(int i)
    {
        if (myIsPlaying == false) return -1;
        return steps[i];
    }
    
    void setFilterType(int index , int line_no)
    {
        myFilter[0][line_no].setFilterMode2(index);
        myFilter[1][line_no].setFilterMode2(index);
    }
    
    bool myIsPlaying  = false;
    int steps[numOfLine] = {};
    std::atomic<float> * gridsArr[numOfLine][numOfStep];
    std::atomic<float> *numOfGrid[numOfLine];
    std::atomic<float> * gridsSpeedAtomic[numOfLine];
    std::atomic<float> * gridsDurationAtomic[numOfLine];
    std::atomic<float> *lineVol[numOfLine];
    
    std::atomic<float> *cutOffAtomic[numOfLine];
    std::atomic<float> *qAtomic[numOfLine];
    std::atomic<float> *attackAtomic[numOfLine];
    std::atomic<float> *decayAtomic[numOfLine];
    std::atomic<float> *sustainAtomic[numOfLine];
    std::atomic<float> *releaseAtomic[numOfLine];
    std::atomic<float> *envAtomic[numOfLine];
    std::atomic<float> * filterTypeAtomic[numOfLine];
    std::atomic<float> *globalResyncBar;
    
    std::atomic<float> * chorusRateAtomic[numOfLine];
    std::atomic<float> * chorusdepthSAtomic[numOfLine];
    std::atomic<float> * chorusDelayAtomic[numOfLine];
    std::atomic<float> * chorusFeedbackAtomic[numOfLine];
    std::atomic<float> * chorusMixAtomic[numOfLine];
    
    std::atomic<float> * reverbroomSizeAtomic[numOfLine];
    std::atomic<float> * reverbdampingAtomic[numOfLine];
    std::atomic<float> * reverbwetLevelAtomic[numOfLine];
    std::atomic<float> * reverbdryLevelAtomic[numOfLine];
    std::atomic<float> * reverbwidthAtomic[numOfLine];
    

    std::atomic<float> * dreywetdelayAtomic[numOfLine];
    std::atomic<float> * timedelayAtomic[numOfLine];
    std::atomic<float> * timedelaysyncAtomic[numOfLine];
    std::atomic<float> * feedbackdelayAtomic[numOfLine];
    std::atomic<float> * delaysyncAtomic[numOfLine];
    
    juce::AudioProcessorValueTreeState valueTreeState;
    
    
    void setAdsrUpdate(int line_no)
    {
        adsrParams[line_no].attack = *attackAtomic[line_no];
        adsrParams[line_no].decay = *decayAtomic[line_no];
        adsrParams[line_no].sustain = *sustainAtomic[line_no];
        adsrParams[line_no].release = *releaseAtomic[line_no];
        adsr[line_no].setParameters(adsrParams[line_no]);

    }
    
    
    void setEffectType(int line_no,int fxIndex)
    {
        //int x = line_no;
        selectedEffect[line_no] = fxIndex;
        processFunctions.at(line_no) = myEffecrBankFunctions.at(fxIndex);

    }
    int selectedEffect[numOfLine] = {};
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> bandpassfilter[numOfLine];
    Filter myFilter[2][numOfLine];
private:
    juce::UndoManager undoManager;
    float myBpm;
    int measureSample = 0;
    int measureBar = 0;
    double  mySampleRate = 0;
    int stepResetInterval[numOfLine] = {};
    int stepLoopResetInterval[numOfLine];
    int stepmidStopSampleInterval[numOfLine];
    int stepmidStopSampleCounter[numOfLine] ;
    bool effectState[numOfLine] = {};
 
    int stpSample[numOfLine] = {};
    int stepDurationCounter[numOfLine] = {};
   
 //   typedef void (TugGlicentoAudioProcessor::*ProcessFunc)(juce::AudioBuffer<float>&, juce::MidiBuffer&);
    std::vector<void (TugGlicentoAudioProcessor::* )(juce::AudioBuffer<float>&, juce::MidiBuffer&,int )> myEffecrBankFunctions;
    std::vector<void (TugGlicentoAudioProcessor::* )(juce::AudioBuffer<float>&, juce::MidiBuffer&,int )> processFunctions;
    std::vector<void (TugGlicentoAudioProcessor::* )(juce::AudioBuffer<float>&, juce::MidiBuffer&,int )> processFunctionsRealTime;
    
    
    
    void processBlockDleay (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockReverb (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockChorus (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockFilter (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockDecimator (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockDistortion (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockPhaser (juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockFlanger(juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockPitchShifter(juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;
    void processBlockReapeater(juce::AudioBuffer<float>&, juce::MidiBuffer&,int line_no) ;

    
    std::unique_ptr <juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>> mDelayLine[numOfLine];
    juce::dsp::Chorus<float> chorus[numOfLine];
    
    dsp::Reverb::Parameters params;
    dsp::Reverb leftReverb[numOfLine], rightReverb[numOfLine];

    

    dsp::WaveShaper<float>  waveshape;

    AudioBuffer<float> copyBuffer [numOfLine];
    SmoothedValue<float> lineGainSmooth[numOfLine];
    SmoothedValue<float> lineVolSmooth[numOfLine];
    int debugcounter = 0;

    filter_coeff_s  filter_coeff[numOfLine] = {0};
    
    juce::ADSR adsr[numOfLine];
    juce::ADSR::Parameters adsrParams[numOfLine];
    
    struct DelayVariables_s {
        std::vector <float> mCircularBuffer[2];
        int mCicularBufferWriteHead;
        int mCircularBufferLenght;
        float mDelayTimeinSamples;
        float mDelayRead;
        float mFeedback[2];
        float mDelayTimeSmooth;
        float mDryWet;
    }delayVariables [numOfLine];
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TugGlicentoAudioProcessor)
};

