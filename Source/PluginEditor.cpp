/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandSaturationAudioProcessorEditor::MultibandSaturationAudioProcessorEditor(MultibandSaturationAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), scopeComponent(processor.getAudioBufferQueue())
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.

	addAndMakeVisible(scopeComponent);
	auto area = getLocalBounds();
	int visualiserMargin = 20;
	scopeComponent.setTopLeftPosition(visualiserMargin, 60);
	scopeComponent.setSize(area.getWidth() - visualiserMargin * 2, 200);

	// Low Band Knobs
	addAndMakeVisible(dropdownLowType = new ComboBox("Low Saturation Type Menu"));
	for (int i = 0; i < NUM_SATURATION_TYPES; ++i)
		(*dropdownLowType).addItem(saturationTypes[i].name, saturationTypes[i].id);
	(*dropdownLowType).setSelectedId(1);
	(*dropdownLowType).addListener(this);

	addAndMakeVisible(sliderLowPreGain = new Slider("Low PreGain Slider"));
	(*sliderLowPreGain).setRange(0, 30000, 1);
	(*sliderLowPreGain).setSliderStyle(Slider::Rotary);
	(*sliderLowPreGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderLowPreGain).addListener(this);
	(*sliderLowPreGain).setSkewFactor(0.2);

	addAndMakeVisible(sliderLowPostGain = new Slider("Low PostGain Slider"));
	(*sliderLowPostGain).setRange(0, 20, 0.01);
	(*sliderLowPostGain).setSliderStyle(Slider::Rotary);
	(*sliderLowPostGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderLowPostGain).addListener(this);

	addAndMakeVisible(sliderLowBlend = new Slider("Low Blend Slider"));
	(*sliderLowBlend).setRange(0, 1, 0.01);
	(*sliderLowBlend).setSliderStyle(Slider::Rotary);
	(*sliderLowBlend).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderLowBlend).addListener(this);

	// Mid Band Knobs
	addAndMakeVisible(dropdownMidType = new ComboBox("Mid Saturation Type Menu"));
	for (int i = 0; i < NUM_SATURATION_TYPES; ++i)
		(*dropdownMidType).addItem(saturationTypes[i].name, saturationTypes[i].id);
	(*dropdownMidType).setSelectedId(1);
	(*dropdownMidType).addListener(this);

	addAndMakeVisible(sliderMidPreGain = new Slider("Mid PreGain Slider"));
	(*sliderMidPreGain).setRange(0, 30000, 1);
	(*sliderMidPreGain).setSliderStyle(Slider::Rotary);
	(*sliderMidPreGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderMidPreGain).addListener(this);
	(*sliderMidPreGain).setSkewFactor(0.2);

	addAndMakeVisible(sliderMidPostGain = new Slider("Mid PostGain Slider"));
	(*sliderMidPostGain).setRange(0, 20, 0.01);
	(*sliderMidPostGain).setSliderStyle(Slider::Rotary);
	(*sliderMidPostGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderMidPostGain).addListener(this);

	addAndMakeVisible(sliderMidBlend = new Slider("Mid Blend Slider"));
	(*sliderMidBlend).setRange(0, 1, 0.01);
	(*sliderMidBlend).setSliderStyle(Slider::Rotary);
	(*sliderMidBlend).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderMidBlend).addListener(this);

	// High Band Knobs
	addAndMakeVisible(dropdownHighType = new ComboBox("High Saturation Type Menu"));
	for (int i = 0; i < NUM_SATURATION_TYPES; ++i)
		(*dropdownHighType).addItem(saturationTypes[i].name, saturationTypes[i].id);
	(*dropdownHighType).setSelectedId(1);
	(*dropdownHighType).addListener(this);

	addAndMakeVisible(sliderHighPreGain = new Slider("High PreGain Slider"));
	(*sliderHighPreGain).setRange(0, 30000, 1);
	(*sliderHighPreGain).setSliderStyle(Slider::Rotary);
	(*sliderHighPreGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderHighPreGain).addListener(this);
	(*sliderHighPreGain).setSkewFactor(0.2);

	addAndMakeVisible(sliderHighPostGain = new Slider("High PostGain Slider"));
	(*sliderHighPostGain).setRange(0, 20, 0.01);
	(*sliderHighPostGain).setSliderStyle(Slider::Rotary);
	(*sliderHighPostGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderHighPostGain).addListener(this);

	addAndMakeVisible(sliderHighBlend = new Slider("High Blend Slider"));
	(*sliderHighBlend).setRange(0, 1, 0.01);
	(*sliderHighBlend).setSliderStyle(Slider::Rotary);
	(*sliderHighBlend).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderHighBlend).addListener(this);

	// Low Cutoff Frequency Slider
	addAndMakeVisible(sliderLowCutoff = new Slider("Low Cutoff"));
	(*sliderLowCutoff).setRange(10, processor.getSampleRate() / 2, 0);
	(*sliderLowCutoff).setSliderStyle(Slider::Rotary);
	(*sliderLowCutoff).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderLowCutoff).addListener(this);
	(*sliderLowCutoff).setSkewFactor(0.2);

	// High Cutoff Frequency Slider
	addAndMakeVisible(sliderHighCutoff = new Slider("High Cutoff"));
	(*sliderHighCutoff).setRange(1, processor.getSampleRate() / 2, 0);
	(*sliderHighCutoff).setSliderStyle(Slider::Rotary);
	(*sliderHighCutoff).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderHighCutoff).addListener(this);
	(*sliderHighCutoff).setSkewFactor(0.2);

	// Saturation State Buttons
	addAndMakeVisible(buttonLowSaturationState = new TextButton("Low Saturation"));
	(*buttonLowSaturationState).setButtonText(TRANS("Low"));
	(*buttonLowSaturationState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
	(*buttonLowSaturationState).setColour(TextButton::textColourOnId, Colours::black);
	(*buttonLowSaturationState).setColour(TextButton::textColourOffId, Colours::white);
	(*buttonLowSaturationState).addListener(this);

	addAndMakeVisible(buttonMidSaturationState = new TextButton("Mid Saturation"));
	(*buttonMidSaturationState).setButtonText(TRANS("Mid"));
	(*buttonMidSaturationState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
	(*buttonMidSaturationState).setColour(TextButton::textColourOnId, Colours::black);
	(*buttonMidSaturationState).setColour(TextButton::textColourOffId, Colours::white);
	(*buttonMidSaturationState).addListener(this);

	addAndMakeVisible(buttonHighSaturationState = new TextButton("High Saturation"));
	(*buttonHighSaturationState).setButtonText(TRANS("High"));
	(*buttonHighSaturationState).setColour(TextButton::buttonOnColourId, Colours::lightblue);
	(*buttonHighSaturationState).setColour(TextButton::textColourOnId, Colours::black);
	(*buttonHighSaturationState).setColour(TextButton::textColourOffId, Colours::white);
	(*buttonHighSaturationState).addListener(this);

	(*buttonHighSaturationState).setClickingTogglesState(true);
	(*buttonMidSaturationState).setClickingTogglesState(true);
	(*buttonLowSaturationState).setClickingTogglesState(true);

	// Labels
	addAndMakeVisible(cutoffLabel = new Label("Cutoff", TRANS("Cutoff:")));
	(*cutoffLabel).setFont(Font(15.00f, Font::plain));
	(*cutoffLabel).setJustificationType(Justification::centredLeft);
	(*cutoffLabel).setEditable(false, false, false);
	(*cutoffLabel).setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(saturationTypeLabel = new Label("Saturation", TRANS("Saturation:")));
	(*saturationTypeLabel).setFont(Font(15.00f, Font::plain));
	(*saturationTypeLabel).setJustificationType(Justification::centredLeft);
	(*saturationTypeLabel).setEditable(false, false, false);
	(*saturationTypeLabel).setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(preGainLabel = new Label("PreGain", TRANS("PreGain:")));
	(*preGainLabel).setFont(Font(15.00f, Font::plain));
	(*preGainLabel).setJustificationType(Justification::centredLeft);
	(*preGainLabel).setEditable(false, false, false);
	(*preGainLabel).setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(postGainLabel = new Label("PostGain", TRANS("PostGain:")));
	(*postGainLabel).setFont(Font(15.00f, Font::plain));
	(*postGainLabel).setJustificationType(Justification::centredLeft);
	(*postGainLabel).setEditable(false, false, false);
	(*postGainLabel).setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(blendLabel = new Label("Blend", TRANS("Blend:")));
	(*blendLabel).setFont(Font(15.00f, Font::plain));
	(*blendLabel).setJustificationType(Justification::centredLeft);
	(*blendLabel).setEditable(false, false, false);
	(*blendLabel).setColour(Label::textColourId, Colours::white);

	addAndMakeVisible(sliderOverallGain = new Slider("Overall Gain"));
	(*sliderOverallGain).setRange(0, 10, 0);
	(*sliderOverallGain).setSliderStyle(Slider::Rotary);
	(*sliderOverallGain).setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	(*sliderOverallGain).addListener(this);

	addAndMakeVisible(overallGainLabel = new Label("OverallGain", TRANS("Overall Gain:")));
	(*overallGainLabel).setFont(Font(15.00f, Font::plain));
	(*overallGainLabel).setJustificationType(Justification::centredLeft);
	(*overallGainLabel).setEditable(false, false, false);
	(*overallGainLabel).setColour(Label::textColourId, Colours::white);

	setSize(732, 680);
	startTimer(100); // is this necessary? cant i update the knobs once in the constructor and then, whenever they change?
}

MultibandSaturationAudioProcessorEditor::~MultibandSaturationAudioProcessorEditor()
{
	sliderLowCutoff = nullptr;
	sliderHighCutoff = nullptr;

	buttonLowSaturationState = nullptr;
	buttonMidSaturationState = nullptr;
	buttonHighSaturationState = nullptr;

	dropdownLowType = nullptr;
	sliderLowPreGain = nullptr;
	sliderLowPostGain = nullptr;
	sliderLowBlend = nullptr;

	dropdownMidType = nullptr;
	sliderMidPreGain = nullptr;
	sliderMidPostGain = nullptr;
	sliderMidBlend = nullptr;

	dropdownHighType = nullptr;
	sliderHighPreGain = nullptr;
	sliderHighPostGain = nullptr;
	sliderHighBlend = nullptr;

	cutoffLabel = nullptr;
	preGainLabel = nullptr;
	postGainLabel = nullptr;

	overallGainLabel = nullptr;
	sliderOverallGain = nullptr;
}

//==============================================================================
void MultibandSaturationAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Multiband Saturation", getWidth() / 2 - 75, 0, 150, 20, Justification::centred, 1);
}

void MultibandSaturationAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	//(processor.visualiser).setBounds(100, 20, getWidth() - 100, 200);
	auto area = getLocalBounds();
	int visualiserMargin = 20;
	scopeComponent.setTopLeftPosition(visualiserMargin, 60);
	scopeComponent.setSize(area.getWidth() - visualiserMargin * 2, 200);

	// Cutoff Frequency Sliders
	(*sliderLowCutoff).setBounds(195, 31, 56, 64);
	(*sliderHighCutoff).setBounds(345, 31, 56, 64);

	// Saturation State Buttons
	(*buttonLowSaturationState).setBounds(130, 98, 50, 24);
	(*buttonMidSaturationState).setBounds(280, 98, 50, 24);
	(*buttonHighSaturationState).setBounds(430, 98, 50, 24);

	// Labels
	(*cutoffLabel).setBounds(16, 60, 88, 50);
	//(*saturationTypeLabel).setBounds(16, 292, 72, 50);
	(*preGainLabel).setBounds(16, 360, 72, 50);
	(*postGainLabel).setBounds(16, 440, 72, 50);
	(*blendLabel).setBounds(16, 520, 72, 50);

	// Low Band Knobs
	(*dropdownLowType).setBounds(120, 292, 80, 24);
	(*sliderLowPreGain).setBounds(120, 340, 80, 64);
	(*sliderLowPostGain).setBounds(120, 420, 80, 64);
	(*sliderLowBlend).setBounds(120, 500, 80, 64);

	// Mid Band Knobs
	(*dropdownMidType).setBounds(270, 292, 80, 24);
	(*sliderMidPreGain).setBounds(270, 340, 80, 64);
	(*sliderMidPostGain).setBounds(270, 420, 80, 64);
	(*sliderMidBlend).setBounds(270, 500, 80, 64);

	// High Band Knobs
	(*dropdownHighType).setBounds(420, 292, 80, 24);
	(*sliderHighPreGain).setBounds(420, 340, 80, 64);
	(*sliderHighPostGain).setBounds(420, 420, 80, 64);
	(*sliderHighBlend).setBounds(420, 500, 80, 64);

	// Overall Gain
	(*overallGainLabel).setBounds(520, 440, 88, 24);
	(*sliderOverallGain).setBounds(620, 420, 80, 64);

}

