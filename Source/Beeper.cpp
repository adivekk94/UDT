/*
 * Beeper.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/Beeper.hpp"

Beeper::Beeper()
	: sampleFrequency(SAMPLE_FREQ),
	  sinGen(sampleFrequency)
{
	sinGen.setAmplitude(AMPLITUDE);
}

void Beeper::beep(const Aquila::FrequencyType freq,
				  				const u32 				  duration) //in ms
{
	const u32 numSamples = sampleFrequency * duration / 1000;
	sinGen.setFrequency(freq).generate(numSamples);
	Aquila::SoundBufferAdapter buffer(sinGen);
	sf::Sound sound(buffer);
	sound.play();
	sf::sleep(buffer.getDuration());
}


