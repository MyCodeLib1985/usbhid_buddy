#include "pwm.h"

/// base clock frequency used for subsequent operations.  This is
/// is dynamically chosen when the pwm init routine is run
static uint32_t pwm_timebase = BUDDY_SYSCLK;

/// PWM capture module high and low bytes.  These are stored and
/// reloaded in the PWM interrupt.
static uint32_t pwm_cex[NUMBER_PCA_CHANNELS];

/// array to indicate which channels have PWM enabled on them
static uint8_t pwm_chan_enable[BUDDY_CHAN_LENGTH] = { 0 };

/// enum of type RUNTIME_PWM_MODE indicating if the PWM operates in a
/// frequency or duty cycle mode.
static uint8_t pwm_mode;

/// the resolution used with the PWM
static uint8_t pwm_resolution = RESOLUTION_CTRL_HIGH;

/** @brief Configures pins for PWM operation crossbar mode with as a push/pull output. 
 *  @return Void.
 */
void pwm_pin_init(void)
{
	// enable push-pull on P2.0 - P2.7
	P2MDOUT   = 0xFF;
	
	// crossbar skip over fixed P0, P1, and P2
  P0SKIP    = 0xCF;
  P1SKIP    = 0xF0;
  P2SKIP    = 0x00;  
	
	// disable high impedance on P2.0 - P2.7
	P2MDIN    = 0xFF;
	
	// enable PCA CEX0 - CEX4
  XBR0      = 0x03;
  XBR1      = 0x45;
}

/**
 * @brief initialize the PWM subsystem mode acting as a variable duty
 *  cycle.  
 * 
 * @return int8_t PWM_ERROR_CODE_OK if success, otherwise enum of type
 *  PWM_ERROR_CODE.
 */
int8_t pwm_duty_cycle_init(void)
{
	uint8_t i;
	
	// Stop counter; clear all flags
	PCA0CN = 0x00;
	
	// Use SYSCLK as time base
	PCA0MD = 0x08;      
	
	if (pwm_resolution == RESOLUTION_CTRL_LOW) {
		// 0100 1011
		// Module 0 = 8-bit PWM mode and 
		// enable Module 0 Match and Interrupt Flags
		PCA0CPM0 = 0x42;
		PCA0CPM1 = 0x42;
		PCA0CPM2 = 0x42;
		PCA0CPM3 = 0x42;
		PCA0CPM4 = 0x42;
	} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
		// 1100 1011
		// Module 0 = 16-bit PWM mode and 
		// enable Module 0 Match and Interrupt Flags
		PCA0CPM0 = 0xCB;
		PCA0CPM1 = 0xCB;
		PCA0CPM2 = 0xCB;
		PCA0CPM3 = 0xCB;
		PCA0CPM4 = 0xCB;
	} else {
		return PWM_ERROR_CODE_INDEX_ERROR;
	}
	
	for (i = BUDDY_CHAN_0; i <= BUDDY_CHAN_7; i++) {
		if (pwm_chan_enable[i]) {
			pwm_cex[i] = 0xFFFF;
			pwm_set_duty_cycle(i, pwm_cex[i]); 
		}
	}
				
	return PWM_ERROR_CODE_OK;
}

/**
 * @brief initialize the PWM subsystem mode acting as a variable frequency
 *  configuration.
 * 
 * @return int8_t PWM_ERROR_CODE_OK if success, otherwise enum of type
 *  PWM_ERROR_CODE.
 */
int8_t pwm_frequency_init(void)
{
	uint8_t i;

	// Stop counter; clear all flags
	PCA0CN = 0x00;

	// Use SYSCLK/12 as time base
	PCA0MD = 0x00;
	
	// 0100 0110
	// Module 0 = Frequency Output mode
	PCA0CPM0 = 0x46;
	PCA0CPM1 = 0x46;
	PCA0CPM2 = 0x46;
	PCA0CPM3 = 0x46;
	PCA0CPM4 = 0x46;
	
	for (i = BUDDY_CHAN_0; i <= BUDDY_CHAN_7; i++) {
		if (pwm_chan_enable[i]) {
			// Configure initial PWM frequency for 1 kHz
			pwm_cex[i] = DEFAULT_FREQUENCY;
			pwm_set_frequency(i, pwm_cex[i]);
		}
	}
	
	return PWM_ERROR_CODE_OK;
}

