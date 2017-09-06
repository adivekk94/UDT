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

void DataSender::sendThreeBits(const EBitsData threeBits)
{
	switch(threeBits)
	{
		case E3xZero:
			beeper.beep(frequencies[0], BEEP_DURATION);
//			cout << "000" << endl;
		break;
		case E3xOne:
			beeper.beep(frequencies[7], BEEP_DURATION);
//			cout << "111" << endl;
		break;
		case E2xZeroOne:
			beeper.beep(frequencies[1], BEEP_DURATION);
//			cout << "001" << endl;
		break;
		case EZero2xOne:
			beeper.beep(frequencies[3], BEEP_DURATION);
//			cout << "011" << endl;
		break;
		case EOne2xZero:
			beeper.beep(frequencies[4], BEEP_DURATION);
//			cout << "100" << endl;
		break;
		case E2xOneZero:
			beeper.beep(frequencies[6], BEEP_DURATION);
//			cout << "110" << endl;
		break;
		case EOneZeroOne:
			beeper.beep(frequencies[5], BEEP_DURATION);
//			cout << "101" << endl;
		break;
		case EZeroOneZero:
			beeper.beep(frequencies[2], BEEP_DURATION);
//			cout << "010" << endl;
		break;
	}
}

void DataSender::sendData(const bitset<DATA_SIZE> data)
{
	EBitsData bitsData;
	for(u32 i = 0; i < DATA_SIZE; i+=3)
	{
		if(!data[i] && !data[i+1] && !data[i+2]) //000
		{
			bitsData = E3xZero;
		}
		else if(!data[i] && !data[i+1] && data[i+2]) //001
		{
			bitsData = E2xZeroOne;
		}
		else if(!data[i] && data[i+1] && data[i+2]) //011
		{
			bitsData = EZero2xOne;
		}
		else if(data[i] && data[i+1] && data[i+2]) //111
		{
			bitsData = E3xOne;
		}
		else if(data[i] && !data[i+1] && !data[i+2]) //100
		{
			bitsData = EOne2xZero;
		}
		else if(data[i] && data[i+1] && !data[i+2]) //110
		{
			bitsData = E2xOneZero;
		}
		else if(data[i] && !data[i+1] && data[i+2]) //101
		{
			bitsData = EOneZeroOne;
		}
		else //010
		{
			bitsData = EZeroOneZero;
		}
		sendThreeBits(bitsData);
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

void DataSender::setDataToSend(const u32 frequency, const u32 duration)
{

}

void DataSender::getData() const
{

}


