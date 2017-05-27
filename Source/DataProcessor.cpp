/*
 * DataProcessor.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataProcessor.hpp"
#include "source/generator/SineGenerator.h"

DataProcessor::DataProcessor()
	: highestFftAmplitudePosition(0),
	  foundFrequency(0),
	  dataStr(),
	  currentBit(0),
		dataReceived(false),
		invalidTxReceived(false),
		crcReceived(false),
		crcRespReceived(false),
		crcExpected(false),
		crcRespExpected(false),
		dataExpected(false),
		dataRespExpected(false),
		dataRespReceived(false)
{
	memset(receivedByte, 0, BYTE);
}

void DataProcessor::calculateFoundFrequency()
{
	foundFrequency = highestFftAmplitudePosition*SAMPLE_FREQ/WINDOW_SIZE;
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
//	for(u32 i = 1; i < lengthToCheck; ++i)
	for(u32 i = lengthToCheck-1; i > lengthToCheck/2; --i)
	{
		ampTmp = sqrt(pow(spectrum.at(i).real(), 2)+pow(spectrum.at(i).imag(), 2));
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
									   double 			      convertedData[])
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
//	Aquila::TextPlot plt("Spectrum");
//	plt.plotSpectrum(spectrum);
	calculateHighestFFTPosition(spectrum);
	calculateFoundFrequency();
	u32 freq = getFoundFrequency();
//	cout << "Freq = " << freq << ", HighestFftAmplitudePosition = " << highestFftAmplitudePosition << endl;
	if(freq > 17200 && freq < 18400)
	{
		dataStr += "1";
		receivedByte[currentBit] = 1;
		++currentBit;
	}
	else if(freq > 18700 && freq < 20000)
	{
		dataStr += "0";
		receivedByte[currentBit] = 0;
		++currentBit;
	}
	else
	{
		if(8 == currentBit && dataExpected)
		{
			dataReceived = true;
		}
		else if(6 == currentBit && crcExpected)
		{
			crcReceived = true;
		}
		else if(3 == currentBit && crcRespExpected)
		{
			crcRespReceived = true;
		}
		else if(3 == currentBit && dataRespExpected)
		{
			dataRespReceived = true;
		}
		else if(currentBit > 0)
		{
			cout << "InvalidTxReceived, numOfBitsReceived = " << (u32)currentBit << endl;
			invalidTxReceived = true;
		}
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

void DataProcessor::setDataReceived(const bool state)
{
	dataReceived = state;
}

void DataProcessor::setInvalidTxReceived(const bool state)
{
	invalidTxReceived = state;
}

bool* DataProcessor::getReceivedByte()
{
	return receivedByte;
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

bool DataProcessor::isPositiveRespReceived() const
{
	if((receivedByte[0] && receivedByte[1])
		 || (receivedByte[1] && receivedByte[2])
		 || (receivedByte[0] && receivedByte[2]))
	{
		return true;
	}
	return false;
}
