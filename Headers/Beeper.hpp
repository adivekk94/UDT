/*
 * Beeper.hpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_BEEPER_HPP_
#define HEADERS_BEEPER_HPP_

#include <iostream>
#include "source/generator/SineGenerator.h"
#include "wrappers/SoundBufferAdapter.h"
#include "../Definitions/glo_def.hpp"

using namespace std;

class Beeper
{
public:
	Beeper(Aquila::FrequencyType sampleFreq);
	void beep(const Aquila::FrequencyType freq,
			  const u32 				  duration);

private:
	const Aquila::FrequencyType sampleFrequency;
	Aquila::SineGenerator sinGen;
};

#endif /* HEADERS_BEEPER_HPP_ */
