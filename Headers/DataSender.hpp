/*
 * DataSender.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_DATASENDER_HPP_
#define HEADERS_DATASENDER_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"
#include "Beeper.hpp"

class DataSender
{
public:
	DataSender();
	void sendData(const bool zero);
	void setDataToSend(const u32 frequency, const u32 duration);
	void getData() const;
private:
	Beeper beeper;
	double oneFreq;
	double zeroFreq;
};



#endif /* HEADERS_DATASENDER_HPP_ */
