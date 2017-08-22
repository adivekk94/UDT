/*
 * System.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_SYSTEM_HPP_
#define HEADERS_SYSTEM_HPP_

#include "../Headers/DataSender.hpp"
#include "../Headers/DataReceiver.hpp"
#include "../Headers/DataProcessor.hpp"
#include "../Headers/CRC.hpp"
#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"

class System
{
public:
	System();
	bool isInTxMode() const;
	bool isInRxMode() const;
	void setTxMode();
	void setRxMode();
    void operator=(const System& sys);

	DataSender    dataSender;
	DataReceiver  dataReceiver;
	DataProcessor dataProcessor;
private:
	EMode mode;
};

#endif /* HEADERS_SYSTEM_HPP_ */
