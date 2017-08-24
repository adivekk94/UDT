/*
 * glo_def.hpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#ifndef DEFINITIONS_GLO_DEF_HPP_
#define DEFINITIONS_GLO_DEF_HPP_

#include "glo_inc.hpp"

typedef unsigned char 	   u8;
typedef char 	   		   		 i8;
typedef unsigned int 	   	 u32;
typedef int 	   	 				 i32;
typedef unsigned long long u64;
typedef long long 				 i64;

const u32 AMPLITUDE = 1024;
const u32 SAMPLE_FREQ = 44100;
const u32 WINDOW_SIZE = 1024;
const u8  BYTE = 8;
const u8  CRC_DIVIDER_LENGTH = 4;
const u8  CRC_LENGTH = 3;
const u8  RESP_LENGTH = 3;
const u32 BEEP_DURATION = 100;
const u8  DATA_SIZE = BYTE + CRC_LENGTH + 1;

const u32 F000 = 17000;
const u32 F001 = 17400;
const u32 F010 = 17800;
const u32 F011 = 18200;
const u32 F100 = 18600;
const u32 F101 = 19000;
const u32 F110 = 19400;
const u32 F111 = 19800;

const u32 FOFFSET = 300;

typedef bitset<CRC_LENGTH> CrcBitset;
typedef bitset<DATA_SIZE>  DataBitset;



enum EMode
{
	ETxMode,
	ERxMode
};


#endif /* DEFINITIONS_GLO_DEF_HPP_ */
