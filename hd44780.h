#ifndef HD44780_H
#define HD44780_H

#include <p18cxxx.h>
#include "delay.h"

#define HD44780_CLEAR_DISPLAY	0b00000001	//82us-1.64ms 
#define HD44780_RETURN_HOME		0b00000010	//40us-1.64ms

#define HD44780_REGISTER_COMMAND		0x10
#define HD44780_REGISTER_DATA			0x01

/*
#define HD44780_clearDisplay	0b00000001	//82us-1.64ms 
#define HD44780_returnHome		0b0000001*	//40us-1.64ms
*/

/*
#define HD44780_EN_PINteryModeSet	0b 0 0 0 0 0 1 I/D S	//40us-1.64ms

I/D = 1: Increment
I/D = 0: Decrement
S 	= 1: Accompanies display shift
*/

/*
#define HD44780_displayOnOff	0b 0 0 0 0 1 D C B	//40us
Sets entire display (D) on/off,
cursor on/off (C), and
blinking of cursor position
character (B).
*/

/*
#define HD44780_cursorDisplayShift 0b 0 0 0 1 S/C R/L * *	//40us

S/C = 1: Display shift
S/C = 0: Cursor move
R/L = 1: Shift to the right
R/L = 0: Shift to the left
*/

/*
#define HD44780_functionSet		   0b 0 0 1 DL N F * *	//40us
DL 	= 1: 8 bits, DL = 0: 4 bits
N 	= 1: 2 lines, N = 0: 1 line
F 	= 1: 5'10 dots, F = 0: 5'8 dots
*/

/*
#define HD44780_setCGRAMAddress	   0b01xxxxxx	//40us
#define HD44780_setDDRAMAddress	   0b1xxxxxxx	//40us
*/

/*
DDRAM: Display data RAM
CGRAM: Character generator RAM
ACG:   CGRAM address
ADD:   DDRAM address (corresponds to cursor address)
AC:    Address counter used for both DD and CGRAM addresses
*/

#define HD44780_initPinIO()		   {TRISBbits.RB4=0; TRISBbits.RB5=0; TRISD=0x00;}
#define HD44780_EN_PIN				LATBbits.LATB5
#define HD44780_RS_PIN				LATBbits.LATB4
#define HD44780_DATA_PORT			LATD

void HD44780_Init(void); 
void HD44780_WriteROMString(const rom char *s);
void HD44780_WriteRAMString(char *s);
void HD44780_WriteNumber(long number);
void HD44780_GoToPoint(char row, char col);
void HD44780_AddCharacter(char addr, const rom char *pattern);
void HD44780_WriteData(char dat);
void HD44780_ClearDisplay(void);
void HD44780_ReturnHome(void);

#endif

