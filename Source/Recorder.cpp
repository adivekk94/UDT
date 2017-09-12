/*
 * Recorder.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/Recorder.hpp"

Recorder::Recorder()
{}

void Recorder::recordData(const u32 recLength)
{
	start(SAMPLE_FREQ);
	sf::sleep(sf::milliseconds(recLength));
	stop();
}
