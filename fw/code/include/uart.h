/**
 * @file uart.h
 * @author Nicholas Shrake <shraken@gmail.com>
 *
 * @date 2017-09-26
 * @brief Initialization library for the UART0 peripheral. 
 *			
 */

#ifndef _UART_H
#define _UART_H

#include <c8051f3xx.h>
#include "globals.h"

#define BAUDRATE           115200           // Baud rate of UART in bps

void uart_init (void);

#endif