/** @brief Initialize the PWM device.  Sets the pins to a PWM state and saves off
 *				 local PWM state values.  Checks if frequency or duty cycle operation is
 *				 requested and delegates to function.  
 *  @param mode enum of type RUNTIME_PWM_MODE specifying duty cycle or frequency mode.
 *  @param resolution enum of type BUDDY_DATA_SIZE specifying low (8-bit), high (16-bit),
 *				 or super (32-bit) resolution.
 *	@param chan_mask enum of BUDDY_CHANNELS_MASK bitmask values representing the channels
 *				 requested for operation.
 *  @return PWM_ERROR_CODE_OK on success, PWM_ERROR_CODE_GENERAL_ERROR on error.
 */
int8_t pwm_init(uint8_t mode, uint8_t resolution, uint8_t chan_mask)
{
	uint8_t i;

	pwm_pin_init();

	pwm_mode = mode;
	pwm_resolution = resolution;
	
	for (i = BUDDY_CHAN_0; i <= BUDDY_CHAN_7; i++) {
		if (chan_mask & (1 << i)) {
		  pwm_chan_enable[i] = 1;
		} else {
			pwm_chan_enable[i] = 0;
		}
	}
	
	if (mode == RUNTIME_PWM_MODE_FREQUENCY) {
		pwm_frequency_init();
	} else if (mode == RUNTIME_PWM_MODE_DUTY_CYCLE) {
	  pwm_duty_cycle_init();
	} else {
		return PWM_ERROR_CODE_GENERAL_ERROR;
	}

	return PWM_ERROR_CODE_OK;
}

/** @brief Enable PCA interrupts and enable PCA mode.
 *  @return Void.
 */
void pwm_enable(void)
{
	// Enable PCA interrupts
  EIE1 |= 0x10;
	
	// Start PCA counter
  CR = 1;
}

/** @brief Disable PCA interrupts and disable PCA mode.
 *  @return Void.
 */
void pwm_disable(void)
{
	// Stop counter; clear all flags
	PCA0CN = 0x00;
	
	// Enable PCA interrupts
  EIE1 &= ~(0x10);
	
	P2MDOUT   = 0x00;
	XBR1     &= ~(0x05);
}

/** @brief Sets the timebase used for PWM frequency mode of operation.  The timebase
 *				 specifies the maximum frequency that is a fraction of the provided PWM
 *				 counter value.
 *  @param value enum of type RUNTIME_PWM_TIMEBASE specifying the SYSCLK frequency used
 *				 as a timebase for PWM frequency mode.
 *  @return PWM_ERROR_CODE_OK on sucess, PWM_ERROR_CODE_GENERAL_ERROR on error.
 */
int8_t pwm_set_timebase(uint8_t value)
{
	//debug(("pwm_set_timebase: value = %bd\r\n", value));
	
		PCA0MD &= ~(0x0E);
	
		switch (value) {
			case RUNTIME_PWM_TIMEBASE_SYSCLK:
				PCA0MD |= 0x08;
				pwm_timebase = BUDDY_SYSCLK;
				break;
			
			case RUNTIME_PWM_TIMEBASE_SYSCLK_DIV_4:
				PCA0MD |= 0x02;
				pwm_timebase = (BUDDY_SYSCLK / 4);
				break;
			
			case RUNTIME_PWM_TIMEBASE_SYSCLK_DIV_12:
				PCA0MD |= 0x00;
				pwm_timebase = (BUDDY_SYSCLK / 12);
				break;
			
			case RUNTIME_PWM_TIMEBASE_TIMER0_OVERFLOW:
			default:
				return PWM_ERROR_CODE_INDEX_ERROR;
		}
		
		return PWM_ERROR_CODE_OK;
}

