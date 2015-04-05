/*
* by Ilya Dubkov
* 05 april 2015
*/

#include <stdlib.h>
#include "q16.h"
#include <Arduino.h>

q16::q16(int pinclk, int pinstb, int pinoe, int pinc, int pinb, int pina, int pintd, int pinbd)
{
	pinMode(_pinclk, OUTPUT);
	pinMode(_pinstb, OUTPUT);
	pinMode(_pinoe, OUTPUT);
	pinMode(_pinc, OUTPUT);
	pinMode(_pinb, OUTPUT);
	pinMode(_pina, OUTPUT);
	pinMode(_pintd, OUTPUT);
	pinMode(_pinbd, OUTPUT);

	_pinclk = pinclk; 
	_pinstb = pinstb;
	_pinoe = pinoe;
	_pinc = pinc; 
	_pinb = pinb;
	_pina = pina;
	_pintd = pintd;
	_pinbd = pinbd;
	
}

void q16::transferBits(boolean bitToSendTop, boolean bitToSendBottom){
	digitalWrite(_pintd,bitToSendTop);
	digitalWrite(_pinbd,bitToSendBottom);
	digitalWrite(_pinclk,HIGH);
	delayMicroseconds(CLKTIME);
	digitalWrite(_pinclk,LOW);
	delayMicroseconds(CLKTIME);
}

void q16::transferLines(uint16_t lineToSendTop, uint16_t lineToSendBottom){
	digitalWrite(_pinstb,LOW);
	for(int i=0; i<HALFROWSNUM; i++) 
		transferBits(lineToSendTop&(1<<i),lineToSendBottom&(1<<i));
	for(int i=0; i<HALFROWSNUM; i++) 
		transferBits(lineToSendTop>>HALFCOLSNUM&(1<<i),lineToSendBottom>>HALFCOLSNUM&(1<<i));
	digitalWrite(_pinstb,HIGH);
}

void q16::selectRow(uint8_t rowNumber){
	digitalWrite(_pina,rowNumber&1);
	digitalWrite(_pinb,rowNumber&2);
	digitalWrite(_pinc,rowNumber&4);
}

void q16::displayLine(){
	digitalWrite(_pinoe,LOW);
	delayMicroseconds(DISPLAYTIME);
	digitalWrite(_pinoe,HIGH);
}

void q16::display(uint16_t picture[16]){
	for (int j=0;j<HALFROWSNUM;j++){
		selectRow(j);
		transferLines(picture[j],picture[j+HALFROWSNUM]);
		displayLine();
	}
}
