/*
 * Recorder.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_RECORDER_HPP_
#define HEADERS_RECORDER_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"
#include <SFML/Config.hpp>

class Recorder : public sf::SoundBufferRecorder
{
public:
	Recorder();
	void recordData(const u32 delay);
	void onStop();
	bool onProcessSamples(const sf::Int16* samples,
						  std::size_t 	   sampleCount);
	void testRecordedSound();
private:
	sf::SoundBuffer buffer;
};

#endif /* HEADERS_RECORDER_HPP_ */
