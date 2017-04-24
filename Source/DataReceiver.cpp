/*
 * DataReceiver.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/DataReceiver.hpp"

DataReceiver::DataReceiver()
{}

void DataReceiver::receiveData(const u32 recLen)
{
	recorder.recordData(recLen);
	//TODO: setDataToReceivedData
}

string DataReceiver::getReceivedData() const
{
	return receivedData;
}

void DataReceiver::testRecordedSound()
{
	recorder.testRecordedSound();
}
