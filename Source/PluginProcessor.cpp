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
        tmp_s << valueTreeNames[LINEVOL] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0,1.0f,0.9f));
        lineVol[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[EFFECT] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(tmp_s, tmp_s,effectChoicesStr,1));

        
        tmp_s.clear();
        tmp_s << valueTreeNames[CUTOFF] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,20,20000.0f,200));
        cutOffAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[Q] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.01,1.0,0.2));
        qAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
    
        
        tmp_s.clear();
        tmp_s << valueTreeNames[ATTACKNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.1,5,1));
        attackAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[DECAYNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.1,5,1));
        decayAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[SUSTAINNAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.1,5,1));
        sustainAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        tmp_s.clear();
        tmp_s << valueTreeNames[RELEASENAME] << j;
        valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(tmp_s, tmp_s,0.1,5,1));
        releaseAtomic[j] = valueTreeState.getRawParameterValue(tmp_s);
        
        
        
        
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
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockFilter);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDecimator);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockDistortion);
    myEffecrBankFunctions.push_back(&TugGlicentoAudioProcessor::processBlockPhaser);
  
    
    
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
        
        filter_coeff[i].freq = 200*pow(2,i);
        filter_coeff[i].q = 0.5;
        *bandpassfilter[i].state = *dsp::IIR::Coefficients<float>::makeBandPass(mySampleRate,  filter_coeff[i].freq,filter_coeff[i].q);
        
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
                }
                
            }
            
        }
        for(int j = 0 ; j< 2 ;j++)
        {
           for(int i = 0 ; i< numOfLine ;i++)
            {
      
                *cb_ptr[i][j] = * buf_ptr[j]*lineGainSmooth[i].getNextValue()*lineVolSmooth[i].getNextValue();
                
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
    
    for(auto i = 0 ; i < numOfLine ; i++)
    for (auto channel = 0; channel < copyBuffer[i].getNumChannels(); channel++)
    {
        
        buffer.addFrom(channel, 0, copyBuffer[i], channel, 0, buffer.getNumSamples());
        
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
void TugGlicentoAudioProcessor::processBlockDleay (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDleay");
    
    const int numInputChannels = getTotalNumInputChannels();
    const int numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        auto* channelDatain = buffer.getWritePointer (channel);
        auto* channelDataout = copyBuffer[line_no].getWritePointer (channel);
        
        for (int sample = 0; sample < numSamples; ++sample) {
            const float in = channelDatain[sample];
            
            channelDataout[sample] = in*lineGainSmooth[line_no].getNextValue();
            
            
        }
    }
    
    
}
void TugGlicentoAudioProcessor::processBlockReverb (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages ,int line_no)
{
    DBG("processBlockReverb");
    

    params.dryLevel = 0.5;
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
}
void TugGlicentoAudioProcessor::processBlockDecimator (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDecimator");
}
void TugGlicentoAudioProcessor::processBlockDistortion (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
}
void TugGlicentoAudioProcessor::processBlockPhaser(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockDistortion");
}
void TugGlicentoAudioProcessor::processBlockFilter (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int line_no)
{
    DBG("processBlockFilter");
 


    dsp::AudioBlock<float> output (copyBuffer[line_no]);
    
    bandpassfilter[line_no].process(dsp::ProcessContextReplacing<float>(output));
    
    //waveshape.process(dsp::ProcessContextReplacing<float>(output));
}

