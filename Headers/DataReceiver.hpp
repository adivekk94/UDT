/*
 * DataReceiver.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_DATARECEIVER_HPP_
#define HEADERS_DATARECEIVER_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"
#include "../Headers/Recorder.hpp"

class DataReceiver
{
public:
	DataReceiver();
	void receiveData(const u32 recLen);
	string getReceivedData() const;
	void testRecordedSound();
private:
	Recorder recorder;
	string   receivedData; //TODO: tmp string, will be processed data
};

#endif /* HEADERS_DATARECEIVER_HPP_ */
