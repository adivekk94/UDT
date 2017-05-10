/*
 * glo_def.hpp
 *
 *  Created on: 12.04.2017
 *      Author: adivek
 */

#ifndef DEFINITIONS_GLO_DEF_HPP_
#define DEFINITIONS_GLO_DEF_HPP_

typedef unsigned char 	   u8;
typedef unsigned int 	   u32;
typedef unsigned long long u64;

const u32 AMPLITUDE = 8192;
const u32 SAMPLE_FREQ = 44100;
const u32 WINDOW_SIZE = 1024;

enum EMode
{
	ETxMode,
	ERxMode
};

static EMode systemMode = ERxMode;

#endif /* DEFINITIONS_GLO_DEF_HPP_ */
