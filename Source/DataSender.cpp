/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
{

}

void DataSender::sendData(const bool zero, const bool changed)
{
//	beeper.beep(16500, 5000); //TODO: change to proper data
//	beeper.beep(16350, 1000);
	const u32 dur = 100;
	double oneFreq = 16000, zeroFreq = 18000;
	if(changed)
	{
//		oneFreq = 18000;
//		zeroFreq = 20000;
	}
	if(!zero)
	{
		beeper.beep(oneFreq, dur);
	}
	else
	{
		beeper.beep(zeroFreq, dur);
	}
	sf::sleep(sf::milliseconds(1));
}

void DataSender::setDataToSend(const u32 frequency, const u32 duration)
{

}

void DataSender::getData() const
{

}


