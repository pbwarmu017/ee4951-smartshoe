#include "24aa32a.h"

//
// @brief      Initializes the I2C peripheral
//
void I2C_Initialize(void)
{
    SSP1STAT = 0x00;
    SSP1CON1 = 0x08;
    SSP1CON2 = 0x00;
    SSP1ADD = 0x13;
    PIR1bits.SSP1IF = 0;
    SSP1CON1bits.SSPEN = 1;
}
void ACK_Poll(void)
{
	do
	{
		I2C_MasterStart();

	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); 
	} while(NACKFLAG); //NACK response
	I2C_MasterStop();
}

/**
 * @brief      Writes data byte to the EEPROM address and then waits for the device to achnowledge
 *             that it is complete. This forces a full page write, so it's better to use
 *             eeprom_writePage()
 *
 * @param[in]  address  The 16 bit address
 * @param[in]  data     The data byte
 */

void I2C_WaitForCompletion(void)
{
	while(!PIR1bits.SSP1IF)
        ;
    PIR1bits.SSP1IF = 0;
}
void I2C_MasterStart(void)
{
    SSP1CON2bits.SEN = 1;
    I2C_WaitForCompletion();
  }

void I2C_MasterStop(void)
{
    SSP1CON2bits.PEN = 1;
    I2C_WaitForCompletion();
}

void I2C_MasterWrite(unsigned char data)
{
	SSP1BUF = data;
	I2C_WaitForCompletion();
}

void I2C_MasterSetReceive(void)
{
	SSPCON2bits.RCEN = 1;;
	I2C_WaitForCompletion();
}

void I2C_MasterSendAck(void)
{
	SSPCON2bits.ACKDT = 0;
	SSPCON2bits.ACKEN = 1;
	I2C_WaitForCompletion();
}

void I2C_MasterSendNack(void)
{
	SSPCON2bits.ACKDT = 1;
	SSPCON2bits.ACKEN = 1;
	I2C_WaitForCompletion();
}

void eeprom_writeByte(unsigned short address, unsigned char *data)
{
    unsigned char addressmsb = (unsigned char)(address >> 8);
    unsigned char addresslsb = (unsigned char)address;
    I2C_MasterStart();
    I2C_MasterWrite( (CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00) ); //trailing 0 commands a write cycle
    I2C_MasterWrite(addressmsb);    //write the MSB address bits
    I2C_MasterWrite(addresslsb);    //write the LSB address bits
    I2C_MasterWrite(*data);//write out the data byte;
    I2C_MasterStop();
    ACK_Poll();//wait for the EEPROM to finish its write cycle. 
}

/**
 * @brief      Writes a page worth of data (32 bytes) out to the EEPROM
 *
 * @param[in]  address  The 16 bit address
 * @param      data     The data byte array pointer (16 elements)
 *
 * @return     If the address is not the beginning of the page, returns
 */
void eeprom_writePage(unsigned short address, unsigned char data[][8])
{
   unsigned char addressmsb = (unsigned char)address >> 8;
   unsigned char addresslsb = (unsigned char)address;
	if(address % 0x20 != 0) return; //address is not the start of a page
	I2C_MasterStart();
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //trailing 0 commands a write cycle
	I2C_MasterWrite(addressmsb); //write the MSB address bits
	I2C_MasterWrite(addresslsb); //write the LSB address bits
    for(char row = 0; row < 2; row++)
    {
        for (int column = 0; column < 32; column++)
        {
            I2C_MasterWrite(data[row][column]); //write out the data byte;
        }
        I2C_MasterStop();
        ACK_Poll(); //wait for the EEPROM to finish its write cycle. 
    }
}


/**
 * @brief      This takes a group of 50 measurement bursts and writes them out to EEPROM 4 bursts at
 *             a time, as this is what will fit on a single page in EEPROM. We cannnot write across
 *             page boundaries in a single operation. With a 10 bit ADC, we are using 16 bits per
 *             measurement for simplicity. 4 measurements per burst makes 8 bytes per burst. It is
 *             only really safe to assume that we have around 400 bytes of ram available for interim
 *             storage, so this means we are allowed 50 bursts before we need to write ito ut to
 *             EEPROM. To collect data over two seconds, we need to measure once every 40
 *             milliseconds
 *
 * @param[in]  address  The 16 bit address of where to start storing this data in EEPROM
 * @param      data     The pointer to the start of the 50*4 burst storage array
 */
