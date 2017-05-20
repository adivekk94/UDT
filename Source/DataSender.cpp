/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
	: oneFreq(17500),
	  zeroFreq(19000)
{}

void DataSender::sendData(const bool isOne)
{
	const u32 dur = 100;
	const double diff = 100;
	if(oneFreq > 18200)
	{
		oneFreq = 17500;
	}
	if(zeroFreq > 19800)
	{
		zeroFreq = 19000;
	}

	if(isOne)
	{
		beeper.beep(oneFreq, dur);
		oneFreq += diff;
	}
	else
	{
		beeper.beep(zeroFreq, dur);
		zeroFreq += diff;
	}
	sf::sleep(sf::milliseconds(1));
}

void DataSender::setDataToSend(const u32 frequency, const u32 duration)
{

}

void DataSender::getData() const
{

}


