#include "1wire.h"

void OW_DriveLow(void);
void OW_DriveHigh(void);
void OW_WriteBit(unsigned char OW_data_bit);

void OW_DriveLow(void)
{
	OW_PIN_DIRECTION=OW_OUTPUT;
	OW_WRITE_PIN=0;
}

void OW_DriveHigh(void)
{
	OW_PIN_DIRECTION=OW_OUTPUT;
	OW_WRITE_PIN=1;	
}
	
void OW_WriteBit(unsigned char OW_data_bit)
{
	if(OW_data_bit)
	{
		OW_DriveLow();
		delay6MicroSecond();
		OW_DriveHigh();
		delay64MicroSecond();
	}
	else
	{
		OW_DriveLow();
		delay60MicroSecond();
		OW_DriveHigh();
		delay10MicroSecond();
	}
}

void OW_WriteByte(unsigned char OW_data_byte)
{
	char i;
	
	for (i=0;i<8;i++)
	{
		OW_WriteBit(OW_data_byte&0x01);
		OW_data_byte=OW_data_byte>>1;
	}
}

		
unsigned char OW_ReadBit(void)
{
	unsigned char OW_data_bit=0;

	OW_DriveLow();
	delay6MicroSecond();
	OW_DriveHigh();
	delay9MicroSecond();
		
	OW_PIN_DIRECTION=OW_INPUT;
	
	OW_data_bit=OW_READ_PIN;
	
	delay55MicroSecond();
	
	return OW_data_bit;
}

unsigned char OW_ReadByte(void)
{
	unsigned char OW_data_byte=0;
	unsigned char i;
	
	for (i=0;i<8;i++)
	{
		OW_data_byte=OW_data_byte>>1;
		
		if (OW_ReadBit()==1) OW_data_byte=OW_data_byte|0x80;
	}
	
	return OW_data_byte;
}

unsigned char OW_ResetPulse(void)
{
	unsigned char presence_detect;
	
	OW_DriveLow();
	delay480MicroSecond();
	
	OW_DriveHigh();
	delay70MicroSecond();

	OW_PIN_DIRECTION=OW_INPUT;
	if(OW_READ_PIN==0) presence_detect=1;	// device present
	if(OW_READ_PIN==1) presence_detect=0;	// no device present
	
	delay410MicroSecond();
	
	OW_DriveHigh();
	
	return presence_detect;
}
