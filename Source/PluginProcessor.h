/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Saturation.h"
#include "SaturationTypes.h"
#include "Visualiser.h"

//==============================================================================
/**
*/
class MultibandSaturationAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	MultibandSaturationAudioProcessor();
	~MultibandSaturationAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	//==============================================================================
	// Setter Functions for each global parameter
	void setOverallGain(float overallGain) { pOverallGain = Decibels::decibelsToGain(overallGain); }

	// Cutoff Parameters
	void setLowCutoff(float lowCutoff) { pLowPassCutoff = lowCutoff; }
	void setHighCutoff(float highCutoff) { pHighPassCutoff = highCutoff; }

	// Saturation States
	void setLowSaturationState(bool lowSaturationState) { pLowSaturationState = lowSaturationState; }
	void setMidSaturationState(bool midSaturationState) { pMidSaturationState = midSaturationState; }
	void setHighSaturationState(bool highSaturationState) { pHighSaturationState = highSaturationState; }

	//==============================================================================
	// Getter Functions for each global parameter
	float getOverallGain() { return Decibels::gainToDecibels(pOverallGain); }

	// Cutoff Parameters
	float getLowCutoff() { return pLowPassCutoff; }
	float getHighCutoff() { return pHighPassCutoff; }

	// Saturation States
	bool getLowSaturationState() { return pLowSaturationState; }
	bool getMidSaturationState() { return pMidSaturationState; }
	bool getHighSaturationState() { return pHighSaturationState; }

	AudioBufferQueue<float>& getAudioBufferQueue() noexcept { return audioBufferQueue; }

	// Saturations
	Saturation lowSaturation;
	Saturation midSaturation;
	Saturation highSaturation;

private:
	AudioBufferQueue<float> audioBufferQueue;
	ScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };

	// Filter Definition
	IIRFilter lowBandFilterL1, lowBandFilterL2, lowBandFilterR1, lowBandFilterR2;
	IIRFilter lowMidBandFilterL1, lowMidBandFilterL2, lowMidBandFilterR1, lowMidBandFilterR2;
	IIRFilter highMidBandFilterL1, highMidBandFilterL2, highMidBandFilterR1, highMidBandFilterR2;
	IIRFilter highBandFilterL1, highBandFilterL2, highBandFilterR1, highBandFilterR2;
	IIRCoefficients coefficients;

	// Parameters
	int numChannels;
	float pOverallGain;

	// Cutoff Frequencies
	float pLowPassCutoff;
	float pHighPassCutoff;

	// Saturation States
	bool pLowSaturationState;
	bool pMidSaturationState;
	bool pHighSaturationState;

	void recalculateBandCoefficients(float sampleRate)
	{
		// Recalculate the coefficients in case the cutoffs are altered
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
	}

	void splitBands(AudioSampleBuffer& lowOutput, AudioSampleBuffer& midOutput, AudioSampleBuffer& highOutput, const int numSamples)
	{
		// Apply Filter onto the buffer
		//==============================
		// First Low Band Filtering Stage
		lowBandFilterL1.processSamples(lowOutput.getWritePointer(0), numSamples);
		lowBandFilterR1.processSamples(lowOutput.getWritePointer(1), numSamples);
		// Second Low Band Filtering Stage
		lowBandFilterL2.processSamples(lowOutput.getWritePointer(0), numSamples);
		lowBandFilterR2.processSamples(lowOutput.getWritePointer(1), numSamples);

		// First Low - Mid Band Filtering Stage
		lowMidBandFilterL1.processSamples(midOutput.getWritePointer(0), numSamples);
		lowMidBandFilterR1.processSamples(midOutput.getWritePointer(1), numSamples);
		// Second Low - Mid Band Filtering Stage
		lowMidBandFilterL2.processSamples(midOutput.getWritePointer(0), numSamples);
		lowMidBandFilterR2.processSamples(midOutput.getWritePointer(1), numSamples);

		//First High - Mid Band Filtering Stage
		highMidBandFilterL1.processSamples(midOutput.getWritePointer(0), numSamples);
		highMidBandFilterR1.processSamples(midOutput.getWritePointer(1), numSamples);
		// Second High - Mid Band Filtering Stage
		highMidBandFilterL2.processSamples(midOutput.getWritePointer(0), numSamples);
		highMidBandFilterR2.processSamples(midOutput.getWritePointer(1), numSamples);

		// First High Band Filtering Stage
		highBandFilterL1.processSamples(highOutput.getWritePointer(0), numSamples);
		highBandFilterR1.processSamples(highOutput.getWritePointer(1), numSamples);
		// Second High Band Filtering Stage
		highBandFilterL2.processSamples(highOutput.getWritePointer(0), numSamples);
		highBandFilterR2.processSamples(highOutput.getWritePointer(1), numSamples);
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultibandSaturationAudioProcessor)
};