/** @brief Sets the PWM frequency for a given channel.
 *  @param channel enum of type BUDDY_CHANNELS specifying the channel to set frequency on.
 *  @param value integer value specifying the fractional count value that the pwm_timebase
 *				 should be set to.  The max integer value is 255, 65535, or 4294967295 depending
 *				 on the resolution setting specified in the pwm_init call.
 *  @return PWM_ERROR_CODE_OK on sucess, PWM_ERROR_CODE_GENERAL_ERROR on error.
 */
int8_t pwm_set_frequency(uint8_t channel, uint32_t value)
{
	uint16_t reg_value;
	
	if ((channel < BUDDY_CHAN_0) ||
		  (channel > BUDDY_CHAN_4)) {
	  return PWM_ERROR_CODE_INDEX_ERROR;
	}
	
	pwm_cex[channel] = value;
	
	reg_value = (pwm_timebase / (2 * pwm_cex[channel]));
	
	/*
	debug(("value = %lu\r\n", value));
	debug(("pwm_timebase = %lu\r\n", pwm_timebase));
	debug(("pwm_cex[%bd] = %lu\r\n", channel, pwm_cex[channel]));
	debug(("pwm_set_frequency: pwm_cex[%bd] = %u\r\n", channel, reg_value));
	*/
	
	switch (channel) {
		case BUDDY_CHAN_0:
			PCA0CPH0 = reg_value;
			break;
					
		case BUDDY_CHAN_1:
			PCA0CPH1 = reg_value;
			break;
					
		case BUDDY_CHAN_2:
			PCA0CPH2 = reg_value;
			break;
					
		case BUDDY_CHAN_3:
			PCA0CPH3 = reg_value;
			break;
					
		case BUDDY_CHAN_4:
			PCA0CPH4 = reg_value;
			break;
					
		default:
			break;
	}

	return PWM_ERROR_CODE_OK;
}

/** @brief Sets the PWM duty cycle for the given channel.
 *  @param channel enum of type BUDDY_CHANNELS specifying the channel to set duty cycle on.
 *  @param value integer value specifying the frational count value that the duty cycle is set
 *				 to.  The max integer value is 255, 65535, or 4294967295 depending
 *				 on the resolution setting specified in the pwm_init call.
 *
 *				 If the channel value is passed as 32767 and the resolution is set to 16-bit mode
 *				 then a 50% duty cycle will be set.
 *  @return PWM_ERROR_CODE_OK on sucess, PWM_ERROR_CODE_GENERAL_ERROR on error.
 */
int8_t pwm_set_duty_cycle(uint8_t channel, uint16_t value)
{
	if ((channel < BUDDY_CHAN_0) ||
		  (channel > BUDDY_CHAN_4)) {
	  return PWM_ERROR_CODE_INDEX_ERROR;
	}
		  
	printf("pwm_duty_cycle: channel = %bd\r\n", channel);
	printf("pwm_duty_cycle: value = %u\r\n", value);
	
	pwm_cex[channel] = value;
	
	switch (channel) {
		case BUDDY_CHAN_0:
			if (pwm_resolution == RESOLUTION_CTRL_LOW) {
					PCA0CPH0 = (pwm_cex[BUDDY_CHAN_0] & 0x00FF);
			} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
					PCA0CPL0 = (pwm_cex[BUDDY_CHAN_0] & 0x00FF);
					PCA0CPH0 = (pwm_cex[BUDDY_CHAN_0] & 0xFF00)>>8;
			}
			break;
					
		case BUDDY_CHAN_1:
			if (pwm_resolution == RESOLUTION_CTRL_LOW) {
					PCA0CPH1 = (pwm_cex[BUDDY_CHAN_1] & 0x00FF);
			} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
					PCA0CPL1 = (pwm_cex[BUDDY_CHAN_1] & 0x00FF);
					PCA0CPH1 = (pwm_cex[BUDDY_CHAN_1] & 0xFF00)>>8;
			}
			break;
					
		case BUDDY_CHAN_2:
			if (pwm_resolution == RESOLUTION_CTRL_LOW) {
					PCA0CPH2 = (pwm_cex[BUDDY_CHAN_2] & 0x00FF);
			} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
					PCA0CPL2 = (pwm_cex[BUDDY_CHAN_2] & 0x00FF);
					PCA0CPH2 = (pwm_cex[BUDDY_CHAN_2] & 0xFF00)>>8;
			}
			break;
					
		case BUDDY_CHAN_3:
			if (pwm_resolution == RESOLUTION_CTRL_LOW) {
					PCA0CPH3 = (pwm_cex[BUDDY_CHAN_3] & 0x00FF);
			} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
					PCA0CPL3 = (pwm_cex[BUDDY_CHAN_3] & 0x00FF);
					PCA0CPH3 = (pwm_cex[BUDDY_CHAN_3] & 0xFF00)>>8;
			}
			break;
					
		case BUDDY_CHAN_4:
			if (pwm_resolution == RESOLUTION_CTRL_LOW) {
					PCA0CPH4 = (pwm_cex[BUDDY_CHAN_4] & 0x00FF);
			} else if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
					PCA0CPL4 = (pwm_cex[BUDDY_CHAN_4] & 0x00FF);
					PCA0CPH4 = (pwm_cex[BUDDY_CHAN_4] & 0xFF00)>>8;
			}
			break;
					
		default:
			break;
	}

	return PWM_ERROR_CODE_OK;
}

