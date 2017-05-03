/*
 * DataProcessor.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_DATAPROCESSOR_HPP_
#define HEADERS_DATAPROCESSOR_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"
#include "transform/FftFactory.h"
#include "tools/TextPlot.h"

class DataProcessor
{
public:
	DataProcessor();
	void processData(const sf::SoundBuffer& data);
	void calculateFoundFrequency();
	u32 getFoundFrequency() const;
	void calculateHighestFFTPosition(Aquila::SpectrumType& spectrum);
	void convertDataToArray(const u64 			   samplesAmount,
					   	    const sf::SoundBuffer& data,
						    double 				   convertedData[]);
private:
	u32 highestFftAmplitudePosition;
	u32 foundFrequency;
	string dataStr;
};

#endif /* HEADERS_DATAPROCESSOR_HPP_ */
