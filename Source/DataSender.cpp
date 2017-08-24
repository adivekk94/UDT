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

void DataSender::sendFourBits(const EBitsData fourBits)
{
	switch(fourBits)
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

void DataSender::sendTwoBits(const EBitsData twoBits)
{
//	const u32 FREQ_DIFF = 100;
//	u32 index11 = 0, index00 = 0, index10 = 0, index01 = 0;
//	const u32 frequencies11[5] = {frequencies[3], frequencies[3]+FREQ_DIFF, frequencies[3]+2*FREQ_DIFF, frequencies[3]+3*FREQ_DIFF, frequencies[3]+4*FREQ_DIFF};
//	const u32 frequencies10[5] = {frequencies[2], frequencies[2]+FREQ_DIFF, frequencies[2]+2*FREQ_DIFF, frequencies[2]+3*FREQ_DIFF, frequencies[2]+4*FREQ_DIFF};
//	const u32 frequencies00[5] = {frequencies[0], frequencies[0]+FREQ_DIFF, frequencies[0]+2*FREQ_DIFF, frequencies[0]+3*FREQ_DIFF, frequencies[0]+4*FREQ_DIFF};
//	const u32 frequencies01[5] = {frequencies[1], frequencies[1]+FREQ_DIFF, frequencies[1]+2*FREQ_DIFF, frequencies[1]+3*FREQ_DIFF, frequencies[1]+4*FREQ_DIFF};

//	switch(twoBits)
//	{
//		case EOneOne:
//			beeper.beep(frequencies[3], BEEP_DURATION);
////			beeper.beep(frequencies11[index11++], BEEP_DURATION);
////			if(index11 == 4)
////				index11 = 0;
////			cout << "11" << endl;
//		break;
//		case EOneZero:
//			beeper.beep(frequencies[2], BEEP_DURATION);
////			beeper.beep(frequencies10[index10++], BEEP_DURATION);
////			if(index10 == 4)
////				index10 = 0;
////			cout << "10" << endl;
//		break;
//		case EZeroZero:
//			beeper.beep(frequencies[0], BEEP_DURATION);
////			beeper.beep(frequencies00[index00++], BEEP_DURATION);
////			if(index00 == 4)
////				index00 = 0;
////			cout << "00" << endl;
//		break;
//		case EZeroOne:
//			beeper.beep(frequencies[1], BEEP_DURATION);
////			beeper.beep(frequencies01[index01++], BEEP_DURATION);
////			if(index01 == 4)
////				index01 = 0;
////			cout << "01" << endl;
//		break;
//	}
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
		sendFourBits(bitsData);
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


