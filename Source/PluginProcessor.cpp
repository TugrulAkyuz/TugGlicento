/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "Grids.h"
#include "EffectsPanel.h"
#include "PluginEditor.h"

double linearInterpol(float v0, float v1, float t)
{
    
    return (1 - t) * v0 + t * v1;
}

//==============================================================================
TugGlicentoAudioProcessor::TugGlicentoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),
valueTreeState(*this, &undoManager)
#endif
{
    juce::String  tmp_s;
    for(int j = 0 ; j <  numOfLine; j++)
    {
        for(int i = 0 ; i < numOfStep ; i++)
        {
            juce::String  grid_block;
            grid_block <<valueTreeNames[BLOCK]<< j << i;
            valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterBool>(grid_block, grid_block,false));
            
            gridsArr[j][i] = valueTreeState.getRawParameterValue(grid_block);
            
        }
        tmp_s.clear();
        tmp_s << valueTreeNames[SPEEED] << j;
        //myNotetUnitSA
        
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s,tmp_s,myNotetUnitSA,13));
        gridsSpeedAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        tmp_s.clear();
        tmp_s << valueTreeNames[DUR] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s,tmp_s,myNotetUnitSA,13));
        gridsDurationAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        tmp_s.clear();
        tmp_s << valueTreeNames[GRIDNUM] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterInt>(tmp_s, tmp_s,1,32,16));
        numOfGrid[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[LINEVOL] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0,1.0f,0.9f));
        lineVol[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        
        tmp_s.clear();
        tmp_s << valueTreeNames[EFFECT] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s, tmp_s,effectChoicesStr,1));

        
        tmp_s.clear();
        tmp_s << valueTreeNames[CUTOFF] << j;
        //valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,20,20000.0f,200));
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s, NormalisableRange<float>(20,20000.0f,1.0f,0.25),200));
        cutOffAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[Q] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.01,0.99,0.2));
        qAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
    
        
        tmp_s.clear();
        tmp_s << valueTreeNames[ATTACKNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.001,5,0.001));
        attackAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[DECAYNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.01,5,1));
        decayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[SUSTAINNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.001,1,0.9f));
        sustainAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[RELEASENAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.1,5,0.1));
        releaseAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[ENVNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,0.9,0.1));
        envAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[FILTERTYPE]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s, tmp_s,filterChoicesStr,1));
        filterTypeAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
 
        tmp_s.clear();
        tmp_s << valueTreeNames[CHORUSRATE]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        chorusRateAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[CHORUSDEPTH]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        chorusdepthSAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[CHORUSDELAY]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        chorusDelayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[CHORUSFEEDBACK]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        chorusFeedbackAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
       
        tmp_s.clear();
        tmp_s << valueTreeNames[CHORUSMIX]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        chorusMixAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
   
 
         tmp_s.clear();
         tmp_s << valueTreeNames[REVERBROOMSIZE]<<j;
         valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        reverbroomSizeAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
    
         tmp_s.clear();
         tmp_s << valueTreeNames[REVERBDAMPING]<<j;
         valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        reverbdampingAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
         tmp_s.clear();
         tmp_s << valueTreeNames[REVERBWETLEVEL]<<j;
         valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        reverbwetLevelAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        
         tmp_s.clear();
         tmp_s << valueTreeNames[REVERBDRYLEVEL]<<j;
         valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        reverbdryLevelAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        
         tmp_s.clear();
         tmp_s << valueTreeNames[REVERBWIDTH]<<j;
         valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        reverbwidthAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
      //DELAY

        
        tmp_s.clear();
        tmp_s << valueTreeNames[DELAYDREYWETDELAY]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        dreywetdelayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
   
        tmp_s.clear();
        tmp_s << valueTreeNames[DELAYTIMEDELAY]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        timedelayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
       
        tmp_s.clear();
        tmp_s << valueTreeNames[DELAYTIMEDELAYSYNC]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        timedelaysyncAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
       
       
        tmp_s.clear();
        tmp_s << valueTreeNames[DELAYFEEDBACKDELAY]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        feedbackdelayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
       
       
        tmp_s.clear();
        tmp_s << valueTreeNames[DELAYSYNC]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        delaysyncAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
    
        
        tmp_s.clear();
        tmp_s << valueTreeNames[PHASERDEPTH]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        phaserDepthAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[PHASERPEEDBAC]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,-1.0,1.0,0.1));
        phaserPeedbacAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
       
        tmp_s.clear();
        tmp_s << valueTreeNames[PHASERMIX]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1.0,0.1));
        phaserMixAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[PHASERDECAY]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,100.0,1.0));
        phaserDecayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[PHASERRATE]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,100.0,3));
        phaserRateAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        
  
        tmp_s.clear();
        tmp_s << valueTreeNames[DISTMODE]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s, tmp_s,distChoicesStr,1));
        distModeAtomic[j]  = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[DISTDRIVE]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,25,1.0));
        distDriveAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[DISTMIX]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1,3));
        distMixAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[DISTTRESHOLD]<<j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.0,1,3));
        distthresholdAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        // PitchShifter


        
 
         
        
