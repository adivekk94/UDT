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
		beeper.beep(oneFreq, BEEP_DURATION);
		oneFreq += diff;
	}
	else
	{
		beeper.beep(zeroFreq, BEEP_DURATION);
		zeroFreq += diff;
	}
}

void DataSender::sendPositiveResp()
{
	for(u32 i = 0; i < RESP_LENGTH; ++i)
	{
		beeper.beep(oneFreq, BEEP_DURATION);
	}
}

void DataSender::sendNegativeResp()
{
	for(u32 i = 0; i < RESP_LENGTH; ++i)
	{
		beeper.beep(zeroFreq, BEEP_DURATION);
	}
}

void DataSender::setDataToSend(const u32 frequency, const u32 duration)
{

}

void DataSender::getData() const
{

}


