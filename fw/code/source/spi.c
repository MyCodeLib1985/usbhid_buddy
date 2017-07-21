#include <compiler_defs.h>
#include <C8051F380_defs.h>
#include <spi.h>
#include <stdio.h>
#include <stdlib.h>
#include <gpio.h>
#include <globals.h>

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
unsigned char SPI_Data_Rx_Array[SPI_MAX_BUFFER_SIZE] = { 0 };
unsigned char SPI_Data_Tx_Array[SPI_MAX_BUFFER_SIZE] = { 0 };

unsigned char bytes_trans;

void SPI_ISR (void) interrupt 6
{
	static unsigned char state = 0;
	static unsigned char array_index = 0;
	
	switch (state) {
		// continue sending
		case 0:
			SPI_Data_Rx_Array[array_index] = SPI0DAT;
			array_index++;
		
			SPI0DAT = SPI_Data_Tx_Array[array_index];
			
			// bytes_trans = 2, 2 -1 = 1
            if (array_index >= (bytes_trans - 1)) {
				state = 1;
            }
		
			break;
		
		// copy off last byte in SPI RX buffer and
		// deselect chip select
		case 1:
			SPI_Data_Rx_Array[array_index] = SPI0DAT;
		
			// De-select the Slave
			NSSMD0 = 1;

			array_index = 0;
			state = 0;
			break;
		
		default:
			state = 0;
			break;
	}
	
	// Clear the SPIF flag
	SPIF = 0;
}

void SPI0_Init(void)
{
   // set the number of bytes in transcation to zero
   bytes_trans = 0;
	
   //SPI0CFG   = 0x70;                   // Enable the SPI as a Master
   //                                    // CKPHA = '0', CKPOL = '0'
   // 
   SPI0CFG = 0x50;

   SPI0CN    = 0x0D;                   // 4-wire Single Master, SPI enabled

   // SPI clock frequency equation from the datasheet
   SPI0CKR   = (SYSCLK/(2*SPI_CLOCK))-1;

   ESPI0 = 1;                          // Enable SPI interrupts
}

void SPI_Array_ReadWrite (void)
{
	// Wait until the SPI is free, in case
    // it's already busy
    while (!NSSMD0);                    
	
    NSSMD0 = 0;

    //Command = SPI_READ_BUFFER;

    //SPI0DAT = Command;
    SPI0DAT = SPI_Data_Tx_Array[0];
	
    // Wait for SPI transcation to complete
    while (!NSSMD0);
}

void SPI_Select(uint8_t chip_select)
{
	switch (chip_select) {
		case SPI_DEVICE_TYPE_TLV563x:
			// disable chip select for memory
			gpio_set_pin_value(SPI_MEM_CS_PIN, GPIO_VALUE_HIGH);
		
			// disable SPI NSS skip
			P1SKIP &= ~(1 << 3);
			break;
		
		case SPI_DEVICE_TYPE_23LC1024:
			// disable chip select for tlv563x DAC
			gpio_set_pin_value(SPI_DAC_CS_PIN, GPIO_VALUE_HIGH);
		
			// enable SPI NSS skip
			P1SKIP |= (1 << 3);
			break;
		
		default:
			break;
	}
}