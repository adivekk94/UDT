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

bool Recorder::onProcessSamples(const sf::Int16* samples,
								std::size_t      sampleCount)
{
	samples = buffer.getSamples();
	sampleCount = static_cast<std::size_t>(buffer.getSampleCount());
	//TODO: proccess data
	return true; //tmp
}

void Recorder::onStop()
{
	cout << "Buffer size1: " << getBuffer().getDuration().asSeconds() << endl;
//	buffer = getBuffer();
	//TODO: getDataToBuffer
}

void Recorder::testRecordedSound()
{
	cout << "Buffer size: " << buffer.getDuration().asSeconds() << endl;
	sf::Sound sound(buffer);
	sound.play();
	while(2 == sound.getStatus())
	{

	}
}
