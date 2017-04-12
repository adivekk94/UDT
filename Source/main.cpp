/*
 * main.cpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#include "../Headers/main.hpp"

int main()
{
	Beeper beeper(SAMPLE_FREQ);
	beeper.beep(15000, 50);
	beeper.beep(1000, 50);

	return 0;
}
