/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandSaturationAudioProcessor::MultibandSaturationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	// Default Saturation States
	pLowSaturationState = 1;
	pMidSaturationState = 1;
	pHighSaturationState = 1;

	pOverallGain = 10.0;

	// Default Cutoff Frequencies
	pLowPassCutoff = 500;
	pHighPassCutoff = 3000;

	// Initialise the Saturations
	//lowSaturation = new Saturation;
	//midSaturation = new Saturation;
	//highSaturation = new Saturation;

}

MultibandSaturationAudioProcessor::~MultibandSaturationAudioProcessor()
{
}

//==============================================================================
const String MultibandSaturationAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool MultibandSaturationAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool MultibandSaturationAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool MultibandSaturationAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double MultibandSaturationAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int MultibandSaturationAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int MultibandSaturationAudioProcessor::getCurrentProgram()
{
	return 0;
}

void MultibandSaturationAudioProcessor::setCurrentProgram(int index)
{
}

const String MultibandSaturationAudioProcessor::getProgramName(int index)
{
	return {};
}

void MultibandSaturationAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void MultibandSaturationAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	numChannels = getTotalNumInputChannels();

	// Calculate Filter Coefficients
	//==============================
	// First Left Channel Filters
	lowBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
	lowMidBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
	highMidBandFilterL1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
	highBandFilterL1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

	// First Right Channel Filters
	lowBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
	lowMidBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
	highMidBandFilterR1.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
	highBandFilterR1.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

	// Second Left Channel Filters
	lowBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
	lowMidBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
	highMidBandFilterL2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
	highBandFilterL2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

	// Second Right Channel Filters
	lowBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pLowPassCutoff));
	lowMidBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pLowPassCutoff));
	highMidBandFilterR2.setCoefficients(coefficients.makeLowPass(sampleRate, pHighPassCutoff));
	highBandFilterR2.setCoefficients(coefficients.makeHighPass(sampleRate, pHighPassCutoff));

	// Prepare the Saturations
	lowSaturation.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
	midSaturation.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
	highSaturation.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());

	// Initialise the Saturation Parameters
	// currently done in Saturation.prepareToPlay
	//lowSaturation.setParameters(pLowRatio, pLowThreshold, pLowAttack, pLowRelease, pLowGain, pKneeWidth);
	//midSaturation.setParameters(pMidRatio, pMidThreshold, pMidAttack, pMidRelease, pMidGain, pKneeWidth);
	//highSaturation.setParameters(pHighRatio, pHighThreshold, pHighAttack, pHighRelease, pHighGain, pKneeWidth);
	
	//visualiser.clear();
}

void MultibandSaturationAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandSaturationAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void MultibandSaturationAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();

	// Initialise Buffer for Each Band
	AudioSampleBuffer lowOutput;
	AudioSampleBuffer midOutput;
	AudioSampleBuffer highOutput;

	// Set each buffer to an input
	lowOutput.makeCopyOf(buffer);
	midOutput.makeCopyOf(buffer);
	highOutput.makeCopyOf(buffer);

	float sampleRate = getSampleRate();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, numSamples);

	recalculateBandCoefficients(sampleRate);
	splitBands(lowOutput, midOutput, highOutput, numSamples);

	// Process each band individually
	if (pLowSaturationState)
		lowSaturation.processBlock(lowOutput);
	if (pMidSaturationState)
		midSaturation.processBlock(midOutput);
	if (pHighSaturationState)
		highSaturation.processBlock(highOutput);

	// Sum Each Band
	buffer.clear();
	for (int channel = 0; channel < totalNumInputChannels; channel++)
	{
		buffer.addFrom(channel, 0, lowOutput, channel, 0, numSamples, 1.0 / 3.0);
		buffer.addFrom(channel, 0, midOutput, channel, 0, numSamples, 1.0 / 3.0);
		buffer.addFrom(channel, 0, highOutput, channel, 0, numSamples, 1.0 / 3.0);
	}

	// Apply the Overall Gain
	buffer.applyGain(pOverallGain);

	scopeDataCollector.process(buffer.getReadPointer(0), (size_t)buffer.getNumSamples());
	//visualiser.pushBuffer(buffer);
}

//==============================================================================
bool MultibandSaturationAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultibandSaturationAudioProcessor::createEditor()
{
	return new MultibandSaturationAudioProcessorEditor(*this);
}

//==============================================================================
void MultibandSaturationAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void MultibandSaturationAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new MultibandSaturationAudioProcessor();
}
