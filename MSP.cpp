#include "MSP.h"

MSP::MSP()
{
	
}

void MSP::writeMSPData(MSP_COMMAND command, uint16_t data[12], uint8_t length)
{	
	uint8_t i = 0;
	checksum = 0;
	
	buffer[0] = (length * 2 & 0xFF);
	checksum ^= (length * 2 & 0xFF);
	
	buffer[1] = (command & 0xFF);
	checksum ^= (command & 0xFF);
	
	if(length > 0)
	{
		uint8_t msb = 0;
		uint8_t lsb = 1;
		
		for(i = 0; i < length; i++)
		{
			buffer_2[msb] = (data[i] & 0xFF);
			buffer_2[lsb] = (data[i] >> 8);
			
			msb += 2;
			lsb += 2;
		}
		
		for(i = 0; i < length * 2; i++)
		{
			buffer[2 + i] = (buffer_2[i] & 0xFF);
			checksum ^= (buffer_2[i] & 0xFF);
		}
	}
	
	buffer[length * 2 + 2] = checksum;
	
	Serial.write("$M<", 3);
    for(i = 0; i < length * 2 + 3; i++)
		Serial.write(buffer[i]);
}

MSP_COMMAND MSP::readMSPData(uint16_t data[12])
{
	if(Serial.available() > 3)
	{
		if (read8() == '$')
			if (read8() == 'M')
				if (read8() == '>')
				{
					uint8_t data_length = read8();
					MSP_COMMAND command = read8();
					checksum = 0;
					
					switch(command)
					{
						case MSP_IDENT:
							
							break;
						case MSP_STATUS:
							break;
						case MSP_RC:
							
							// ROLL/PITCH/YAW/THROTTLE/AUX1/AUX2/AUX3AUX4
							data[0] = read16();
							data[1] = read16();
							data[2] = read16();
							data[3] = read16();
							data[4] = read16();
							data[5] = read16();
							data[6] = read16();
							data[7] = read16();
							
							checksum = read8();
							break;
						default:
							while(data_length > 0)
							{
								read8();
								data_length--;
							}
							
							checksum = read8();
							break;
					}
					
					return command;
				}
	}
	
	return MSP_ERROR;
}

uint8_t MSP::read8()  
{
	uint8_t temp = Serial.read()
	checksum ^= c;
	
	return (temp & 0xFF);
}

uint16_t MSP::read16() 
{
  uint16_t temp = read8();
  temp += (uint16_t)read8() << 8;
  return temp;
}

uint32_t MSP::read32() 
{
  uint32_t temp = read16();
  temp += (uint32_t)read16() << 16;
  return temp;
}




