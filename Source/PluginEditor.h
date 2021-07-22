/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SaturationTypes.h"

//==============================================================================
/**
*/
class MultibandSaturationAudioProcessorEditor : public AudioProcessorEditor, public Timer, public Slider::Listener, public Button::Listener, public ComboBox::Listener
{
public:
	MultibandSaturationAudioProcessorEditor(MultibandSaturationAudioProcessor&);
	~MultibandSaturationAudioProcessorEditor();

	//==============================================================================
	void timerCallback() override;

	void paint(Graphics&) override;
	void resized() override;
	void constructBandKnobs(
		String bandString,
		ScopedPointer <ComboBox> dropdownType,
		ScopedPointer <Slider> sliderPreGain,
		ScopedPointer <Slider> sliderPostGain,
		ScopedPointer <Slider> sliderBlend,
		ScopedPointer <Slider> sliderRange,
		MultibandSaturationAudioProcessorEditor* _this);
	void comboBoxChanged(ComboBox* comboBoxChanged) override;
	void sliderValueChanged(Slider* sliderMoved) override;
	void buttonClicked(Button* buttonClicked) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	MultibandSaturationAudioProcessor& processor;

	//==============================================================================

	//ScopedPointer<Visualiser> visualiser;
	ScopeComponent<float> scopeComponent;

	// Low Saturation Sliders
	ScopedPointer<ComboBox> dropdownLowType;
	ScopedPointer<Slider> sliderLowPreGain;
	ScopedPointer<Slider> sliderLowPostGain;
	ScopedPointer<Slider> sliderLowBlend;
	ScopedPointer<Slider> sliderLowRange;
	// Mid Saturation Sliders
	ScopedPointer<ComboBox> dropdownMidType;
	ScopedPointer<Slider> sliderMidPreGain;
	ScopedPointer<Slider> sliderMidPostGain;
	ScopedPointer<Slider> sliderMidBlend;
	ScopedPointer<Slider> sliderMidRange;
	// High Saturation Sliders
	ScopedPointer<ComboBox> dropdownHighType;
	ScopedPointer<Slider> sliderHighPreGain;
	ScopedPointer<Slider> sliderHighPostGain;
	ScopedPointer<Slider> sliderHighBlend;
	ScopedPointer<Slider> sliderHighRange;

	ScopedPointer<Slider> sliderOverallGain;

	// Labels
	ScopedPointer<Label> saturationTypeLabel;
	ScopedPointer<Label> preGainLabel;
	ScopedPointer<Label> postGainLabel;
	ScopedPointer<Label> blendLabel;
	ScopedPointer<Label> rangeLabel;
	ScopedPointer<Label> overallGainLabel;
	ScopedPointer<Label> cutoffLabel;

	// Buttons to Switch the Saturation states to ON/OFF
	ScopedPointer<TextButton> buttonLowSaturationState;
	ScopedPointer<TextButton> buttonMidSaturationState;
	ScopedPointer<TextButton> buttonHighSaturationState;

	// Crossover Cutoff Sliders
	ScopedPointer<Slider> sliderLowCutoff;
	ScopedPointer<Slider> sliderHighCutoff;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultibandSaturationAudioProcessorEditor)
};
