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
#include "../aquila/transform/FftFactory.h"
#include "../aquila/source/generator/SineGenerator.h"

class DataProcessor
{
public:
	DataProcessor();
	void processData(const sf::SoundBuffer& data,
									 const bool expectResp = false);
	bool getCalculatedParityBit(const DataBitset& data, const bool forCalc = true);
	bool isParityCorrect(const DataBitset& data);
	void calculateFoundFrequency();
	u32 getFoundFrequency() const;
	void resetHighestFftAmplitudePosition();
	void calculateHighestFFTPosition(Aquila::SpectrumType& spectrum);
	void convertDataToArray(const u64 			   		 samplesAmount,
													const sf::SoundBuffer& data,
													double* 				   			 convertedData);
	DataBitset getReceivedData() const;
	bool isDataRespReceived() const;
	bool isDataRespReceivedPropably() const;
	bool isInvalidTxReceived() const;
	void setDataRespReceived(const bool state);
	void setDataRespReceivedPropably(const bool state);
	void setInvalidTxReceived(const bool state);
	bool isPositiveRespReceived() const;
	bool isCorrectDataSizeReceived() const;
	void setCorrectDataSizeReceived(const bool state);
private:
	u32 highestFftAmplitudePosition;
	u32 foundFrequency;
	DataBitset receivedData;
	bool correctDataSizeReceived;
	u8 currentBit;
	bool dataRespReceived;
	bool dataRespReceivedPropably;
	bool invalidTxReceived;
};

#endif /* HEADERS_DATAPROCESSOR_HPP_ */
