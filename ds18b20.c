#include "ds18b20.h"
#include "1wire.h"

/*
Decimal point table - represent the floating point in integer
*/
rom unsigned int ds18b20_decimal[16]={
	0,
	625,
	1250,
	1875,
	2500,
	3125,
	3750,
	4375,
	5000,
	5625,
	6250,
	6875,
	7500,
	8125,
	8750,
	9375
	};
	
unsigned char DS18B20_Init(void);

unsigned char DS18B20_Init(void)
{
	if(OW_ResetPulse()) return DS18B20_PRESENT;
	else return DS18B20_NO_DEVICE;	
}

unsigned int DS18B20_ReadTemperature(void)
{
	unsigned char temp_lsb, temp_msb;
	unsigned int temp=0;
	
	if(DS18B20_Init()==DS18B20_PRESENT)
	{
		OW_WriteByte(DS18B20_SKIP_ROM);
		OW_WriteByte(DS18B20_CONVERT_T);
		while(!OW_ReadBit());
		
		OW_ResetPulse();
		OW_WriteByte(DS18B20_SKIP_ROM);
		OW_WriteByte(DS18B20_READ_SCRATCHPAD);
			
		temp_lsb=OW_ReadByte();
		temp_msb=OW_ReadByte();
		
		temp=(unsigned int)temp_msb;
		temp=temp<<8;
		temp=temp&0xFF00;
		temp=temp+temp_lsb;
	}
	return temp;
}

void DS18B20_RawTempToBCD(char *temp_BCD, char *BCD_length)
{
	char temp_storage[9];
	char i,j,k;
	char BCD_data_pointer=0;
	unsigned int temp, temp_int, temp_decimal;
	
	temp=DS18B20_ReadTemperature();
	
	if((temp>=0x0000)&&(temp<=0x07D0))				//positive temperature range
	{
		temp_int=temp>>4;							//remove decimal number
		temp_int=temp_int&0x00FF;
		temp_decimal=ds18b20_decimal[(temp&0x000F)];//obtain decimal number
	}
	else if((temp>=0xFC90)&&(temp<=0xFFF8))			//negative temperature range
	{
		temp=~temp;									//reverse the 2nd complement
		temp=temp+1;								//change it to positive value
		temp_int=temp>>4;							//remove decimal number
		temp_int=temp_int&0x00FF;
		temp_decimal=ds18b20_decimal[(temp&0x000F)];//get the decimal number	
		temp_storage[BCD_data_pointer]='-';
		BCD_data_pointer++;							//point to new blank space to store new data
	}
	
	//calculate the size of temp_int
	if(temp_int<10) j=1;
	else if(temp_int>=10 && temp_int<100) j=2;
	else if(temp_int>100) j=3;
	
	//convert temp_int to bcd
	for(i=(BCD_data_pointer+j-1);i>=BCD_data_pointer;i--)
	{
		temp_storage[i]=(temp_int%10)+0x30; 
		temp_int=temp_int/10;
	}						
	
	BCD_data_pointer=BCD_data_pointer+j;			//point to new blank space
	temp_storage[BCD_data_pointer]='.';				//store the dot

	//process the decimal point
	for(j=(BCD_data_pointer+4);j>BCD_data_pointer;j--)
	{
		temp_storage[j]=(temp_decimal%10)+0x30;
		temp_decimal=temp_decimal/10;
	}

	BCD_data_pointer=BCD_data_pointer+4;

	for(k=0;k<=BCD_data_pointer;k++)
	{
		*temp_BCD=temp_storage[k];
		 temp_BCD++;
	}
	
	*temp_BCD=0;
	*BCD_length=(BCD_data_pointer+1);
}

void testbuffer(char *buffer)
{
	char i=0;
	while(i<5)	
	{
		*buffer=*buffer+1;
		buffer++;
		i++;
	}
}