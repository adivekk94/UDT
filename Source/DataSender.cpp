/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
	: frequencies{ F000, F001, F010, F011,
								 F100, F101, F110, F111 }
{}

void DataSender::sendThreeBits(const u32 threeBits)
{
	beeper.beep(frequencies[threeBits], BEEP_DURATION);
}

void DataSender::sendData(const bitset<DATA_SIZE> data)
{
	u32 number = 0;
	for(u32 i = 0; i < DATA_SIZE; i+=3)
	{
		number =   (data[i]   ? 4 : 0)
						 + (data[i+1] ? 2 : 0)
						 + (data[i+2] ? 1 : 0);
		sendThreeBits(number);
	}
}

void DataSender::sendPositiveResp()
{
	for(u32 i = 0; i < RESP_LENGTH; ++i)
	{
		beeper.beep(frequencies[7], BEEP_DURATION);
	}
}

void DataSender::sendNegativeResp()
{
	for(u32 i = 0; i < RESP_LENGTH; ++i)
	{
		beeper.beep(frequencies[0], BEEP_DURATION);
	}
}
