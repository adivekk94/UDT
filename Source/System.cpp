/*
 * System.cpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#include "../Headers/System.hpp"

System::System()
	: mode(ERxMode)
{}

bool System::isInTxMode() const
{
	return (ETxMode == mode);
}

bool System::isInRxMode() const
{
	return (ERxMode == mode);
}

void System::setTxMode()
{
	mode = ETxMode;
}

void System::setRxMode()
{
	mode = ERxMode;
}