//        
//        tmp_s.clear();
//        tmp_s << valueTreeNames[DENEME]<<j;
//        deneme[j] = new juce::AudioParameterInt(tmp_s,tmp_s, 0, 3, 0);
//        addParameter(deneme[j]);
//        
//        
// 
 


     
 
        
    }
    
    tmp_s.clear();
    tmp_s << valueTreeNames[GLOBALRESTBAR];
    valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterInt>(tmp_s, tmp_s,1,32,1));
    globalResyncBar = valueTreeState.getRawParameterValue(tmp_s);
    

    
    
    valueTreeState.state = juce::ValueTree("TugGlicento");
    memset(stepmidStopSampleInterval, -1, sizeof(stepmidStopSampleInterval));
    memset(stepmidStopSampleCounter, -1, sizeof(stepmidStopSampleCounter));
    
    // auto x =  processBlockDleay;
//    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDleay);
//    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockReverb);
//    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
//    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    
    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    processFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    
     processFunctionsRealTime =  processFunctions;

     
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockReverb);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDleay);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockChorus);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDecimator);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDistortion);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockPhaser);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockFlanger);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockPitchShifter);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockReapeater);
    waveshape.functionToUse = [] (float x)
    {
         return std::sin (x);
    };
    
}

TugGlicentoAudioProcessor::~TugGlicentoAudioProcessor()
{
}

//==============================================================================
const juce::String TugGlicentoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TugGlicentoAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TugGlicentoAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TugGlicentoAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double TugGlicentoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TugGlicentoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TugGlicentoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TugGlicentoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TugGlicentoAudioProcessor::getProgramName (int index)
{
    return {};
}

void TugGlicentoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TugGlicentoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mySampleRate = sampleRate;
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;  //dsp module parameter
    spec.numChannels = getTotalNumOutputChannels();

    for(auto i = 0 ; i < numOfLine ; i++)
    {
        copyBuffer[i].setSize(2, samplesPerBlock);
        lineGainSmooth[i].reset (sampleRate,1.0/20);
        lineVolSmooth[i].reset(sampleRate,1.0/4);
        
        bandpassfilter[i].prepare(spec);
        bandpassfilter[i].reset();
        mDelayLine[i] = std::make_unique< juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear > > ( MAX_DELAY_TIME*  sampleRate);
        mDelayLine[i]->reset();
        mDelayLine[i]->prepare(spec);
        delayVariables[i].mCircularBufferLenght =sampleRate*MAX_DELAY_TIME;
        delayVariables[i].mCicularBufferWriteHead = 0;
        delayVariables[i].mCircularBuffer[0].resize(delayVariables[i].mCircularBufferLenght,0);
        delayVariables[i].mCircularBuffer[1].resize(delayVariables[i].mCircularBufferLenght,0);
        
        filter_coeff[i].freq = 200*pow(2,i);
        filter_coeff[i].q = 0.5;
        *bandpassfilter[i].state = *dsp::IIR::Coefficients<float>::makeBandPass(mySampleRate,  filter_coeff[i].freq,filter_coeff[i].q);
        
        adsr[i].setSampleRate(sampleRate);
        chorus[i].prepare (spec);
        chorus[i].reset();
        phaser[i].prepare (spec);
        phaser[i].reset();
        
        for(auto channel = 0 ; channel < 2 ; channel++)
        {
            delayVariables[i].mCircularBuffer[channel].resize(delayVariables[i].mCircularBufferLenght,0);
        }
        delayVariables[i].mDelayTimeSmooth = 0;
        delayVariables[i].mCicularBufferWriteHead = 0;
        delayVariables[i].mCircularBufferLenght = 0;
        delayVariables[i].mDelayTimeinSamples = 0;
        delayVariables[i].mDryWet = 0.5;
        delayVariables[i].mDelayRead = 0;
        distProcessor[i] = new Distortion();
        
    }
    
    pitchshiftVariables.mCircularBufferLenght =sampleRate;
    pitchshiftVariables.mCicularBufferWriteHead = 0;
    for(auto channel = 0 ; channel < 2 ; channel++)
    {
        pitchshiftVariables.mCircularBuffer[channel].resize(pitchshiftVariables.mCircularBufferLenght,0);

    }
    
    
    waveshape.prepare(spec);
    waveshape.reset();
    
    
}

void TugGlicentoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TugGlicentoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void TugGlicentoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());
    
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for(int i =  0; i  < numOfLine ; i++)
    {

        filter_coeff[i].freq = *cutOffAtomic[i];
        filter_coeff[i].q =  *qAtomic[i];
        *bandpassfilter[i].state = *dsp::IIR::Coefficients<float>::makeBandPass(mySampleRate,  filter_coeff[i].freq,filter_coeff[i].q);
        myFilter[0][i].setCutoff(*cutOffAtomic[i]/20000);
        myFilter[0][i].setResonance(*qAtomic[i]);
        myFilter[1][i].setCutoff(*cutOffAtomic[i]/20000);
        myFilter[1][i].setResonance(*qAtomic[i]);
        
        
    }
    
    juce::AudioPlayHead::CurrentPositionInfo positionInfo;
    juce::AudioPlayHead* playHead = getPlayHead();
    if (playHead == nullptr) return;
    playHead->getCurrentPosition(positionInfo);
    int samplePos;
    if (positionInfo.bpm == 0) return;
    
    double mBpm =  positionInfo.bpm;
    double mBps = (float)mBpm/60;
    myBpm = mBpm;
    for(int i = 0 ; i< numOfLine ;i++)
    {
        double first = 1.5*4*(60*mySampleRate/ mBpm); // first value in combos  number of sample musical durations and speeds
        
        int index = *gridsSpeedAtomic[i] ;
        
        if(index%3 == 0) {  index = (index+1) / 3;}
        else if((index -1)%3 == 0) { index = (index) / 3;first = 2*first/3;}
        else if((index -2)%3 == 0) { index = (index-1) / 3;first = 4*first/9;}
        stepResetInterval[i] = first / pow(2,index); // dviding  "first" you get number of sample  for musical note time values
        
        stepLoopResetInterval[i] = stepResetInterval[i]**numOfGrid[i];
        
        first = 1.5*4*(60*mySampleRate/ mBpm);
        index = *gridsDurationAtomic[i];
        
        if(index%3 == 0) {  index = (index+1) / 3;}
        else if((index -1)%3 == 0) { index = (index) / 3;first = 2*first/3;}
        else if((index -2)%3 == 0) { index = (index-1) / 3;first = 4*first/9;}
        
        stepmidStopSampleInterval[i] = first / pow(2,index);
        
        lineVolSmooth[i].setTargetValue(*lineVol[i]);
    }
    if (myIsPlaying == false &&  positionInfo.isPlaying == true ) // stop to start
    {
        measureBar = *globalResyncBar-1;  // resync var number
        measureSample = (int)(4*mySampleRate/mBps)-1; // mBps Beat per second  ---> 1 bar  numof sample
    }
    myIsPlaying = positionInfo.isPlaying;
    
    float *cb_ptr[numOfLine][2];
    float *buf_ptr[2];
    for(int i = 0 ; i< numOfLine ;i++)
    for(int j = 0 ; j< 2 ;j++)
    cb_ptr[i][j] = copyBuffer[i].getWritePointer(j);
    for(int j = 0 ; j< 2 ;j++)
    buf_ptr[j] = buffer.getWritePointer(j);
    
    for(int s = 0 ; s < buffer.getNumSamples();  s++)/**ppq ye bakma code*/
    {
        
        for(int i = 0 ; i< numOfLine ;i++)
        for(int j = 0 ; j< 2 ;j++)
        *cb_ptr[i][j] =  *buf_ptr[j];
        
        
        measureSample++;
        measureSample %= (int)(4*mySampleRate/mBps);
        if(measureSample == 0)
        {
            measureBar++;
            measureBar %= (int)(*globalResyncBar);
            if(measureBar == 0)
            {
                for(int i =  0; i  < numOfLine ; i++)
                {
                    steps[i] = (int)(*numOfGrid[i]) -1;
                    
                    stpSample[i] = stepResetInterval[i] -1;
                }
                
            }
        }
        for(int i =  0; i  < numOfLine ; i++)
        {
            
            stpSample[i]++;
            stpSample[i] %=stepResetInterval[i];
            if(stepmidStopSampleCounter[i] != -1)
            {
                stepmidStopSampleCounter[i]++;
                stepmidStopSampleCounter[i] %= stepmidStopSampleInterval[i]; // byrada uçuyor bir bak
            }
            if( stepmidStopSampleCounter[i]== 0)
            {
                
                stepmidStopSampleCounter[i] = -1;
                effectState[i] = false;
                lineGainSmooth[i].setTargetValue(0.0f);
                adsr[i].noteOff();
            }
            if(stpSample[i] == 0)
            {
                
                steps[i]++;
                steps[i] %= (int)(*numOfGrid[i]);
                
                if(*gridsArr[i][steps[i]] == 1)
                {
                    stepmidStopSampleCounter[i] = 1;
                    effectState[i] = true;
                    lineGainSmooth[i].setTargetValue(1.0f);
                    adsr[i].noteOn();
                }
                
            }
            
        }
        for(int j = 0 ; j< 2 ;j++)
        {
           for(int i = 0 ; i< numOfLine ;i++)
            {
      
                *cb_ptr[i][j] = * buf_ptr[j]*lineGainSmooth[i].getNextValue();
                
                cb_ptr[i][j]++;
            }
            
            buf_ptr[j]++;
        }
       
       
       
       
    }
    for(int i =  0; i  < numOfLine ; i++)
    {

        processBlockFilter (buffer,  midiMessages, i);
    }
    
    int i = 0;
    for(auto f : processFunctions)
    {
        processFunctionsRealTime.at(i) = processFunctions.at(i);
        i++;
    }
    i = 0;
    for(auto f : processFunctions)
    {
    
        (this->*(f))(buffer,midiMessages,i);
        i++;
    }
    

        buffer.clear();
   
