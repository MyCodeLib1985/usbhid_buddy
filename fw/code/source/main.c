#include "main.h"

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

/** firmware info structure that identifies serial, version,
 *   and hardware specific (DAC & expander) types. */
code firmware_info_t fw_info = {
	BUDDY_FW_INFO_SERIAL,
	BUDDY_FW_INFO_DATETIME,
	BUDDY_FW_FWREV_INFO_MAJOR,
	BUDDY_FW_FWREV_INFO_MINOR,
	BUDDY_FW_FWREV_INFO_TINY,
	BUDDY_FW_BOOTLREV_INFO_MAJOR,
	BUDDY_FW_BOOTLREV_INFO_MINOR,
	BUDDY_FW_BOOTLREV_INFO_TINY,
	FIRMWARE_INFO_DAC_TYPE_TLV5630,
};

/**
 * @brief print the firmware information to the debug uart console
 * @return Void. 
 */
void print_device_info(void)
{
    printf("                                 \r\n");
	printf(" ____            _     _         \r\n");
    printf("| __ ) _   _  __| | __| |_   _   \r\n");
    printf("|  _ \| | | |/ _` |/ _` | | | |  \r\n");
    printf("| |_) | |_| | (_| | (_| | |_| |  \r\n");
    printf("|____/ \__,_|\__,_|\__,_|\__, |  \r\n");
    printf("                         |___/   \r\n");
		printf("   version %bd.%bd.%bd \r\n", fw_info.fw_rev_major,
				fw_info.fw_rev_minor, fw_info.fw_rev_tiny);
		printf("   serial id: %lu (%08lx)\r\n", 
				fw_info.serial, fw_info.serial);
		printf("   build datetime: %lu (%08lx)\r\n", 
				fw_info.flash_datetime, fw_info.flash_datetime);
	
	switch (fw_info.type_dac) {
		case FIRMWARE_INFO_DAC_TYPE_TLV5630:
			printf("   dac type: TLV5630 (12-bit)\r\n");
			break;
		
		case FIRMWARE_INFO_DAC_TYPE_TLV5631:
			printf("   dac type: TLV5631 (10-bit)\r\n");
			break;
		
		case FIRMWARE_INFO_DAC_TYPE_TLV5632:
			printf("   dac type: TLV5632 (8-bit)\r\n");
			break;
		
		case FIRMWARE_INFO_DAC_TYPE_NONE:
		default:
			printf("   dac type: none\r\n");
			break;
	}
	
	printf("\r\n");
}

/**
 * @brief initialize the buddy context structure.  the context
 * 	structure stores the real time configuration settings
 *  during operation.  
 * 
 */
void contexts_init(void)
{
	buddy_ctx.daq_state         = GENERAL_CTRL_NONE;
	buddy_ctx.m_ctrl_mode       = MODE_CTRL_IMMEDIATE;
	buddy_ctx.m_adc_mode          = RUNTIME_ADC_MODE_SINGLE_ENDED;
	buddy_ctx.m_pwm_mode        = RUNTIME_PWM_MODE_FREQUENCY;
	buddy_ctx.m_pwm_timebase    = RUNTIME_PWM_TIMEBASE_SYSCLK;
	buddy_ctx.m_counter_control = RUNTIME_COUNTER_CONTROL_ACTIVE_HIGH;
	buddy_ctx.m_chan_mask       = 0;
	buddy_ctx.m_resolution      = RESOLUTION_CTRL_HIGH;
	buddy_ctx.m_data_size       = BUDDY_DATA_SIZE_HIGH;
	buddy_ctx.m_chan_number     = 0;
	
	buddy_ctx.m_expander_type = BUDDY_EXPANDER_TYPE_BASE;
	buddy_ctx.m_expander_mode = 0;
	buddy_ctx.m_expander_pin_state = 0;
}

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main(void)
{
	system_init();
	contexts_init();
	
	gpio_init();
	
  usb_init();
  spi_init();
    
  adc_init();
  uart_init();

  timers_init();
  tlv563x_dac_init();
	
	print_device_info();
  debug(("tlv563x_dac_init passed\r\n"));
	
	PCA0MD = 0x00;                      // Disable watchdog timer
	EA = 1;                             // Globally enable interrupts
		
	while (1) {
		process();
  }
}

