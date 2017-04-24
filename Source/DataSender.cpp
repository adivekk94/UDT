/*
 * DataSender.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataSender.hpp"

DataSender::DataSender()
{

}

void DataSender::sendData()
{
//	beeper.beep(16500, 5000); //TODO: change to proper data
	beeper.beep(18000, 1000);
}

void DataSender::setDataToSend(const string data)
{
	dataToSend = data;
}

string DataSender::getData() const
{
	return dataToSend;
}


