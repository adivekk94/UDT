/*
 * main.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/main.hpp"
#include "tools/TextPlot.h"
#include "transform/Fft.h"


int main()
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

	if(mainSystem.isInTxMode()) //TxMode
	{
//		mainSystem.dataSender.setDataToSend(data);
		bool dataSend[] = {true, false, false, true, false, true, true, false};
		for(int j = 0; j < 1; ++j)
		{
			for(int i = 0; i < 8; ++i)
			{
				mainSystem.dataSender.sendData(dataSend[i]);
			}
			cout << "Send data: 10010110 " << endl;
		}
		mainSystem.dataSender.sendData(false); //only for check last bit proper
	}
	else //RxMode
	{
		const sf::SoundBuffer& data = mainSystem.dataReceiver.getReceivedData();
		while(true)
		{
			mainSystem.dataReceiver.receiveData(1);
			mainSystem.dataProcessor.processData(data);
		}
	}

	cout << "End of program." << endl;
	return 0;
}
