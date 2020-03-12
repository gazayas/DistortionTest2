/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionTest2AudioProcessor::DistortionTest2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
state(*this, nullptr, "Parameters",
      {
          std::make_unique<AudioParameterFloat> ("drive", "Drive", NormalisableRange<float> (0.0f, 1.0f, 0.0001f), 0),
          std::make_unique<AudioParameterFloat> ("range", "Range", NormalisableRange<float> (0.0f, 3000.0f, 0.0001f), 0),
          std::make_unique<AudioParameterFloat> ("blend", "Blend", NormalisableRange<float> (0.0f, 1.0f, 0.0001f), 0),
          std::make_unique<AudioParameterFloat> ("volume", "Volume", NormalisableRange<float> (0.0f, 3.0f, 0.0001f), 0),
      })
#endif
{
    state.state = ValueTree ("drive");
    state.state = ValueTree ("range");
    state.state = ValueTree ("blend");
    state.state = ValueTree ("volume");
}

DistortionTest2AudioProcessor::~DistortionTest2AudioProcessor()
{
}

//==============================================================================
const String DistortionTest2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionTest2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionTest2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionTest2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionTest2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionTest2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionTest2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionTest2AudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionTest2AudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionTest2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionTest2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortionTest2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionTest2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DistortionTest2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float drive = state.getRawParameterValue("drive")->load();
    float range = state.getRawParameterValue("range")->load();
    float blend = state.getRawParameterValue("blend")->load();
    float volume = state.getRawParameterValue("volume")->load();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            float cleanSig = *channelData;
            
            *channelData *= drive * range;
            
            // https://www.desmos.com/calculator/nqfu5lxaij
            // ここにこの関数を入れると、driveの関数が見れる
            // g(x) = (2/π) * atan(x)
            // (atanを表示させるのにarctanを入力する)
            *channelData = (((((2.0f / float_Pi) * atan(*channelData)) * blend) + (cleanSig * (1.0f / blend))) / 2) * volume;
            
            channelData++;
        }
    }
}

//==============================================================================
bool DistortionTest2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionTest2AudioProcessor::createEditor()
{
    return new DistortionTest2AudioProcessorEditor (*this);
}

//==============================================================================
void DistortionTest2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistortionTest2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionTest2AudioProcessor();
}
