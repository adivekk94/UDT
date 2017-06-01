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

	void calculateCRC(DataBitset data);
	bool isByteCorrect(DataBitset data);
	bitset<CRC_LENGTH> getCRC() const;
	void setCRC(const u8 val);
private:
	bitset<CRC_LENGTH> crc;
};

#endif /* HEADERS_CRC_HPP_ */
