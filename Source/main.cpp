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

void showData(DataBitset data)
{
	cout << "DATA: ";
	for(u32 i = 0; i < DATA_SIZE; ++i)
	{
		cout << data[i];
	}
	cout << endl;
}

void showDataByte(const DataBitset& data)
{
//	cout << "BYTE: " << data.to_string().substr(0, 8) << ", as char = '" <<
//			static_cast<char>(data.to_ulong()) << "'" << endl;
	cout << static_cast<char>(data.to_ulong()) << endl;
}

void prepareDataToSend(DataBitset& data)
{
	crc.calculateCRC(data);
	CrcBitset calculatedCrc = crc.getCRC();
	for(u32 i = 0; i < CRC_LENGTH; ++i)
	{
		data.set(BYTE+i, calculatedCrc[i]);
	}
	data.set(DATA_SIZE-1, mainSystem.dataProcessor.getCalculatedParityBit(data));
}

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

//	string dataString[4] = {"000001110101", "000010011001", "000010000011", "000010110100"};
	string dataString[5] = {"000001001101", "000001101001", "000001110011", "000001101001", "000001100001"};
	bool dataReceivedCorrectly = true;
	if(mainSystem.isInTxMode()) //TxMode
	{
		DataBitset dataToSend;
		for(u32 i = 0; i < 5; ++i)
		{
			dataToSend = DataBitset(dataString[i]);
			prepareDataToSend(dataToSend);
			cout << "Bitset: " << dataToSend << endl;
			mainSystem.dataSender.sendData(dataToSend);
			sf::SoundBuffer data2;
			while(true)
			{
				dataReceivedCorrectly = true;
				mainSystem.dataReceiver.receiveData(1);
				data2 = mainSystem.dataReceiver.getReceivedData();
				mainSystem.dataProcessor.processData(data2);
				if(mainSystem.dataProcessor.isDataRespReceived()
					 || mainSystem.dataProcessor.isDataRespReceivedPropably())
				{
					if(mainSystem.dataProcessor.isPositiveRespReceived())
					{
						cout << "Data send correctly" << endl;
					}
					else
					{
						cout << "Data send incorrectly. Retransmission needed." << endl;
						dataReceivedCorrectly = false;
						sf::sleep(sf::milliseconds(100));
						mainSystem.dataSender.sendData(dataToSend);
						sf::sleep(sf::milliseconds(100));
					}
					mainSystem.dataProcessor.setDataRespReceived(false);
					mainSystem.dataProcessor.setDataRespReceivedPropably(false);
					if(dataReceivedCorrectly)
					{
						break;
					}
				}
			}
			sf::sleep(sf::milliseconds(1000));
		}
	}
	else //RxMode
	{
		sf::SoundBuffer data;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
			data = mainSystem.dataReceiver.getReceivedData();
			mainSystem.dataProcessor.processData(data);
			DataBitset receivedData;
			if(mainSystem.dataProcessor.isCorrectDataSizeReceived())
			{
				receivedData = mainSystem.dataProcessor.getReceivedData();
				if(mainSystem.dataProcessor.isParityCorrect(receivedData)
					 && crc.isByteCorrect(receivedData))
				{
//					cout << "CORRECT RECEIVED ";
					showDataByte(receivedData);
					sf::sleep(sf::milliseconds(100));
					mainSystem.dataSender.sendPositiveResp();
					sf::sleep(sf::milliseconds(100));
				}
				else
				{
//					cout << "INCORRECT RECEIVED BYTE" << endl;
					sf::sleep(sf::milliseconds(100));
					mainSystem.dataSender.sendNegativeResp();
					sf::sleep(sf::milliseconds(100));
				}
				mainSystem.dataProcessor.setCorrectDataSizeReceived(false);
			}
			else if(mainSystem.dataProcessor.isInvalidTxReceived())
			{
				sf::sleep(sf::milliseconds(100));
				mainSystem.dataSender.sendNegativeResp();
				mainSystem.dataProcessor.setInvalidTxReceived(false);
				sf::sleep(sf::milliseconds(100));
			}
		}
	}

	cout << "End of program." << endl;
	return 0;
}
