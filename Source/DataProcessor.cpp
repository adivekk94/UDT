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
	  dataStr()
{}

void DataProcessor::calculateFoundFrequency()
{
	foundFrequency = highestFftAmplitudePosition*SAMPLE_FREQ/WINDOW_SIZE;
}

u32 DataProcessor::getFoundFrequency() const
{
	return foundFrequency;
}

void DataProcessor::calculateHighestFFTPosition(Aquila::SpectrumType& spectrum)
{
	double amp = 0.0, ampTmp = 0.0;
	const u32 lengthToCheck = spectrum.size()/2;
	for(u32 i = 1; i < lengthToCheck; ++i)
	{
		ampTmp = sqrt(pow(spectrum.at(i).real(), 2)+pow(spectrum.at(i).imag(), 2));
		if(ampTmp > amp)
		{
			amp = ampTmp;
			highestFftAmplitudePosition = i;
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
	//TODO: fft, filters etc.
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
//	cout << freq << endl;
	if(freq > 15500 && freq < 16500)
//		cout << "0" << endl;
		dataStr += "0";
	else if(freq > 17500 && freq < 18500)
//		cout << "1" << endl;
		dataStr += "1";
	else
	{
		cout << "-" << endl;
		if(dataStr.length() > 0)
			cout << "Data: " << dataStr << endl;
	}
}


