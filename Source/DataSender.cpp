/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
	: oneFreq(17000),
	  zeroFreq(18500)
{}

void DataSender::sendData(const bool zero)
{
	const u32 dur = 100;
	const double diff = 100;
//	if(oneFreq > 17700)
//	{
//		oneFreq = 17000;
//	}
//	if(zeroFreq > 19200)
//	{
//		zeroFreq = 18500;
//	}

	if(!zero)
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


