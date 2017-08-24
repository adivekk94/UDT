/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
	: frequencies{ ZERO_ZERO_FREQ, ZERO_ONE_FREQ,
								 ONE_ZERO_FREQ, ONE_ONE_FREQ }
{}

void DataSender::sendTwoBits(const EBitsData twoBits)
{
//	const u32 FREQ_DIFF = 100;
//	u32 index11 = 0, index00 = 0, index10 = 0, index01 = 0;
//	const u32 frequencies11[5] = {frequencies[3], frequencies[3]+FREQ_DIFF, frequencies[3]+2*FREQ_DIFF, frequencies[3]+3*FREQ_DIFF, frequencies[3]+4*FREQ_DIFF};
//	const u32 frequencies10[5] = {frequencies[2], frequencies[2]+FREQ_DIFF, frequencies[2]+2*FREQ_DIFF, frequencies[2]+3*FREQ_DIFF, frequencies[2]+4*FREQ_DIFF};
//	const u32 frequencies00[5] = {frequencies[0], frequencies[0]+FREQ_DIFF, frequencies[0]+2*FREQ_DIFF, frequencies[0]+3*FREQ_DIFF, frequencies[0]+4*FREQ_DIFF};
//	const u32 frequencies01[5] = {frequencies[1], frequencies[1]+FREQ_DIFF, frequencies[1]+2*FREQ_DIFF, frequencies[1]+3*FREQ_DIFF, frequencies[1]+4*FREQ_DIFF};

	switch(twoBits)
	{
		case EOneOne:
			beeper.beep(frequencies[3], BEEP_DURATION);
//			beeper.beep(frequencies11[index11++], BEEP_DURATION);
//			if(index11 == 4)
//				index11 = 0;
//			cout << "11" << endl;
		break;
		case EOneZero:
			beeper.beep(frequencies[2], BEEP_DURATION);
//			beeper.beep(frequencies10[index10++], BEEP_DURATION);
//			if(index10 == 4)
//				index10 = 0;
//			cout << "10" << endl;
		break;
		case EZeroZero:
			beeper.beep(frequencies[0], BEEP_DURATION);
//			beeper.beep(frequencies00[index00++], BEEP_DURATION);
//			if(index00 == 4)
//				index00 = 0;
//			cout << "00" << endl;
		break;
		case EZeroOne:
			beeper.beep(frequencies[1], BEEP_DURATION);
//			beeper.beep(frequencies01[index01++], BEEP_DURATION);
//			if(index01 == 4)
//				index01 = 0;
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
		beeper.beep(frequencies[3], BEEP_DURATION);
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


