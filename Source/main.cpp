/*
 * main.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/main.hpp"
#include "aquila/tools/TextPlot.h"
#include "aquila/transform/Fft.h"
#include <cstdlib>

const string WORD_TO_END = "STOPSTOPSTOPSTOP";

void showData(DataBitset& data)
{
    cout << "DATA: " << data << endl;
}

void showDataByte(const DataBitset& data)
{
//	cout << "BYTE: " << data.to_string().substr(0, 8) << ", as char = '" <<
//			static_cast<char>(data.to_ulong()) << "'" << endl;
    cout << static_cast<char>(data.to_ulong());
}

void setParityBit(DataBitset& data)
{
    data.set(DATA_SIZE-1, mainSystem.dataProcessor.getCalculatedParityBit(data));
}

void prepareDataToSend(DataBitset& data)
{
    crc.calculateCRC(data);
    CrcBitset calculatedCrc = crc.getCRC();
    for(u32 i = 0; i < CRC_LENGTH; ++i)
    {
        data.set(BYTE+i, calculatedCrc[i]);
    }
    setParityBit(data);
}

void showMainMenu()
{
	system("clear");
	cout << endl << "     	Welcome to UDT v. 1.0  		   " << endl
			 << "     	Author: Adrian Graczyk  	 	 " << endl << endl
			 << "####################################" << endl
			 << "##           MAIN MENU            ##" << endl
			 << "####################################" << endl
			 << "##                                ##" << endl
			 << "##        1. Send data            ##" << endl
			 << "##        2. Receive data         ##" << endl
			 << "##                                ##" << endl
			 << "##                                ##" << endl
			 << "## Type number and press enter... ##" << endl
			 << "##                                ##" << endl
			 << "####################################" << endl;
}

void showTxMenu()
{
	system("clear");
		cout << "####################################" << endl
				 << "##         Transmitter mode       ##" << endl
				 << "####################################" << endl
				 << "##                                ##" << endl
				 << "##       Type word and press      ##" << endl
				 << "##       enter to send data...    ##" << endl
				 << "##                                ##" << endl
				 << "####################################" << endl
				 << endl << "\tWord: STOP";
		cout << flush;
		//TODO: update to access type word
}

void showRxMenu()
{
	system("clear");
	cout << "####################################" << endl
			 << "##          Receiver mode         ##" << endl
			 << "####################################" << endl;
	cout << flush;
}


int main(int argc, char* argv[])
{
	bool rxStarted = false;
	showMainMenu();
	char action = 'n';
	cin >> action;
	switch(action)
	{
		case '1':
			showTxMenu();
			mainSystem.setTxMode();
		break;
		case '2':
			showRxMenu();
			mainSystem.setRxMode();
		break;
		default:
			cout << "Bad command. Exiting..." << endl;
			return -1;
	}

//	string dataString[4] = {"000001110101", "000010011001", "000010000011", "000010110100"};
//	string dataString[5] = {"000001001101", "000001101001", "000001110011", "000001101001", "000001100001"}; //Misia
//	string dataString[5] = {"000001001000", "000001100101", "000001101100", "000001101100", "000001101111"}; //Hello
	string dataString[4] = {"000001010011", "000001010100", "000001001111", "000001010000"}; //STOP
	string word = "";
	const u32 timeDelay = 100;
	bool dataReceivedCorrectly = true;
	if(mainSystem.isInTxMode()) //TxMode
	{
		DataBitset dataToSend;
		for(u32 j = 0; j < 4; ++j)
		{
		for(u32 i = 0; i < 4; ++i)
		{
			dataToSend = DataBitset(dataString[i]);
			prepareDataToSend(dataToSend);
//			cout << "Bitset: " << dataToSend << endl;
			mainSystem.dataSender.sendData(dataToSend);
			sf::SoundBuffer data2;
			while(true)
			{
				dataReceivedCorrectly = true;
				mainSystem.dataReceiver.receiveData(1000);
				data2 = mainSystem.dataReceiver.getReceivedData();
				mainSystem.dataProcessor.processData(data2);
				if(mainSystem.dataProcessor.isDataRespReceived()
					 || mainSystem.dataProcessor.isDataRespReceivedPropably())
				{
					if(!mainSystem.dataProcessor.isPositiveRespReceived())
					{
//						cout << "Data send incorrectly. Retransmission needed." << endl;
						dataReceivedCorrectly = false;
						sf::sleep(sf::milliseconds(timeDelay));
						mainSystem.dataSender.sendData(dataToSend);
						sf::sleep(sf::milliseconds(timeDelay));
					}
					mainSystem.dataProcessor.setDataRespReceived(false);
					mainSystem.dataProcessor.setDataRespReceivedPropably(false);
					if(dataReceivedCorrectly)
					{
						break;
					}
				}
			}
			sf::sleep(sf::milliseconds(timeDelay));
		}
		}
	}
	else //RxMode
	{
		cout << "\tWaiting for transmission..." << endl;
		sf::SoundBuffer data;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1000);
			data = mainSystem.dataReceiver.getReceivedData();
			mainSystem.dataProcessor.processData(data);
			DataBitset receivedData;
			if(mainSystem.dataProcessor.isCorrectDataSizeReceived())
			{
				if(!rxStarted)
				{
					cout << "\tData receiving started..." << endl << endl;
					cout << "\tReceived data: ";
					cout << flush;
					rxStarted = true;
				}
				receivedData = mainSystem.dataProcessor.getReceivedData();
				if(mainSystem.dataProcessor.isParityCorrect(receivedData)
					 && crc.isByteCorrect(receivedData))
				{
//					cout << "CORRECT RECEIVED ";
					showDataByte(receivedData);
					word += static_cast<char>(receivedData.to_ulong());
					sf::sleep(sf::milliseconds(timeDelay/2));
					mainSystem.dataSender.sendPositiveResp();
					sf::sleep(sf::milliseconds(timeDelay));
					cout.flush();
				}
				else
				{
//					cout << "INCORRECT RECEIVED BYTE" << endl;
					sf::sleep(sf::milliseconds(timeDelay/2));
					mainSystem.dataSender.sendNegativeResp();
					sf::sleep(sf::milliseconds(timeDelay));
				}
				mainSystem.dataProcessor.setCorrectDataSizeReceived(false);
			}
			else if(mainSystem.dataProcessor.isInvalidTxReceived())
			{
				sf::sleep(sf::milliseconds(timeDelay/2));
				mainSystem.dataSender.sendNegativeResp();
				mainSystem.dataProcessor.setInvalidTxReceived(false);
				sf::sleep(sf::milliseconds(timeDelay));
			}
			if(WORD_TO_END == word)
			{
				cout << endl;
				break;
			}
		}
	}

	cout << endl << "End of program." << endl;
}
