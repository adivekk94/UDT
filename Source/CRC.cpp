/*
 * CRC.cpp
 *
 *  Created on: 21.05.2017
 *      Author: adivek
 */

#include "../Headers/CRC.hpp"

void CRC::calculateCRC(DataBitset data)
{
	const u8 numOfBits = 11;
	const bitset<CRC_DIVIDER_LENGTH> crcDivider("1101");
	u32 diff = numOfBits-CRC_DIVIDER_LENGTH, currentPos = 0;
	u32 maxPosition = numOfBits-CRC_DIVIDER_LENGTH;
//	cout << "Extracted CRC: " << data[8] << data[9] << data[10] << endl;
	while(diff > 0)
	{
		for(u32 i = currentPos; i <= maxPosition; ++i)
		{
			currentPos = i;
			if(!data[i])
			{
				continue;
			}
			else
			{
				for(u32 j = currentPos, k = 0; j < currentPos+CRC_DIVIDER_LENGTH; ++j, ++k)
				{
					data[j] = data[j] ^ crcDivider[k];
				}
				break;
			}
		}
		diff = numOfBits-CRC_DIVIDER_LENGTH-currentPos;
	}
	crc.set(2, data[numOfBits-1]);
	crc.set(1, data[numOfBits-2]);
	crc.set(0, data[numOfBits-3]);
}

bool CRC::isByteCorrect(DataBitset data)
{
	calculateCRC(data);

	if(!crc[0] && !crc[1] && !crc[2])
	{
		return true;
	}
	return false;
}

bitset<CRC_LENGTH> CRC::getCRC() const
{
	return crc;
}

void CRC::setCRC(const u8 val)
{
	crc = val;
}

