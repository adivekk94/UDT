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
	void sendThreeBits(const u32 threeBits);
	void sendData(const bitset<DATA_SIZE> data);
	void sendPositiveResp();
	void sendNegativeResp();
private:
	Beeper beeper;
	u32 frequencies[8];
};



#endif /* HEADERS_DATASENDER_HPP_ */
