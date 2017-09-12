/*
 * DataProcessor.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataProcessor.hpp"

DataProcessor::DataProcessor()
	: highestFftAmplitudePosition(0),
	  foundFrequency(0),
		correctDataSizeReceived(false),
	  currentBit(0),
		dataRespReceived(false),
		dataRespReceivedPropably(false),
		invalidTxReceived(false)
{}

void DataProcessor::calculateFoundFrequency()
{
	foundFrequency = highestFftAmplitudePosition*SAMPLE_FREQ/WINDOW_SIZE;
}

bool DataProcessor::getCalculatedParityBit(const DataBitset& data, const bool forCalc)
{
	u8 numOfOnes = 0;
	for(u32 i = 0; i < DATA_SIZE-static_cast<u32>(forCalc); ++i)
	{
		if(data[i])
		{
			++numOfOnes;
		}
	}
	return numOfOnes%2;
}

bool DataProcessor::isParityCorrect(const DataBitset& data)
{

	return !getCalculatedParityBit(data, false);
}

void DataProcessor::resetHighestFftAmplitudePosition()
{
	highestFftAmplitudePosition = 0;
}

u32 DataProcessor::getFoundFrequency() const
{
	return foundFrequency;
}

void DataProcessor::calculateHighestFFTPosition(Aquila::SpectrumType& spectrum)
{
	double amp = 0.0, ampTmp = 0.0;
	const u32 lengthToCheck = spectrum.size()/2;

	for(u32 i = lengthToCheck-1; i > lengthToCheck/2; --i)
	{
		ampTmp = abs(spectrum.at(i));
		if(ampTmp > AMP_THRESHOLD && ampTmp > amp)
		{
			amp = ampTmp;
			highestFftAmplitudePosition = i;
		}
	}
}

void DataProcessor::convertDataToArray(const u64 			  samplesAmount,
																			 const sf::SoundBuffer& data,
																			 double* 			      convertedData)
{
	for(u32 i = 0; i < samplesAmount; ++i)
	{
		convertedData[i] = static_cast<double>(*(data.getSamples()+i));
	}
}

void DataProcessor::processData(const sf::SoundBuffer& data,
																const bool 						 expectResp)
{
	const u64 samplesAmount = data.getSampleCount();
	double convertedData[samplesAmount];
	convertDataToArray(samplesAmount, data, convertedData);
	auto fft = Aquila::FftFactory::getFft(WINDOW_SIZE);

	Aquila::SpectrumType spectrum = fft->fft(convertedData);
	calculateHighestFFTPosition(spectrum);
	calculateFoundFrequency();
	u32 freq = getFoundFrequency();
	if(freq > 0)
	{
		u32 freqDiff = abs(static_cast<i32>(freq-F000));
		if(freqDiff < FREQ_OFFSET_1) //000
		{
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 0;
		}
		else if(freqDiff < FREQ_OFFSET_2) //001
		{
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 1;
		}
		else if(freqDiff < FREQ_OFFSET_3) //010
		{
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 0;
		}
		else if(freqDiff < FREQ_OFFSET_4) //011
		{
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 1;
		}
		else if(freqDiff < FREQ_OFFSET_5) //100
		{
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 0;
		}
		else if(freqDiff < FREQ_OFFSET_6) //101
		{
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 0;
			receivedData[currentBit++] = 1;
		}
		else if(freqDiff < FREQ_OFFSET_7) //110
		{
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 0;
		}
		else if(freqDiff < FREQ_OFFSET_8) //111
		{
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 1;
			receivedData[currentBit++] = 1;
		}
	}
	else if(currentBit > 0)
	{
		if(!expectResp &&
			 ((DATA_SIZE == currentBit)
			 || (DATA_SIZE+3 == currentBit)))
		{
			correctDataSizeReceived = true;
		}
		else if(((3*RESP_LENGTH) == currentBit)
						|| (3*(RESP_LENGTH+1)) == currentBit)
		{
			dataRespReceived = true;
		}
		else if((3*(RESP_LENGTH-1)) == currentBit)
		{
			dataRespReceivedPropably = true;
		}
		else
		{
			invalidTxReceived = true;
		}

		currentBit = 0;
	}
	resetHighestFftAmplitudePosition();
}

bool DataProcessor::isDataRespReceived() const
{
	return dataRespReceived;
}

bool DataProcessor::isDataRespReceivedPropably() const
{
	return dataRespReceivedPropably;
}

bool DataProcessor::isInvalidTxReceived() const
{
	return invalidTxReceived;
}

void DataProcessor::setDataRespReceived(const bool state)
{
	dataRespReceived = state;
}

void DataProcessor::setDataRespReceivedPropably(const bool state)
{
	dataRespReceivedPropably = state;
}

void DataProcessor::setInvalidTxReceived(const bool state)
{
	invalidTxReceived = state;
}

DataBitset DataProcessor::getReceivedData() const
{
	return receivedData;
}

bool DataProcessor::isPositiveRespReceived() const
{
	if(dataRespReceivedPropably)
	{
		if(receivedData[0] && receivedData[3])
		{
			return true;
		}
		return false;
	}

	if((receivedData[0] && receivedData[3])
		 || (receivedData[3] && receivedData[6])
		 || (receivedData[0] && receivedData[6]))
	{
		return true;
	}
	return false;
}

bool DataProcessor::isCorrectDataSizeReceived() const
{
	return correctDataSizeReceived;
}

void DataProcessor::setCorrectDataSizeReceived(const bool state)
{
	correctDataSizeReceived = state;
}

