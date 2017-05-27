/*
 * CRC.hpp
 *
 *  Created on: 21.05.2017
 *      Author: adivek
 */

#ifndef HEADERS_CRC_HPP_
#define HEADERS_CRC_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"

class CRC
{
public:
	CRC() : crc(0)
	{}

	void calculateCRC(const bool *byte);
	bool isByteCorrect(const bool *byte);
	u8 getCRC() const;
	void setCRC(const u8 val);
private:
	u8 crc;
};

#endif /* HEADERS_CRC_HPP_ */
