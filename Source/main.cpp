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

const string WORD_TO_END = "STOP";

string sendingWord = "";

void showDataByte(const DataBitset& data)
{
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
				 << endl << "\tWord: ";
		cout << flush;
		cin >> sendingWord;
}

void showRxMenu()
{
	system("clear");
	cout << "####################################" << endl
			 << "##          Receiver mode         ##" << endl
			 << "####################################" << endl;
	cout << flush;
}

void completeTo12Bits(string& charInBinString)
{
	const u32 iterationsToDo = DATA_SIZE-charInBinString.length();
	for(u32 i = 0; i < iterationsToDo; ++i)
	{
		charInBinString = "0" + charInBinString;
	}
}

string calculate12LengthBinCodeForChar(const char c)
{
	u32 charInU32 = static_cast<u32>(c);
	u32 binVal = 0;
	string charInBinString;

	while(charInU32 != 0)
	{
		binVal = charInU32%2;
		charInBinString = ((0 == binVal)?"0":"1")+charInBinString;
		charInU32 /= 2;
	}
	completeTo12Bits(charInBinString);

	return charInBinString;
}

void fillArrayDataString(vector<string>& dataStr)
{
	for(u32 i = 0; i < sendingWord.length(); ++i)
	{
		dataStr.push_back(calculate12LengthBinCodeForChar(sendingWord[i]));
	}
}

int main(int argc, char* argv[])
{
	bool rxStarted = false;
	showMainMenu();
	char action = 'n';
	vector<string> dataString;
	cin >> action;
	switch(action)
	{
		case '1':
			showTxMenu();
			fillArrayDataString(dataString);
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

	u32 dataLength = sendingWord.length();
	string word = "";
	const u32 timeDelay = 10;

	bool dataReceivedCorrectly = true;
	if(mainSystem.isInTxMode()) //TxMode
	{
		DataBitset dataToSend;
		for(u32 i = 0; i < dataLength; ++i)
		{
			dataToSend = DataBitset(dataString[i]);
			prepareDataToSend(dataToSend);
			cout << "Sending data: " << dataToSend << " - " << sendingWord[i] << endl;
			mainSystem.dataSender.sendData(dataToSend);
			sf::sleep(sf::milliseconds(timeDelay*4));
			sf::SoundBuffer data2;
			while(true)
			{
				dataReceivedCorrectly = true;
				mainSystem.dataReceiver.receiveData(1);
				data2 = mainSystem.dataReceiver.getReceivedData();
				mainSystem.dataProcessor.processData(data2, true);
				if(mainSystem.dataProcessor.isDataRespReceived()
					 || mainSystem.dataProcessor.isDataRespReceivedPropably())
				{
					if(!mainSystem.dataProcessor.isPositiveRespReceived())
					{
						dataReceivedCorrectly = false;
						mainSystem.dataSender.sendData(dataToSend);
						sf::sleep(sf::milliseconds(timeDelay*4));
					}
					mainSystem.dataProcessor.setDataRespReceived(false);
					mainSystem.dataProcessor.setDataRespReceivedPropably(false);
					if(dataReceivedCorrectly)
					{
						break;
					}
				}
			}
			sf::sleep(sf::milliseconds(timeDelay*4));
		}
		cout << "Data has been sent." << endl;
	}
	else //RxMode
	{
		cout << "\tWaiting for transmission..." << endl;
		sf::SoundBuffer data;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
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
					showDataByte(receivedData);
					word += static_cast<char>(receivedData.to_ulong());
					sf::sleep(sf::milliseconds(timeDelay));
					mainSystem.dataSender.sendPositiveResp();
					sf::sleep(sf::milliseconds(timeDelay*8));
					cout.flush();
				}
				else
				{
					sf::sleep(sf::milliseconds(timeDelay));
					mainSystem.dataSender.sendNegativeResp();
					sf::sleep(sf::milliseconds(timeDelay*8));
				}
				mainSystem.dataProcessor.setCorrectDataSizeReceived(false);
			}
			else if(mainSystem.dataProcessor.isInvalidTxReceived())
			{
				sf::sleep(sf::milliseconds(timeDelay));
				mainSystem.dataSender.sendNegativeResp();
				mainSystem.dataProcessor.setInvalidTxReceived(false);
				sf::sleep(sf::milliseconds(timeDelay*8));
			}
			if(WORD_TO_END == word)
			{
				cout << endl << "\tData has been received." << endl;
				break;
			}
		}
	}
}
