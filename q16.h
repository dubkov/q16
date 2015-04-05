/*
* by Ilya Dubkov
* 05 april 2015
*/

#ifndef _q16_h
#define _q16_h

#include <stdlib.h>
#include <Arduino.h>

#define DISPLAYTIME 500
#define CLKTIME 10
#define COLSNUM 16
#define ROWSNUM 16
#define HALFCOLSNUM 8
#define HALFROWSNUM 8

class q16
{
	public:
		q16(int pinclk, int pinstb, int pinoe, int pinc, int pinb, int pina, int pintd, int pinbd);
		void transferBits(boolean bitToSendTop, boolean bitToSendBottom);
		void transferLines(uint16_t lineToSendTop, uint16_t lineToSendBottom);
		void selectRow(uint8_t rowNumber);
		void displayLine();
		void display(uint16_t picture[16]);
	
	private:
		int _pinclk; 
		int _pinstb; 
		int _pinoe;
		int _pinc;
		int _pinb; 
		int _pina; 
		int _pintd; 
		int _pinbd; 
};

#endif
