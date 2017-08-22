/*
 * DataProcessor.hpp
 *
 *  Created on: 14.04.2017
 *      Author: adivek
 */

#ifndef HEADERS_DATAPROCESSOR_HPP_
#define HEADERS_DATAPROCESSOR_HPP_

#include "../Definitions/glo_def.hpp"
#include "../Definitions/glo_inc.hpp"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

#define AMP_THRESHOLD 1000000

class DataProcessor
{
public:
	DataProcessor();
	void processData(const sf::SoundBuffer& data);
	bool getCalculatedParityBit(const DataBitset& data, const bool forCalc = true);
	bool isParityCorrect(const DataBitset& data);
	void calculateFoundFrequency();
	u32 getFoundFrequency() const;
	void resetHighestFftAmplitudePosition();
	void calculateHighestFFTPosition(Aquila::SpectrumType& spectrum);
	void convertDataToArray(const u64 			   		 samplesAmount,
													const sf::SoundBuffer& data,
													double* 				   			 convertedData);
	string getDataStr() const;
	DataBitset getReceivedData() const;
	bool isDataRespReceived() const;
	bool isDataRespReceivedPropably() const;
	bool isByteReceived() const;
	bool isCrcRespReceived() const;
	bool isCrcReceived() const;
	bool isInvalidTxReceived() const;
	void setCrcReceived(const bool state);
	void setCrcRespReceived(const bool state);
	void setDataReceived(const bool state);
	void setDataRespReceived(const bool state);
	void setDataRespReceivedPropably(const bool state);
	void setInvalidTxReceived(const bool state);
	void activateCrcExpected();
	void deactivateCrcExpected();
	void activateCrcRespExpected();
	void deactivateCrcRespExpected();
	void activateDataExpected();
	void deactivateDataExpected();
	void activateDataRespExpected();
	void deactivateDataRespExpected();
	bool isPositiveRespReceived() const;
	bool isPositiveRespReceivedPropably() const;
	bool isCrcRespExpectedActive() const;
	bool isDataRespExpectedActive() const;
	bool isCorrectDataSizeReceived() const;
	void setCorrectDataSizeReceived(const bool state);
private:
	u32 highestFftAmplitudePosition;
	u32 foundFrequency;
	string dataStr;
	DataBitset receivedData;
	bool correctDataSizeReceived;
	u8 currentBit;
	bool dataRespReceived;
	bool dataRespReceivedPropably;
	bool dataReceived;
	bool crcRespReceived;
	bool crcReceived;
	bool invalidTxReceived;
	bool crcExpected;
	bool crcRespExpected;
	bool dataExpected;
	bool dataRespExpected;
};

#endif /* HEADERS_DATAPROCESSOR_HPP_ */