/**
 * @brief PWM interrupt
 * 
 */
void PCA0_ISR (void) interrupt 11
{
	if (pwm_mode == RUNTIME_PWM_MODE_DUTY_CYCLE) {
		if (CCF0) {
			CCF0 = 0;
			
			if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
				PCA0CPL0 = (pwm_cex[BUDDY_CHAN_0] & 0x00FF);
				PCA0CPH0 = (pwm_cex[BUDDY_CHAN_0] & 0xFF00)>>8;
			} else if (pwm_resolution == RESOLUTION_CTRL_LOW) {
				PCA0CPH0 = (pwm_cex[BUDDY_CHAN_0] & 0x00FF);
			}
		} else if (CCF1) {
			CCF1 = 0;
			
			if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
				PCA0CPL1 = (pwm_cex[BUDDY_CHAN_1] & 0x00FF);
				PCA0CPH1 = (pwm_cex[BUDDY_CHAN_1] & 0xFF00)>>8;
			} else if (pwm_resolution == RESOLUTION_CTRL_LOW) {
				PCA0CPH1 = (pwm_cex[BUDDY_CHAN_1] & 0x00FF);
			}
		} else if (CCF2) {
			CCF2 = 0;
			
			if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
				PCA0CPL2 = (pwm_cex[BUDDY_CHAN_2] & 0x00FF);
				PCA0CPH2 = (pwm_cex[BUDDY_CHAN_2] & 0xFF00)>>8;
			} else if (pwm_resolution == RESOLUTION_CTRL_LOW) {
				PCA0CPH2 = (pwm_cex[BUDDY_CHAN_2] & 0x00FF);
			}
		} else if (CCF3) {
			CCF3 = 0;
			
			if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
				PCA0CPL3 = (pwm_cex[BUDDY_CHAN_3] & 0x00FF);
				PCA0CPH3 = (pwm_cex[BUDDY_CHAN_3] & 0xFF00)>>8;
			} else if (pwm_resolution == RESOLUTION_CTRL_LOW) {
				PCA0CPH3 = (pwm_cex[BUDDY_CHAN_3] & 0x00FF);
			}
		} else if (CCF4) {
			CCF4 = 0;
			
			if (pwm_resolution == RESOLUTION_CTRL_HIGH) {
				PCA0CPL4 = (pwm_cex[BUDDY_CHAN_4] & 0x00FF);
				PCA0CPH4 = (pwm_cex[BUDDY_CHAN_4] & 0xFF00)>>8;
			} else if (pwm_resolution == RESOLUTION_CTRL_LOW) {
				PCA0CPH4 = (pwm_cex[BUDDY_CHAN_4] & 0x00FF);
			}
		}
	}
}