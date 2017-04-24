/*
 * main.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/main.hpp"

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
//		sf::SoundBuffer sb;
//		sb.loadFromFile("Source/choir.wav");
//		sf::Sound sound(sb);
//		sound.play();
//		//TODO:check if it works
//		while(2 == sound.getStatus())
//		{
//
//		}

	if(mainSystem.isInTxMode()) //TxMode
	{
		const string data = "Test";
		mainSystem.dataSender.setDataToSend(data);
		mainSystem.dataSender.sendData();
		cout << "Data: " << data << "\nData has been send." << endl;
	}
	else //RxMode
	{
		mainSystem.dataReceiver.receiveData(3000);
		const string data = mainSystem.dataReceiver.getReceivedData();
		cout << "Data has been received.\nData: " << data << endl;
		mainSystem.dataProcessor.processData(data);
		mainSystem.dataReceiver.testRecordedSound();
	}

	return 0;
}
