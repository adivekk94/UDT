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

void Recorder::testRecordedSound()
{
	sf::Sound sound(getBuffer());
	sound.play();
	sf::sleep(getBuffer().getDuration());
}
//
//sf::SoundBuffer Recorder::getBuffer()
//{
//	return buffer;
//}
