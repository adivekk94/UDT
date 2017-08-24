/*
 * DataProcessor.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataProcessor.hpp"
#include "aquila/source/generator/SineGenerator.h"

DataProcessor::DataProcessor()
	: highestFftAmplitudePosition(0),
	  foundFrequency(0),
	  dataStr(),
		correctDataSizeReceived(false),
	  currentBit(0),
		dataReceived(false),
		invalidTxReceived(false),
		crcReceived(false),
		crcRespReceived(false),
		crcExpected(false),
		crcRespExpected(false),
		dataExpected(false),
		dataRespExpected(false),
		dataRespReceived(false),
		dataRespReceivedPropably(false)
{
}

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
//			cout << "FFT " << i << " = " << ampTmp << ", freq = " << i*SAMPLE_FREQ/WINDOW_SIZE << endl;
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

void DataProcessor::processData(const sf::SoundBuffer& data)
{
	const u64 samplesAmount = data.getSampleCount();
	double convertedData[samplesAmount];
	convertDataToArray(samplesAmount, data, convertedData);
	auto fft = Aquila::FftFactory::getFft(WINDOW_SIZE);

	Aquila::SpectrumType spectrum = fft->fft(convertedData);
	calculateHighestFFTPosition(spectrum);
	calculateFoundFrequency();
	u32 freq = getFoundFrequency();
//	cout << "Freq = " << freq << ", HighestFftAmplitudePosition = " << highestFftAmplitudePosition << endl;
	if(freq > 17600 && freq < 18300) //11
	{
//		cout << "Rcv 11: " << freq << endl;
		receivedData[currentBit++] = 1;
		receivedData[currentBit++] = 1;
	}
	else if(freq > 18400 && freq < 19100) //00
	{
//		cout << "Rcv 00: " << freq << endl;
		receivedData[currentBit++] = 0;
		receivedData[currentBit++] = 0;
	}
	else if(freq > 16800 && freq < 17500) //10
	{
//		cout << "Rcv 10: " << freq << endl;
		receivedData[currentBit++] = 1;
		receivedData[currentBit++] = 0;
	}
	else if(freq > 19200 && freq < 19900) //01
	{
//		cout << "Rcv 01: " << freq << endl;
		receivedData[currentBit++] = 0;
		receivedData[currentBit++] = 1;
	}
	else if(currentBit > 0)
	{
		if((DATA_SIZE == currentBit)
			 || (DATA_SIZE+1 == currentBit))
		{
			correctDataSizeReceived = true;
		}
		else if(((2*RESP_LENGTH) == currentBit)
				    || (2*(RESP_LENGTH+1)) == currentBit)
		{
			dataRespReceived = true;
		}
		else if((2*(RESP_LENGTH-1)) == currentBit)
		{
			dataRespReceivedPropably = true;
		}
//		else if((2*CRC_LENGTH == currentBit) && crcExpected)
//		{
//			crcReceived = true;
//		}
//		else if((RESP_LENGTH == currentBit) && crcRespExpected)
//		{
//			crcRespReceived = true;
//		}
//		else if((RESP_LENGTH == currentBit) && dataRespExpected)
//		{
//			dataRespReceived = true;
//		}
//			cout << "InvalidTxReceived, numOfBitsReceived = " << (u32)currentBit;
//			cout << ", BadData = ";
//			for(u32 i = 0; i < currentBit; ++i)
//			{
//				cout << receivedData[i];
//			}
//			cout << endl;
		invalidTxReceived = true;
		currentBit = 0;
	}
	resetHighestFftAmplitudePosition();
}

string DataProcessor::getDataStr() const
{
	return dataStr;
}

bool DataProcessor::isDataRespReceived() const
{
	return dataRespReceived;
}

bool DataProcessor::isDataRespReceivedPropably() const
{
	return dataRespReceivedPropably;
}

bool DataProcessor::isByteReceived() const
{
	return dataReceived;
}

bool DataProcessor::isCrcRespReceived() const
{
	return crcRespReceived;
}

bool DataProcessor::isCrcReceived() const
{
	return crcReceived;
}

bool DataProcessor::isInvalidTxReceived() const
{
	return invalidTxReceived;
}

void DataProcessor::setCrcReceived(const bool state)
{
	crcReceived = state;
}

void DataProcessor::setCrcRespReceived(const bool state)
{
	crcRespReceived = state;
}

void DataProcessor::setDataReceived(const bool state)
{
	dataReceived = state;
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

void DataProcessor::activateCrcExpected()
{
	crcExpected = true;
}

void DataProcessor::deactivateCrcExpected()
{
	crcExpected = false;
}

void DataProcessor::activateCrcRespExpected()
{
	crcRespExpected = true;
}

void DataProcessor::deactivateCrcRespExpected()
{
	crcRespExpected = false;
}

void DataProcessor::activateDataExpected()
{
	dataExpected = true;
}

void DataProcessor::deactivateDataExpected()
{
	dataExpected = false;
}

void DataProcessor::activateDataRespExpected()
{
	dataRespExpected = true;
}

void DataProcessor::deactivateDataRespExpected()
{
	dataRespExpected = false;
}

bool DataProcessor::isCrcRespExpectedActive() const
{
	return crcRespExpected;
}

bool DataProcessor::isPositiveRespReceived() const
{
	if(dataRespReceivedPropably)
	{
		if(receivedData[0] && receivedData[2])
		{
			return true;
		}
		return false;
	}

	if((receivedData[0] && receivedData[2])
		 || (receivedData[2] && receivedData[4])
		 || (receivedData[0] && receivedData[4]))
	{
		return true;
	}
	return false;
}

bool DataProcessor::isPositiveRespReceivedPropably() const
{
	if(receivedData[0] && receivedData[2])
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