void MultibandSaturationAudioProcessorEditor::comboBoxChanged(ComboBox* dropdownThatWasChanged)
{
	if (dropdownThatWasChanged == dropdownLowType)
		processor.lowSaturation.setSaturationType((*dropdownLowType).getSelectedId());

	else if (dropdownThatWasChanged == dropdownMidType)
		processor.midSaturation.setSaturationType((*dropdownMidType).getSelectedId());

	else if (dropdownThatWasChanged == dropdownHighType)
		processor.highSaturation.setSaturationType((*dropdownHighType).getSelectedId());


}

void MultibandSaturationAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{
	float lowCutoff = (float)(*sliderLowCutoff).getValue();
	float highCutoff = (float)(*sliderHighCutoff).getValue();

	// Slider Changed Values for Low Saturation
	if (sliderThatWasMoved == sliderLowPreGain)
		processor.lowSaturation.setPreGain((float)(*sliderLowPreGain).getValue());
	else if (sliderThatWasMoved == sliderLowPostGain)
		processor.lowSaturation.setPostGain((float)(*sliderLowPostGain).getValue());
	else if (sliderThatWasMoved == sliderLowBlend)
		processor.lowSaturation.setBlend((float)(*sliderLowBlend).getValue());

	// Slider Changed Values for Mid Saturation
	else if (sliderThatWasMoved == sliderMidPreGain)
		processor.midSaturation.setPreGain((float)(*sliderMidPreGain).getValue());
	else if (sliderThatWasMoved == sliderMidPostGain)
		processor.midSaturation.setPostGain((float)(*sliderMidPostGain).getValue());
	else if (sliderThatWasMoved == sliderMidBlend)
		processor.midSaturation.setBlend((float)(*sliderMidBlend).getValue());

	// Slider Changed Values for High Saturation
	else if (sliderThatWasMoved == sliderHighPreGain)
		processor.highSaturation.setPreGain((float)(*sliderHighPreGain).getValue());
	else if (sliderThatWasMoved == sliderHighPostGain)
		processor.highSaturation.setPostGain((float)(*sliderHighPostGain).getValue());
	else if (sliderThatWasMoved == sliderHighBlend)
		processor.highSaturation.setBlend((float)(*sliderHighBlend).getValue());

	else if (sliderThatWasMoved == sliderOverallGain)
		processor.setOverallGain((float)(*sliderOverallGain).getValue());

	// Slider Changed Values for Cut Off Frequencies
	else if (sliderThatWasMoved == sliderLowCutoff)
	{
		processor.setLowCutoff(lowCutoff < highCutoff ? lowCutoff : highCutoff);
		(*sliderLowCutoff).setValue(lowCutoff < highCutoff ? lowCutoff : highCutoff);
	}
	else if (sliderThatWasMoved == sliderHighCutoff)
	{
		processor.setHighCutoff(lowCutoff < highCutoff ? highCutoff : lowCutoff);
		(*sliderHighCutoff).setValue(lowCutoff < highCutoff ? highCutoff : lowCutoff);
	}
}

