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

	const u32 numOfBytes = atoi(argv[1]);
	cout << numOfBytes << endl;
	if(mainSystem.isInTxMode()) //TxMode
	{
		bool dataSend[] = {1, 1, 0, 0, 1, 0, 0, 1};
		for(int j = 0; j < numOfBytes; ++j)
		{
			for(int i = 0; i < 8; ++i)
			{
				mainSystem.dataSender.sendData(dataSend[i]);
			}
			cout << "Send data: 11001001" << endl;
		}
		sf::sleep(sf::milliseconds(10));
		mainSystem.dataSender.sendData(false); //only for check last bit proper
	}
	else //RxMode
	{
		sf::SoundBuffer data;
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
			data = mainSystem.dataReceiver.getReceivedData();
			mainSystem.dataProcessor.processData(data);
		}
	}

	cout << "End of program." << endl;
	return 0;
}
