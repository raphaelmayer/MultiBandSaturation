#ifndef SaturationTypes_h
#define SaturationTypes_h
/*
  ==============================================================================

	SaturationTypes.h
	Created: 19 Jul 2021 12:45:20pm
	Author:  rapha

  ==============================================================================
*/

// old implementation
//#define CLIP_NAME "Clip"
//#define CLIP_ID 1
//#define CLIP_FUNC [](float x) { return juce::jlimit(-0.5f, 0.5f, x); }
//
//#define OVERDRIVE_NAME "Overdrive"
//#define OVERDRIVE_ID 2
//#define OVERDRIVE_FUNC [](float x) { return (float)std::tanh(2*x); }
//
//#define BRIT_NAME "British 80's"
//#define BRIT_ID 3
//#define BRIT_FUNC [](float x) { return (2.f / float_Pi)* atan(x); }
//
//#define FUZZ_NAME "Fuzz"
//#define FUZZ_ID 4
//#define FUZZ_FUNC [](float x) { return x <= 0 ? -0.1f : juce::jlimit(0.0f, 0.5f, x); }
//
//#define TANH_NAME "Smooth"
//#define TANH_ID 5
//#define TANH_FUNC [](float x) { return (float)std::tanh(x); }
//
//#define HALFRECT_NAME "Half-wave Rectification"
//#define HALFRECT_ID 6
//#define HALFRECT_FUNC [](float x) { return x <= 0.0f ? 0.0f : x; }
//
//#define FULLRECT_NAME "Full-wave Rectification"
//#define FULLRECT_ID 7
//#define FULLRECT_FUNC [](float x) { return std::abs(x); }
//
//#define SIG_NAME "Destroyer"
//#define SIG_ID 8
//#define SIG_FUNC [](float x) { return (float)(x > 0) - (x < 0); }


#define NUM_SATURATION_TYPES 8

struct saturationType {
	String name;
	int id;
	std::function<float(float)> transferFunction;
};

static struct saturationType saturationTypes[NUM_SATURATION_TYPES] = {
	{
		"Clip", 1,
		[](float x) { return juce::jlimit(-0.5f, 0.5f, x); }
	},
	{
		"Overdrive", 2,
		[](float x) { return (float)std::tanh(2 * x); }
	},
	{
		"British 80's", 3,
		[](float x) { return (2.f / float_Pi) * atan(x); }
	},
	{
		"Fuzz", 4,
		[](float x) { return juce::jlimit(-0.1f, 0.5f, x); }
	},
	{ 
		"Smooth", 5,
		[](float x) { return (float)std::tanh(x); }
	},
	{ 
		"Half-wave Rectification", 6,
		[](float x) { return x <= 0.0f ? 0.0f : x; }
	},
	{ 
		"Full-wave Rectification", 7,
		[](float x) { return std::abs(x); }
	},
	{ 
		"Destroyer", 8,
		[](float x) { return (float)(x > 0) - (x < 0); }
	} 
};

#endif /* SaturationTypes_h */