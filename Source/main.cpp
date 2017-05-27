/*
 * main.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/main.hpp"
#include "tools/TextPlot.h"
#include "transform/Fft.h"
#include <cstdlib>


int main(int argc, char* argv[])
{
	cout << "Type command to execute:\n1. Send data (s)\n2. Receive data (r)\nCommand: ";
	char action;
	cin >> action;
	switch(action)
	{
		case 'r':
			mainSystem.setRxMode();
		break;
		case 's':
			mainSystem.setTxMode();
		break;
		default:
			cout << "Bad command. Exiting..." << endl;
			return -1;
	}

//	u32 numOfBytes = 1;
//	if(2 == argc)
//	{
//		numOfBytes = atoi(argv[1]);
//	}

	CRC crc;
//	bool dataSend[] = {1, 1, 0, 1, 0, 1, 0, 1}; //CRC = 2
//	bool dataSend[] = {1, 1, 0, 0, 1, 0, 0, 1}; //CRC = 1
	if(mainSystem.isInTxMode()) //TxMode
	{
		bool dataSend[] = {1, 0, 1, 0, 1, 1, 1, 0}; //CRC = 5
		crc.calculateCRC(dataSend);
		bool crcBits[CRC_LENGTH*2];
		u8 tmpCrc = crc.getCRC();
		for(u32 i = 0; i < CRC_LENGTH; ++i)
		{
			crcBits[i] = tmpCrc%2;
			tmpCrc /= 2;
		}
		memcpy(crcBits+CRC_LENGTH, crcBits, 3);
		for(u32 i = 0; i < CRC_LENGTH*2; ++i)
		{
			mainSystem.dataSender.sendData(crcBits[i]);
		}
		mainSystem.dataProcessor.activateCrcRespExpected();

		sf::SoundBuffer data2;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
			data2 = mainSystem.dataReceiver.getReceivedData();
			mainSystem.dataProcessor.processData(data2);
			if(mainSystem.dataProcessor.isCrcRespReceived())
			{
				if(mainSystem.dataProcessor.isPositiveRespReceived())
				{
					cout << "CRC is good. Should now send Tx." << endl;
					mainSystem.dataProcessor.deactivateCrcRespExpected();
					for(u32 i = 0; i < BYTE; ++i)
					{
						mainSystem.dataSender.sendData(dataSend[i]);
					}
					mainSystem.dataProcessor.activateDataRespExpected();
				}
				else
				{
					cout << "CRC is bad. Retranssmission." << endl;
					for(u32 i = 0; i < CRC_LENGTH*2; ++i)
					{
						mainSystem.dataSender.sendData(crcBits[i]);
					}
					mainSystem.dataProcessor.activateCrcRespExpected();
				}
			}
			else if(mainSystem.dataProcessor.isDataRespReceived())
			{
				if(mainSystem.dataProcessor.isPositiveRespReceived())
				{
					cout << "Data send and received correctly." << endl;
					mainSystem.dataProcessor.deactivateDataRespExpected();
					break;
				}
				else
				{
					cout << "Bad data received. Retranssmission." << endl;
					for(u32 i = 0; i < BYTE; ++i)
					{
						mainSystem.dataSender.sendData(dataSend[i]);
					}
					mainSystem.dataProcessor.activateDataRespExpected();
				}
			}
		}
	}
	else //RxMode
	{
		mainSystem.dataProcessor.activateCrcExpected();
		sf::SoundBuffer data;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
			data = mainSystem.dataReceiver.getReceivedData();
			mainSystem.dataProcessor.processData(data);
			if(mainSystem.dataProcessor.isCrcReceived())
			{
				bool* tmpCrc = mainSystem.dataProcessor.getReceivedByte();
				if(tmpCrc[0] == tmpCrc[3]
				   && tmpCrc[1] == tmpCrc[4]
				   && tmpCrc[2] == tmpCrc[5])
				{
					cout << "CRC good received. Send ACK." << endl;
					const u8 crcVal = tmpCrc[2]*1 + tmpCrc[1]*2 + tmpCrc[0]*4;
					crc.setCRC(crcVal);
					mainSystem.dataSender.sendPositiveResp();
					mainSystem.dataProcessor.deactivateCrcExpected();
					mainSystem.dataProcessor.activateDataExpected();
				}
				else
				{
					cout << "Bad CRC. Need to be retranssmitted." << endl;
					mainSystem.dataSender.sendNegativeResp();
				}
				mainSystem.dataProcessor.setCrcReceived(false);
			}
			else if(mainSystem.dataProcessor.isByteReceived())
			{
				if(crc.isByteCorrect(mainSystem.dataProcessor.getReceivedByte()))
				{
					mainSystem.dataSender.sendPositiveResp();
					mainSystem.dataProcessor.deactivateDataExpected();
				}
				else
				{
					mainSystem.dataSender.sendNegativeResp();
				}
				mainSystem.dataProcessor.setDataReceived(false);
			}
			else if(mainSystem.dataProcessor.isInvalidTxReceived())
			{
				mainSystem.dataSender.sendNegativeResp();
				mainSystem.dataProcessor.setInvalidTxReceived(false);
			}
		}
	}

	cout << "End of program." << endl;
	return 0;
}