void MultibandSaturationAudioProcessorEditor::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == buttonLowSaturationState)
		processor.setLowSaturationState((*buttonLowSaturationState).getToggleState());
	else if (buttonThatWasClicked == buttonMidSaturationState)
		processor.setMidSaturationState((*buttonMidSaturationState).getToggleState());
	else if (buttonThatWasClicked == buttonHighSaturationState)
		processor.setHighSaturationState((*buttonHighSaturationState).getToggleState());
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MultibandSaturationAudioProcessorEditor::timerCallback() {

	(*sliderOverallGain).setValue(processor.getOverallGain());

	(*dropdownLowType).setSelectedId(processor.lowSaturation.getSaturationType());
	(*sliderLowPreGain).setValue(processor.lowSaturation.getPreGain());
	(*sliderLowPostGain).setValue(processor.lowSaturation.getPostGain());
	(*sliderLowBlend).setValue(processor.lowSaturation.getBlend());

	(*dropdownMidType).setSelectedId(processor.midSaturation.getSaturationType());
	(*sliderMidPreGain).setValue(processor.midSaturation.getPreGain());
	(*sliderMidPostGain).setValue(processor.midSaturation.getPostGain());
	(*sliderMidBlend).setValue(processor.midSaturation.getBlend());

	(*dropdownHighType).setSelectedId(processor.highSaturation.getSaturationType());
	(*sliderHighPreGain).setValue(processor.highSaturation.getPreGain());
	(*sliderHighPostGain).setValue(processor.highSaturation.getPostGain());
	(*sliderHighBlend).setValue(processor.highSaturation.getBlend());

	(*buttonLowSaturationState).setToggleState(processor.getLowSaturationState(), dontSendNotification);
	(*buttonMidSaturationState).setToggleState(processor.getMidSaturationState(), dontSendNotification);
	(*buttonHighSaturationState).setToggleState(processor.getHighSaturationState(), dontSendNotification);

	(*sliderLowCutoff).setValue(processor.getLowCutoff());
	(*sliderHighCutoff).setValue(processor.getHighCutoff());

}