void eeprom_storeBurstGroup(unsigned short address, unsigned short data[][8])
{
	if(address % 0x20 != 0) return; //address is not the start of a page

	for(unsigned char pagewritten = 0; pagewritten < 13; pagewritten++)
	{
		unsigned char addressmsb = (unsigned char)(address >> 8);
        unsigned char addresslsb = (unsigned char)(address);
		I2C_MasterStart();
		I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //trailing 0 commands a write cycle
			
		I2C_MasterWrite(addressmsb); //write the MSB address bits
		I2C_MasterWrite(addresslsb); //write the LSB address bits
		for (unsigned char row = 0; row < 2; row++) //we are going to write 4 rows of data at a time
		{
            for(unsigned char column = 0; column < 8; column++)
            {
                I2C_MasterWrite((unsigned char)((data[row + (pagewritten * 2)][column]) >> 8)); //write out upper half of 16 bit number;
                I2C_MasterWrite((unsigned char)(data[row + (pagewritten * 2)][column])); //write out lower half of 16 bit number;
            }
		}
        I2C_MasterStop();
        ACK_Poll(); //wait for the EEPROM to finish its write cycle. 
    }
}
/**
* @brief      reads a byte from EEPROM at the specified address and writes it to the address
*             provided by the data pointer.
*
* @param[in]  address  The 16 bit EEPROM address
* @param      data     The data byte pointer
*/
void eeprom_readByte(unsigned short address, unsigned char *databyte)
{
   unsigned char addressmsb = (unsigned char)(address >> 8);
   unsigned char addresslsb = (unsigned char)address;
	//first we set the address to be read
	I2C_MasterStart();
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //start a write cycle to set the address
	I2C_MasterWrite(addressmsb);
	I2C_MasterWrite(addresslsb);
	I2C_MasterStart(); //this terminates the write cycle
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x01); //start a read cycle at the current address
	I2C_MasterSetReceive();
	*databyte = SSPBUF;
	I2C_MasterSendNack();
	I2C_MasterStop();
 
}

void eeprom_readPage(unsigned short address, unsigned short measarray[][8])
{
    unsigned char addressmsb = (unsigned char)(address >> 8);
    unsigned char addresslsb = (unsigned char)address;
	//first we set the address to be read
	I2C_MasterStart();
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //start a write cycle to set the address
	I2C_MasterWrite(addressmsb);
	I2C_MasterWrite(addresslsb);
	I2C_MasterStart(); //this terminates the write cycle
    I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x01); //start a read cycle at the current address
    for(unsigned char row = 0; row < 2; row++)
    {
        for (unsigned char column = 0; column < 8; column++)
        {
           I2C_MasterSetReceive();
           unsigned char databyte1 = SSPBUF;
           I2C_MasterSendAck();
           I2C_MasterSetReceive();
           unsigned char databyte2 = SSPBUF;
           measarray[row][column] = (unsigned short)((databyte1 << 8) | databyte2);
        }
	}
     I2C_MasterSendNack();
     I2C_MasterStop();
     
}
//
// /**
// * { list_item_description }
// @brief      reads the entire contents of the EEPROM, one byte at a time, to an outside variable. The
//             idea here is that the contents of that variable will be passed to the USB bus.
//
// @param      byte  The byte
// @param      data  The data byte pointer */
//
void eeprom_readMem(unsigned char *databyte)
{
   I2C_MasterStart();
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x00); //start a write cycle to set the address
	//set the address to read from (we want the start of memory)
	I2C_MasterWrite(0);
	I2C_MasterWrite(0);
	I2C_MasterStart(); //this terminates the write cycle
	I2C_MasterWrite(CONTROLBYTE | (HWADDRESSBITS << 1) | 0x01); //start a read cycle at the current address
	for (unsigned short i = 0; i < 0xFFF; i++)
	{
       I2C_MasterSetReceive();
       *databyte = SSPBUF;
       I2C_MasterSendAck();
	}
		I2C_MasterSetReceive();
     *databyte = SSPBUF;
     I2C_MasterSendNack();
     I2C_MasterStop();
}
//
