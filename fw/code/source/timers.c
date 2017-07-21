#include <stdio.h>
#include <stdint.h>
#include <timers.h>
#include <buddy.h>
#include <globals.h>
#include <action.h>
#include <adc.h>
#include <gpio.h>
#include <utility.h>
#include <c8051f3xx.h>

extern uint8_t daq_state;

extern uint8_t adc_channel_index;
extern uint8_t adc_channel_count;
extern uint8_t adc_mux_tbl[MAX_ANALOG_INPUTS];

uint8_t timer0_flag = 0;
uint8_t timer2_count = 0;

uint8_t timer0_low_set;
uint8_t timer0_high_set;

void Timer0_Init (void)
{
		// set to 0x03E8 (1000) ticks at 0.25 usec timer period
		// for equivalent interrupt of 250 usec.
		
		//timer0_high_set = 0x44;
		//timer0_low_set = 0x78;
	
		timer0_high_set = 0xA2;
		timer0_low_set = 0x3C;
	
		TH0 = timer0_high_set;
		TL0 = timer0_low_set;
	
		// Mode1: 16-bit counter/timer
		TMOD |= 0x01;
	
		// Timer0 uses SYSCLK / 12
		CKCON &= ~(0x07);
		CKCON |= 0x04;
	
		// Timer0 interrupt enabled
		ET0 = 1;
	
		// Timer0 ON
		TCON |= 0x10;
}

void Timer0_Set_Period (uint32_t period)
{
		uint16_t timer_set;
	
		// Disable Timer0
		TCON &= ~(0x10);
	
		// Timer0 interrupt disabled
		ET0 = 0;
	
		debug(("Timer0_Set_Period, nsec period = %lu\r\n", period));
	
		// bound period by lower value of 20.83 nsec (21 nsec)
		// and upper value of 65535000 nsec.
	
		if (period < TIMER0_LOW_PERIOD) {
				period = TIMER0_LOW_PERIOD;
		} else if (period > TIMER0_HIGH_PERIOD) {
				period = TIMER0_HIGH_PERIOD;
		}
	
		CKCON &= ~(0x07);
		
		// set Timer0 clock base and 16-bit timer comparator value
		
		if ((period < (((1.0 /(SYSCLK/48)) * 0xFFFF) / 1e-9)) &&
			 (period > (((1.0 /(SYSCLK/48)) * 0x0001) / 1e-9))) {
				timer_set = 0xFFFF - (period * 1e-9) * (SYSCLK/48);
				timer0_high_set = ((timer_set & 0xFF00) >> 8);
				timer0_low_set = (timer_set & 0x00FF);
			  debug(("Timer0 set region 4 with %u\r\n", timer_set));
				 
				// Timer0 uses SYSCLK / 48
				CKCON |= 0x02;
	  } else if ((period < (((1.0 /(SYSCLK/12)) * 0xFFFF) / 1e-9)) &&
			 (period > (((1.0 /(SYSCLK/12)) * 0x0001) / 1e-9))) {
			  timer_set = 0xFFFF - (period * 1e-9) * (SYSCLK/12);
				timer0_high_set = ((timer_set & 0xFF00) >> 8);
				timer0_low_set = (timer_set & 0x00FF);
				debug(("Timer0 set region 3 with %u\r\n", timer_set));
				 
				// Timer0 uses SYSCLK / 12
				CKCON |= 0x00;
	  } else if ((period < (((1.0 /(SYSCLK/4)) * 0xFFFF) / 1e-9)) &&
			 (period > (((1.0 /(SYSCLK/4)) * 0x0001) / 1e-9))) {
			  timer_set = 0xFFFF - (period * 1e-9) * (SYSCLK/4);
				timer0_high_set = ((timer_set & 0xFF00) >> 8);
				timer0_low_set = (timer_set & 0x00FF);
				debug(("Timer0 set region 2 with %u\r\n", timer_set));
				 
				// Timer0 uses SYSCLK / 4
				CKCON |= 0x01;
	  } else if ((period < (((1.0 /SYSCLK) * 0xFFFF) / 1e-9)) &&
			 (period > (((1.0 /SYSCLK) * 0x0001) / 1e-9))) {
				timer_set = 0xFFFF - (period * 1e-9) * SYSCLK;
				timer0_high_set = ((timer_set & 0xFF00) >> 8);
				timer0_low_set = (timer_set & 0x00FF);
				debug(("Timer0 set region 1 with %u\r\n", timer_set));
				 
				// Timer0 uses SYSCLK
				CKCON |= 0x04;
	 } else {
				debug(("Timer0 region not settable\r\n"));
			
				// Timer0 uses SYSCLK / 48
				CKCON |= 0x02;
			
				timer0_high_set = 0x00;
				timer0_low_set = 0x00;
		}
		
		TH0 = timer0_high_set;
		TL0 = timer0_low_set;
		
		// Timer0 interrupt enabled
		ET0 = 1;
		
		// Enable Timer0
		TCON |= 0x10;
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

void Timer0_ISR (void) interrupt 1
{
		static uint8_t timer0_state = 0;
	  
		TH0 = timer0_high_set;
		TL0 = timer0_low_set;
	
		timer0_flag = 1;
	
		if (daq_state == GENERAL_CTRL_ADC_ENABLE) {
        if (adc_channel_index == (adc_channel_count - 1)) {
            AMX0P = adc_mux_tbl[0];
        }
        else {
            AMX0P = adc_mux_tbl[adc_channel_index + 1];
        }
    }
		
		/*
		if (timer0_state)  {
				gpio_set_pin_value(TEST_STATUS_PIN, GPIO_VALUE_LOW);
				timer0_state = 0;
		} else {
				gpio_set_pin_value(TEST_STATUS_PIN, GPIO_VALUE_HIGH);
				timer0_state = 1;
		}
		*/
}

/*
void Timer2_ISR (void) interrupt 5
{
	if (timer2_count >= TIMER2_LOOPS) {
		if (gpio_get_pin_value(HEARTBEAT_PIN)) {
			gpio_set_pin_value(HEARTBEAT_PIN, GPIO_VALUE_LOW);
		} else {
			gpio_set_pin_value(HEARTBEAT_PIN, GPIO_VALUE_HIGH);
		}
		
		timer2_count = 0;
	}
	
	timer2_count++;
	TF2H = 0;                           // Reset Interrupt
}
*/