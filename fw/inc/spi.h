/**
 * @file spi.h
 * @author Nicholas Shrake <shraken@gmail.com>
 *
 * @date 2017-09-26
 * @brief SPI driver library for configuration and data
 *				transmission using the SPI peripheral.
 *			
 */

#ifndef  _SPI_H_
#define  _SPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
//#define SPI_CLOCK          12000000      // Maximum SPI clock
#define SPI_CLOCK          1000000
                                        // The SPI clock is a maximum of 250 kHz
                                        // when this example is used with
                                        // the SPI0_Slave code example.

#define SPI_MAX_BUFFER_SIZE    128      // Maximum buffer Master will send

// Instruction Set
#define  SPI_WRITE         0x04        // Send a byte from the Master to the
                                       // Slave
#define  SPI_READ          0x08        // Send a byte from the Slave to the
                                       // Master
#define  SPI_WRITE_BUFFER  0x10        // Send a series of bytes from the
                                       // Master to the Slave
#define  SPI_READ_BUFFER   0x20        // Send a series of bytes from the Slave
                                       // to the Master
#define  ERROR_OCCURRED    0x40        // Indicator for the Slave to tell the

typedef enum _SPI_DEVICE_TYPE {
	SPI_DEVICE_TYPE_TLV563x = 0,
	SPI_DEVICE_TYPE_23LC1024,
} SPI_DEVICE_TYPE;

/**
 * @brief Configures SPI0 to use 4-wire Single Master mode. The SPI timing is
 *		  configured for Mode 0,0 (data centered on first edge of clock phase and
 *		  SCK line low in idle state).
 *
 * @return Void.
 */
void spi_init(void);

/**
 * @brief Preforms a SPI read/write transaction of length `bytes_trans`.
 *
 * @return Void.
 */
void spi_array_readwrite(void);

/**
 * @brief Configures the DAC CS as the primary SPI chip select.  This is a leftover
 *			  artificat when multiple SPI devices were supported and isn't explictly necessary
 *	      and in future should be revised and removed.
 *
 * @return Void.
 */
void spi_select(void);

#endif /* _SPI_H_ */