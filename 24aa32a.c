#include "24aa32a.h"

/**
 * @brief      Generates a start condition
 */
void _i2cstart(void)
{
    SDA_TRIS = 0; //ensure this is set to be an output
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
		}// end void bit_start(void)


/**
 * @brief      Generates a stop condition
 */
void _i2cstop(void)
{
    SDA_TRIS = 0;
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
} // end void bit_stop(void)

/**
 * @brief      writes out a bit to I2C
 *
 * @param[in]  data  The data
 */
void _writeBit(unsigned char data)
{
	SDA_TRIS = 0; //make SDA an output
	SCL = 0; //Pull SCL low
	if(data & 0x80) //If the leading bit is a 1
	{
		SDA = 1;
    }
    else
    {
        SDA = 0;
    }
	SCL = 1;
	SCL = 0;
} //end void bit_write(unsigned char *data){

/**
 * @brief      reads in a bit from I2C
 *
 * @param      data  The data
 */
void _readBit(unsigned char *data)
	{
		SDA_TRIS = 1; //make SDA an input
		SCL = 0;
		SCL = 1;
		*data &= 0xFE; //clear trailing bit
		if(SDA) //check data line
	{
		*data |= 0x01; // if data line is high, write a 1 to the end
	}
	SCL = 0;
}


/**
 * @brief      writes a byte out to I2C
 *
 * @param[in]  data  The data to be sent
 *
 * @return     ack status from slave
 */
unsigned char _writeByte(unsigned char data)
{
	unsigned char i; //loop counter
	unsigned char ack = 1; 
	for (int i = 0; i < 8; i++)
	{
		_writeBit(data); //push the data
		data = (unsigned char)(data << 1);
	}
	_readBit(&ack); 
	return ack;
}
/**
 * @brief      reads a byte from I2C
 *
 * @param[in]  ack   The acknowledge
 *
 * @return     { description_of_the_return_value }
 */
unsigned char _readByte(unsigned char ack)
{
	unsigned char ret = 0;
	for (int i = 0; i < 8; i++)
	{
		ret = (unsigned char)(ret << 1);
		_readBit(&ret);

	}
	_writeBit(ack); //gives the option to respond with an ACK or NAK. (needed for sequential reads)
	return(ret);
}

/**
 * @brief      Polls for an acknowledgment from the EEPROM to inidicate that it is finshed with a
 *             write cycle
 */
void ACK_Poll(void)
{
	unsigned char ackstat = 1;

	do
	{
		_i2cstart();
		ackstat = _writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); 
	} while(ackstat == 1); //NACK response
	_i2cstop();
}

/**
 * @brief      Writes data byte to the EEPROM address and then waits for the device to achnowledge
 *             that it is complete. This forces a full page write, so it's better to use
 *             eeprom_writePage()
 *
 * @param[in]  address  The 16 bit address
 * @param[in]  data     The data byte
 */
void eeprom_writeByte(unsigned int address, unsigned char data)
{
    unsigned char addressmsb = (unsigned char)(address >> 8);
    unsigned char addresslsb = (unsigned char)address;
	_i2cstart();
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //trailing 0 commands a write cycle
	_writeByte(addressmsb); //write the MSB address bits
	_writeByte(addresslsb); //write the LSB address bits
	_writeByte(data); //write out the data byte;
	_i2cstop();
	ACK_Poll(); //wait for the EEPROM to finish its write cycle. 
}

/**
 * @brief      Writes a page worth of data (32 bytes) out to the EEPROM
 *
 * @param[in]  address  The 16 bit address
 * @param      data     The data byte array pointer (16 elements)
 *
 * @return     If the address is not the beginning of the page, returns 
 */
void eeprom_writePage(unsigned int address, unsigned char *data)
{
    unsigned char addressmsb = (unsigned char)address >> 8;
    unsigned char addresslsb = (unsigned char)address;
	if(address % 0x20 != 0) return; //address is not the start of a page
	_i2cstart();
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //trailing 0 commands a write cycle
	_writeByte(addressmsb); //write the MSB address bits
	_writeByte(addresslsb); //write the LSB address bits
	for (int i = 0; i < 32; i++)
	{
	_writeByte(data[i]); //write out the data byte;
	}
	_i2cstop();
	ACK_Poll(); //wait for the EEPROM to finish its write cycle. 
}

/**
 * @brief      reads a byte from EEPROM at the specified address and writes it to the address
 *             provided by the data pointer.
 *
 * @param[in]  address  The 16 bit EEPROM address
 * @param      data     The data byte pointer
 */
void eeprom_readByte(unsigned int address, unsigned char *data)
{
    unsigned char addressmsb = (unsigned char)(address >> 8);
    unsigned char addresslsb = (unsigned char)address;
	//first we set the address to be read
	_i2cstart();
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //start a write cycle to set the address
	_writeByte(addressmsb);
	_writeByte(addresslsb);
	_i2cstart(); //this terminates the write cycle
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x01); //start a read cycle at the current address
	*data = _readByte(NAKBIT);
	_i2cstop();
  
}

/**
 * @brief      reads the entire contents of the EEPROM, one byte at a time, to data.
 *
 * @param      data  The data byte
 */
void eeprom_readMem(unsigned char *byte)
{
    _i2cstart();
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //start a write cycle to set the address
	_writeByte(0);
	_writeByte(0xFF);
	_i2cstart(); //this terminates the write cycle
	_writeByte(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x01); //start a read cycle at the current address
	for (unsigned short i = 0; i < 0xFFF; i++)
	{
        *byte = _readByte(ACKBIT);
	}
    *byte = _readByte(NAKBIT);
    _i2cstop();
}

