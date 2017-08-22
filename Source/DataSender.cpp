/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
	: oneFreq(17500),
		oneZeroFreq(16800),
	  zeroFreq(18800),
		zeroOneFreq(20000)
{}

void DataSender::sendTwoBits(const EBitsData twoBits)
{
//	const double diff = 100;
//	if(oneFreq > 18200)
//	{
//		oneFreq = 17500;
//	}
//	if(zeroFreq > 19600)
//	{
//		zeroFreq = 18800;
//	}

	switch(twoBits)
	{
		case EOneOne:
			beeper.beep(oneFreq, BEEP_DURATION);
//			oneFreq += diff;
//			cout << "11" << endl;
		break;
		case EOneZero:
			beeper.beep(oneZeroFreq, BEEP_DURATION);
//			cout << "10" << endl;
		break;
		case EZeroZero:
			beeper.beep(zeroFreq, BEEP_DURATION);
//			cout << "00" << endl;
//			zeroFreq += diff;
		break;
		case EZeroOne:
			beeper.beep(zeroOneFreq, BEEP_DURATION);
//			cout << "01" << endl;
		break;
	}
}

void DataSender::sendData(const bitset<DATA_SIZE> data)
{
	EBitsData bitsData;
	for(u32 i = 0; i < DATA_SIZE; i+=2)
	{
		if(data[i] && data[i+1]) //11
		{
			bitsData = EOneOne;
		}
		else if(data[i] && !data[i+1]) //10
		{
			bitsData = EOneZero;
		}
		else if(!data[i] && data[i+1]) //01
		{
			bitsData = EZeroOne;
		}
		else //00
		{
			bitsData = EZeroZero;
		}
		sendTwoBits(bitsData);
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


