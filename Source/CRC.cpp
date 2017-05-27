/*
 * CRC.cpp
 *
 *  Created on: 21.05.2017
 *      Author: adivek
 */

#include "../Headers/CRC.hpp"

void CRC::calculateCRC(const bool *byte)
{
	const u8 numOfBits = 11;
	const u8 crcDivider[CRC_DIVIDER_LENGTH] = {1, 0, 1, 1};
	bool extByte[numOfBits];
	memcpy(extByte, byte, BYTE);
	memset(extByte+BYTE, 0, CRC_LENGTH);
	u32 diff = numOfBits-CRC_DIVIDER_LENGTH, currentPos = 0;
	while(diff > 0)
	{
		for(u32 i = currentPos; i <= numOfBits-CRC_DIVIDER_LENGTH; ++i)
		{
			currentPos = i;
			if(!extByte[i])
			{
				continue;
			}
			else
			{
				for(u32 j = currentPos, k = 0; j < currentPos+CRC_DIVIDER_LENGTH; ++j, ++k)
				{
					extByte[j] = extByte[j] ^ crcDivider[k];
				}
				break;
			}
		}
		diff = numOfBits-CRC_DIVIDER_LENGTH-currentPos;
	}
	crc = extByte[numOfBits-1]*1 + extByte[numOfBits-2]*2 + extByte[numOfBits-3]*4;
}

bool CRC::isByteCorrect(const bool *byte)
{
	const u8 numOfBits = 11;
	const u8 crcDivider[4] = {1, 0, 1, 1};
	bool extByte[numOfBits];
	memcpy(extByte, byte, 8);
	bool crcBits[CRC_LENGTH];
	u8 tmpCrc = crc;
	for(u32 i = 0; i < CRC_LENGTH; ++i)
	{
		crcBits[i] = tmpCrc%2;
		tmpCrc /= 2;
	}
	extByte[8] = crcBits[0];
	extByte[9] = crcBits[1];
	extByte[10] = crcBits[2];
//	cout << "CRC check" << crcBits[0] << crcBits[1] << crcBits[2] << endl;
	int diff = numOfBits-CRC_DIVIDER_LENGTH, currentPos = 0;
	while(diff > 0)
	{
		for(u8 i = currentPos; i <= numOfBits-CRC_DIVIDER_LENGTH; ++i)
		{
			currentPos = i;
			if(!extByte[i])
			{
				continue;
			}
			else
			{
				for(u8 j = currentPos, k = 0; j < currentPos+CRC_DIVIDER_LENGTH; ++j, ++k)
				{
					extByte[j] = extByte[j] ^ crcDivider[k];
				}
				break;
			}
		}
		diff = numOfBits-CRC_DIVIDER_LENGTH-currentPos;
	}
	u8 crcResult[CRC_LENGTH];
	memcpy(crcResult, extByte+BYTE+1, CRC_LENGTH);
	tmpCrc = extByte[10]*1 + extByte[9]*2 + extByte[8]*4;
//		cout << "After check crc = " << (u32)tmpCrc << endl;
	if(0 == tmpCrc)
	{
		return true;
	}
	return false;
}

u8 CRC::getCRC() const
{
	return crc;
}

void CRC::setCRC(const u8 val)
{
	crc = val;
}

