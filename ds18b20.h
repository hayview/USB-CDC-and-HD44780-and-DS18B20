#ifndef _DS18B20_H
#define _DS18B20_H

#include <p18cxxx.h>

//DS18B20 ROM Command Set
#define DS18B20_SEARCH_ROM			0xF0
#define DS18B20_READ_ROM			0x33
#define DS18B20_MATCH_ROM			0x55
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_ALARM_SEARCH		0xEC

//DS18B20 Resolution Set
#define DS18B20_RESOLUTION_9_BIT 	0b00011111			
#define DS18B20_RESOLUTION_10_BIT	0b00111111
#define DS18B20_RESOLUTION_11_BIT	0b01011111
#define DS18B20_RESOLUTION_12_BIT	0b01111111

//DS18B20 Function Command Set
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD		0xBE
#define DS18B20_WRITE_SCRATCHPAD	0x4E
#define DS18B20_COPY_SCRATCHPAD		0x48	
#define DS18B20_RECALL_E2			0xB8
#define DS18B20_READ_POWER_SUPPLY	0xB4

//System Status
#define DS18B20_NO_DEVICE			0x01
#define DS18B20_PRESENT				0x02

unsigned int DS18B20_ReadTemperature(void);
void DS18B20_RawTempToBCD(char *temp_BCD, char *BCD_length);
void testbuffer(char *buffer);
#endif





