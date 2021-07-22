#ifndef Saturation_h
#define Saturation_h
#include "../JuceLibraryCode/JuceHeader.h"
#include "SaturationTypes.h"

class Saturation
{
public:
	Saturation()
	{
	}
	~Saturation() {}

	void prepareToPlay(double samplerate, int samplesPerBlock, int numInputChannels);
	void processBlock(AudioSampleBuffer& buffer);

	// setters
	void setSaturationType(int type) { cSaturationType = type; };
	void setPreGain(float preGain) { cPreGain = preGain; }
	void setPostGain(float postGain) { cPostGain = postGain; }
	void setBlend(float blend) { cBlend = blend; }
	void setRange(float range) { cRange = range; }

	// getters
	int getSaturationType() { return cSaturationType; };
	float getPreGain() { return cPreGain; }
	float getPostGain() { return cPostGain; }
	float getBlend() { return cBlend; }
	float getRange() { return cRange; }

private:
	enum
	{
		preGainIndex,
		waveshaperIndex,
		//convolutionIndex,
		postGainIndex
	};
	juce::dsp::ProcessorChain<
		juce::dsp::Gain<float>,
		juce::dsp::WaveShaper<float>,
		//juce::dsp::Convolution,
		juce::dsp::Gain<float>
	> processorChain;
	juce::dsp::Gain<float>& preGain = processorChain.template get<preGainIndex>();
	juce::dsp::WaveShaper<float>& waveshaper = processorChain.template get<waveshaperIndex>();
	//juce::dsp::Convolution& convolution = processorChain.template get<convolutionIndex>();
	juce::dsp::Gain<float>& postGain = processorChain.template get<postGainIndex>();

	// Parameters
	float cSampleRate;

	int cSaturationType = 1;
	float cPreGain = 1.0f;
	float cPostGain = 1.0f;
	float cBlend = 1.0f;
	float cRange = 1.0f;

	// Saturation ON-OFF state
	int compressorState = 1;

	// Gain and Levels
	//float inputGain;
	//float inputLevel;
	//float outputGain;
	//float outputLevel;

	//float previousOutputLevel;

	//float controlVoltage;
};

#endif /* Saturation_h */
