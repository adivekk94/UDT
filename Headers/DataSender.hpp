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
	void sendData();
	void setDataToSend(const string data);
	string getData() const;
private:
	Beeper beeper;
	string dataToSend;
};



#endif /* HEADERS_DATASENDER_HPP_ */