//    for(auto i = 0 ; i < numOfLine ; i++)
//    for (auto channel = 0; channel < copyBuffer[i].getNumChannels(); channel++)
//    {
//
//        buffer.addFrom(channel, 0, copyBuffer[i], channel, 0, buffer.getNumSamples());
//
//    }
    
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelDatato = buffer.getWritePointer (channel);
        for(auto l = 0 ; l < numOfLine ; l++)
        {
            float* channelDatafrom = copyBuffer[l].getWritePointer (channel);
        
            for (int i = 0; i < copyBuffer[l].getNumSamples(); ++i) {
                channelDatato[i] += channelDatafrom[i]*lineVolSmooth[l].getNextValue()/4;
            }
        }
    }
    
    // (this->*(processFunctions[0]))(buffer,midiMessages);
    
}

//==============================================================================
bool TugGlicentoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TugGlicentoAudioProcessor::createEditor()
{
    return new TugGlicentoAudioProcessorEditor (*this);
}

//==============================================================================
void TugGlicentoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TugGlicentoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TugGlicentoAudioProcessor();
}
void TugGlicentoAudioProcessor::processBlockDleay (juce::AudioBuffer<float>& buffr, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDleay");
    float * buf[2];
    buf[0] = copyBuffer[line_no].getWritePointer(0);
    buf[1] = copyBuffer[line_no].getWritePointer(1);
    float delayTime;
    
    //buffer.get
    // mDelayLine.popSample(int channel);
    
    //DBG(*parameters.oscGenValues[0][0]);
    
    if(*delaysyncAtomic[line_no] == false)
    {
        delayTime =  (*timedelayAtomic[line_no]);
    }
    else
    {
        delayTime =  4* syncValues[(int)*timedelaysyncAtomic[line_no]] /(myBpm/60);
        
    }


        for(int i = 0 ; i < copyBuffer[line_no].getNumSamples(); i++)
        {
            delayVariables[line_no].mDelayTimeSmooth = delayVariables[line_no].mDelayTimeSmooth - 0.001*(delayVariables[line_no].mDelayTimeSmooth - delayTime);
            delayVariables[line_no].mDelayTimeinSamples = getSampleRate()* delayVariables[line_no].mDelayTimeSmooth;

            
            for(int channel = 0; channel < 2 ; channel++)
            {


            mDelayLine[line_no]->pushSample( channel, *feedbackdelayAtomic[line_no] * (copyBuffer[line_no].getReadPointer(channel)[i] + delayVariables[line_no].mFeedback[channel]));
            auto d =  mDelayLine[line_no]->popSample(channel, delayVariables[line_no].mDelayTimeinSamples);
            delayVariables[line_no].mFeedback[channel] = d;
            copyBuffer[line_no].getWritePointer(channel)[i] = copyBuffer[line_no].getReadPointer(channel)[i]*(1 - *dreywetdelayAtomic[line_no]) + *dreywetdelayAtomic[line_no]*d;
        }

    }
    
}
void TugGlicentoAudioProcessor::processBlockReverb (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages ,int line_no)
{
    DBG("processBlockReverb");
    
 
    params.dryLevel = *reverbdryLevelAtomic[line_no];
    params.damping = *reverbdampingAtomic[line_no];
    params.roomSize = *reverbroomSizeAtomic[line_no];
    params.wetLevel = *reverbwetLevelAtomic[line_no];
    params.width = *reverbwidthAtomic[line_no];
    
    leftReverb[line_no].setParameters (params);
    rightReverb[line_no].setParameters (params);

    
    juce::dsp::AudioBlock<float> block (copyBuffer[line_no]);
    
    auto leftBlock = block.getSingleChannelBlock (0);
    auto rightBlock = block.getSingleChannelBlock (1);
    
    juce::dsp::ProcessContextReplacing<float> leftContext (leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext (rightBlock);
    
    leftReverb[line_no].process (leftContext);
    rightReverb[line_no].process (rightContext);
    
 
}
void TugGlicentoAudioProcessor::processBlockChorus (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockChorus");
    
    chorus[line_no].setRate (*chorusRateAtomic[line_no]);
    chorus[line_no].setDepth (*chorusdepthSAtomic[line_no]);
    chorus[line_no].setCentreDelay (*chorusDelayAtomic[line_no]);
    chorus[line_no].setFeedback (*chorusFeedbackAtomic[line_no]);
    chorus[line_no].setMix (*chorusMixAtomic[line_no]);
    
    juce::dsp::AudioBlock<float> sampleBlock (copyBuffer[line_no]);
    chorus[line_no].process (juce::dsp::ProcessContextReplacing<float> (sampleBlock));
}
void TugGlicentoAudioProcessor::processBlockDecimator (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDecimator");
}
void TugGlicentoAudioProcessor::processBlockDistortion (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
    

    
    distProcessor[line_no]->controls.drive = * distDriveAtomic[line_no];
    distProcessor[line_no]->controls.mode =  * distModeAtomic[line_no];
    distProcessor[line_no]->controls.threshold =  * distthresholdAtomic[line_no];
    distProcessor[line_no]->controls.mix =   * distMixAtomic[line_no];
    
    for (int channel = 0; channel < getNumInputChannels(); ++channel) {
        float* channelData = copyBuffer[line_no].getWritePointer (channel);

        for (int i = 0; i < copyBuffer[line_no].getNumSamples(); ++i) {
            channelData[i] = distProcessor[line_no]->processSample(channelData[i]);
        }
    }
}
void TugGlicentoAudioProcessor::processBlockPhaser(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
    phaser[line_no].setRate (*phaserRateAtomic[line_no]);
    phaser[line_no].setDepth (*phaserDepthAtomic[line_no]);
    phaser[line_no].setMix(*phaserMixAtomic[line_no]);
    phaser[line_no].setFeedback (*phaserPeedbacAtomic[line_no]);
    phaser[line_no].setCentreFrequency(*phaserDecayAtomic[line_no]);
    
    juce::dsp::AudioBlock<float> sampleBlock (copyBuffer[line_no]);
    phaser[line_no].process (juce::dsp::ProcessContextReplacing<float> (sampleBlock));
    

    
}

void TugGlicentoAudioProcessor::processBlockFlanger(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
}
void TugGlicentoAudioProcessor::processBlockPitchShifter(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{

   
    auto r =  log(2);
    float pitch_value = 0.5;
    int block_len = 8;

    

        
        for (auto i = 0; i < buffer.getNumSamples(); ++i)
        {
            for (int channel = 0; channel < getNumInputChannels(); ++channel)
                pitchshiftVariables.mCircularBuffer[channel].at(pitchshiftVariables.mCicularBufferWriteHead) =  buffer.getSample(channel, i);
            pitchshiftVariables.mCicularBufferWriteHead++;
            pitchshiftVariables.mCicularBufferWriteHead %= pitchshiftVariables.mCircularBufferLenght;
    
        }
   

    
    for (int channel = 0; channel < getNumInputChannels(); ++channel) {
       
        
        float start_index = pitchshiftVariables.mCicularBufferWriteHead;
        float fade_out_index = start_index +  4*log(pitch_value)/r;
        
        float first_fade_out_index = fade_out_index;
        float first_start_index = start_index;
        
        if(fade_out_index < 0) fade_out_index = fade_out_index +  pitchshiftVariables.mCircularBufferLenght;
        float incr = pitch_value;
        int b = 0;
        for (auto i = 0; i < buffer.getNumSamples(); ++i)
        {
            

            float v = b*1.0f/(block_len/2);
            int v0 =  fade_out_index;
            int v1 = (v0 + 1) % pitchshiftVariables.mCircularBufferLenght;
            float t = fade_out_index - v0;
            float red_sample = (1- v)*linearInterpol(pitchshiftVariables.mCircularBuffer[channel].at(v0),
                           pitchshiftVariables.mCircularBuffer[channel].at(v1), t);
             v0 =  start_index;
             v1 = (v0 + 1) % pitchshiftVariables.mCircularBufferLenght;
             t = start_index - v0;
            float green_sample = (v)*linearInterpol(pitchshiftVariables.mCircularBuffer[channel].at(v0),
                           pitchshiftVariables.mCircularBuffer[channel].at(v1), t);
            
            buffer.setSample(channel, i, red_sample + green_sample);
            b++;
            b %= block_len/2;
            if(b == 0)
            {
                first_start_index += block_len/2;
                first_fade_out_index += block_len/2;
                start_index = first_start_index - incr;
                fade_out_index = first_fade_out_index - incr;
            }
            fade_out_index += incr;
            if(fade_out_index > pitchshiftVariables.mCircularBufferLenght - 1)
                fade_out_index =  fade_out_index -  (pitchshiftVariables.mCircularBufferLenght - 1);
            start_index += incr;
            if(start_index > pitchshiftVariables.mCircularBufferLenght - 1)
                start_index =  start_index -  (pitchshiftVariables.mCircularBufferLenght - 1);
           
        
        }
    }
    
    
    
}
void TugGlicentoAudioProcessor::processBlockReapeater(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
}
void TugGlicentoAudioProcessor::processBlockFilter (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockFilter");
 
    int channel = 0;
    double main_freq = *cutOffAtomic[line_no]/20000;
    myFilter[0][line_no].setCutoff(main_freq);
    myFilter[1][line_no].setCutoff(main_freq);
    
    auto chan0Write = copyBuffer[line_no].getWritePointer(0);
    auto chan1Write = copyBuffer[line_no].getWritePointer(1);
    for (auto i = 0; i < copyBuffer[line_no].getNumSamples(); ++i)
    {
        double freq = *envAtomic[line_no]*adsr[line_no].getNextSample();
        myFilter[0][line_no].setCutoffMod(freq);
        myFilter[1][line_no].setCutoffMod(freq);
        *chan0Write = myFilter[0][line_no].process(*chan0Write);
        *chan1Write = myFilter[1][line_no].process(*chan1Write);
        chan0Write++;
        chan1Write++;
    }
    
    
//     for (auto i = 0; i < copyBuffer[line_no].getNumSamples(); ++i)
//    {
//
//        double freq = *envAtomic[line_no]*adsr[line_no].getNextSample();
//
//        for(int channel = 0 ; channel < 2 ; channel++ )
//        {
//            copyBuffer[line_no].getSample(channel, i);
//            myFilter[channel][line_no].setCutoffMod(freq);
//            double sample = copyBuffer[line_no].getSample(channel, i);
//            sample  = myFilter[channel][line_no].process(sample);
//            copyBuffer[line_no].setSample(channel, i , sample);
//        }
//
//    }

//    dsp::AudioBlock<float> output (copyBuffer[line_no]);
//    bandpassfilter[line_no].process(dsp::ProcessContextReplacing<float>(output));
//    adsr[line_no].applyEnvelopeToBuffer(copyBuffer[line_no], 0, copyBuffer[line_no].getNumSamples());
    

}

