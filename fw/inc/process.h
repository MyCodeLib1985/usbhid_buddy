/**
 * @file process.h
 * @author Nicholas Shrake <shraken@gmail.com>
 *
 * @date 2017-12-10
 * @brief Handles the incoming configuration and data messages
 *				from the host.  Prepares the configuration response
 *				and sends the data messages back to the host.  
 *			
 */

#ifndef  _PROCESS_H_
#define  _PROCESS_H_

#include <stdint.h>
#include <stdint.h>
#include <adc.h>

extern bit SendPacketBusy;
extern uint8_t timer0_flag;
extern unsigned char OUT_PACKET[];
extern unsigned char *P_IN_PACKET_SEND;

extern __code firmware_info_t fw_info;

extern int16_t __data adc_results[MAX_ANALOG_INPUTS];
extern uint8_t __code adc_mux_ref_tbl[MAX_ANALOG_INPUTS];
extern uint8_t adc_mux_tbl_n[MAX_ANALOG_INPUTS];
extern uint8_t adc_mux_tbl_p[MAX_ANALOG_INPUTS];
extern uint8_t adc_channel_count;
extern uint8_t adc_int_dec_max;
extern uint8_t __data adc_channel_index;
extern uint8_t adc_int_dec;
extern uint16_t adc_timer_count;

/** @brief Routine that is called an infinite loop by the firmware.  It executes the proess_out and process_in messages.
 *  @return 0 on sucess, -1 on error.
 */
void process();

#endif