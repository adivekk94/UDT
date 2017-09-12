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
}

const sf::SoundBuffer DataReceiver::getReceivedData() const
{
	return recorder.getBuffer();
}
