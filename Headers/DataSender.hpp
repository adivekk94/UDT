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

enum EBitsData
{
	EZeroZero,
	EZeroOne,
	EOneZero,
	EOneOne
};

class DataSender
{
public:
	DataSender();
	void sendTwoBits(const EBitsData twoBits);
	void sendData(const bitset<DATA_SIZE> data);
	void sendPositiveResp();
	void sendNegativeResp();
	void setDataToSend(const u32 frequency, const u32 duration);
	void getData() const;
private:
	Beeper beeper;
	u32 frequencies[4];
};



#endif /* HEADERS_DATASENDER_HPP_ */
