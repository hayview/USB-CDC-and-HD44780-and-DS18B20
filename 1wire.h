// MAXIM APPLICATION NOTE 126
#ifndef _OW_H
#define _OW_H

#include <p18cxxx.h>
#include <delays.h>

// PIN DEFINITION
#define OW_PIN_DIRECTION 	  TRISCbits.RC2
#define OW_WRITE_PIN  		  LATCbits.LATC2
#define OW_READ_PIN			  PORTCbits.RC2
#define OW_INPUT			  1
#define OW_OUTPUT			  0

// DELAY DEFINITION
#define delay6MicroSecond()  {Delay10TCYx(7); Delay1TCY(); Delay1TCY();}
#define delay9MicroSecond()	 {Delay10TCYx(10); Delay1TCY(); Delay1TCY();\
							  Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY();}
#define delay10MicroSecond()  Delay10TCYx(12)	
#define delay55MicroSecond()  Delay10TCYx(66)
#define delay60MicroSecond()  Delay10TCYx(72)
#define delay64MicroSecond() {Delay10TCYx(76); Delay1TCY(); Delay1TCY();\
							  Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY();}
#define delay70MicroSecond()  Delay10TCYx(84)
#define delay410MicroSecond(){Delay100TCYx(49); Delay10TCYx(2);}
#define delay480MicroSecond(){Delay100TCYx(57); Delay10TCYx(6);}

void OW_WriteByte(unsigned char OW_data_byte);
unsigned char OW_ReadBit(void);
unsigned char OW_ReadByte(void);
unsigned char OW_ResetPulse(void);

#endif
