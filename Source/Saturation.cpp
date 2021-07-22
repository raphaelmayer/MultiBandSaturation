#include "Saturation.h"
#include <stdio.h>


void Saturation::prepareToPlay(double samplerate, int samplesPerBlock, int numInputChannels)
{
	cSampleRate = samplerate;

	{
		//previousOutputLevel = 0;
		const juce::dsp::ProcessSpec& spec = { samplerate, (juce::uint32)samplesPerBlock, 2 };
		processorChain.prepare(spec);

		auto dir = juce::File::getCurrentWorkingDirectory();

		int numTries = 0;

		while (!dir.getChildFile("Resources").exists() && numTries++ < 15)
			dir = dir.getParentDirectory();

		//convolution.loadImpulseResponse(dir.getChildFile("Resources").getChildFile("guitar_amp.wav"),
		//	juce::dsp::Convolution::Stereo::yes,
		//	juce::dsp::Convolution::Trim::no,
		//	1024);
	}
}

void Saturation::processBlock(AudioSampleBuffer& buffer)
{
	int bufferSize = buffer.getNumSamples();
	int numChannels = buffer.getNumChannels(); // number of channels
	int M = round(numChannels / 2); // number of stereo channels

	{
		// use processorChain to modify signal
		//preGain.setGainLinear(getPreGain());
		//postGain.setGainLinear(getPostGain());

		//if (cSaturationType == CLIP_ID) waveshaper.functionToUse = CLIP_FUNC;
		//else if (cSaturationType == OVERDRIVE_ID) waveshaper.functionToUse = OVERDRIVE_FUNC;
		//else if (cSaturationType == BRIT_ID) waveshaper.functionToUse = BRIT_FUNC;
		//else if (cSaturationType == FUZZ_ID) waveshaper.functionToUse = FUZZ_FUNC;
		//else if (cSaturationType == TANH_ID) waveshaper.functionToUse = TANH_FUNC;
		//else if (cSaturationType == HALFRECT_ID) waveshaper.functionToUse = HALFRECT_FUNC;
		//else if (cSaturationType == FULLRECT_ID) waveshaper.functionToUse = FULLRECT_FUNC;
		//else if (cSaturationType == SIG_ID) waveshaper.functionToUse = SIG_FUNC;

		//auto block = juce::dsp::AudioBlock<float>(buffer);
		//auto context = juce::dsp::ProcessContextReplacing<float>(block);
		//processorChain.process(context);
	}

	for (int channel = 0; channel < numChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < bufferSize; ++sample)
		{
			float drySignal = *channelData;

			*channelData *= cPreGain * cRange;

			float distortedSignal = saturationTypes[cSaturationType - 1].transferFunction(*channelData);
			*channelData = 0 < cBlend ? (distortedSignal * cBlend + drySignal * (1.f / cBlend)) / 2 : drySignal;

			*channelData *= cPostGain;

			++channelData;
		}
	}
}
