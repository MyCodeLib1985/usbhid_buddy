#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <buddy.h>

//#define SYSCLK             12000000    // SYSCLK frequency in Hz

//#define ADC_TEST

// C8051F380 48-pin ADC pin macros
// see pg. 60 of C8051F38x datasheet
#define ADC_P0_3 0x11 // 010001b
#define ADC_P0_4 0x12 // 010010b

#define ADC_P1_0 0x15 // 010101b
#define ADC_P1_1 0x13 // 010011b
#define ADC_P1_2 0x14 // 010100b
#define ADC_P1_3 0x16 // 010110b
#define ADC_P1_6 0x17 // 010111b
#define ADC_P1_7 0x18 // 011000b

#define ADC_P2_0 0x00 // 000000b
#define ADC_P2_1 0x01 // 000001b
#define ADC_P2_2 0x02 // 000010b
#define ADC_P2_3 0x03 // 000011b
#define ADC_P2_4 0x19 // 011001b
#define ADC_P2_5 0x04 // 000100b
#define ADC_P2_6 0x05 // 000101b
#define ADC_P2_7 0x1A // 011010b

#define ADC_P3_0 0x06 // 000110b
#define ADC_P3_1 0x07 // 000111b
#define ADC_P3_2 0x1B // 011011b
#define ADC_P3_3 0x1C // 011100b
#define ADC_P3_4 0x08 // 001000b
#define ADC_P3_5 0x09 // 001001b
#define ADC_P3_6 0x1D // 011101b
#define ADC_P3_7 0x0A // 001010b

#define ADC_P4_0 0x0B // 001011b
#define ADC_P4_1 0x20 // 100000b
#define ADC_P4_2 0x21 // 100001b
#define ADC_P4_3 0x0C // 001100b
#define ADC_P4_4 0x0D // 001101b
#define ADC_P4_5 0x0E // 001110b
#define ADC_P4_6 0x0F // 001111b
#define ADC_P4_7 0x22 // 100010b

// error code used globally for all routines
enum _config_error
{
    E_SUCCESS = 0,
    E_GENERAL_FAIL = -1,
    E_INDEX_OUT_BOUND = -2
};

typedef enum _config_error error_t;

// Encoded pin definition types in an enum
// explicitly specified for clarity
// MSB..LSB
// XX.YYY.ZZZ
//  XX  = don't care
//  YYY = major (P0, P1, etc.)
//  ZZZ = minor is (0..7). 

#define GPIO_MAJOR_MASK 0x38
#define GPIO_MINOR_MASK 0x07

enum _gpio_pin_type
{
    GPIO_P0_0 = 0x00, // 00 000 000
    GPIO_P0_1 = 0x01,
    GPIO_P0_2 = 0x02,
    GPIO_P0_3 = 0x03,
    GPIO_P0_4 = 0x04,
    GPIO_P0_5 = 0x05,
    GPIO_P0_6 = 0x06,
    GPIO_P0_7 = 0x07, // 00 000 111
    
    GPIO_P1_0 = 0x08, // 00 001 000
    GPIO_P1_1 = 0x09,
    GPIO_P1_2 = 0x0A,
    GPIO_P1_3 = 0x0B,
    GPIO_P1_4 = 0x0C,
    GPIO_P1_5 = 0x0D,
    GPIO_P1_6 = 0x0E,
    GPIO_P1_7 = 0x0F, // 00 001 111
    
    GPIO_P2_0 = 0x10, // 00 010 000
    GPIO_P2_1 = 0x11,
    GPIO_P2_2 = 0x12,
    GPIO_P2_3 = 0x13,
    GPIO_P2_4 = 0x14,
    GPIO_P2_5 = 0x15,
    GPIO_P2_6 = 0x16,
    GPIO_P2_7 = 0x17, // 00 010 111
    
    GPIO_P3_0 = 0x18, // 00 011 000
    GPIO_P3_1 = 0x19,
    GPIO_P3_2 = 0x1A,
    GPIO_P3_3 = 0x1B,
    GPIO_P3_4 = 0x1C,
    GPIO_P3_5 = 0x1D,
    GPIO_P3_6 = 0x1E,
    GPIO_P3_7 = 0x1F, // 00 011 111
    
    GPIO_P4_0 = 0x20, // 00 100 000
    GPIO_P4_1 = 0x21,
    GPIO_P4_2 = 0x22,
    GPIO_P4_3 = 0x23,
    GPIO_P4_4 = 0x24,
    GPIO_P4_5 = 0x25,
    GPIO_P4_6 = 0x26,
    GPIO_P4_7 = 0x27, // 00 100 111
};

enum _gpio_pin_mode
{
    GPIO_MODE_OPEN_DRAIN,
    GPIO_MODE_PUSH_PULL
};

enum _gpio_pin_value
{
    GPIO_VALUE_LOW,
    GPIO_VALUE_HIGH
};

enum _gpio_major_type 
{
    GPIO_MAJOR_PORT0,
    GPIO_MAJOR_PORT1,
    GPIO_MAJOR_PORT2,
    GPIO_MAJOR_PORT3,
    GPIO_MAJOR_PORT4
};

enum _gpio_minor_type 
{
    GPIO_MINOR_PIN0,
    GPIO_MINOR_PIN1,
    GPIO_MINOR_PIN2,
    GPIO_MINOR_PIN3,
    GPIO_MINOR_PIN4,
    GPIO_MINOR_PIN5,
    GPIO_MINOR_PIN6,
    GPIO_MINOR_PIN7
};

typedef enum _gpio_pin_type gpio_pin;
typedef enum _gpio_pin_mode gpio_mode;
typedef enum _gpio_pin_value gpio_value;
typedef enum _gpio_major_type gpio_major_pin;
typedef enum _gpio_minor_type gpio_minor_pin;

/*
#define STATUS_TX_LED_PIN GPIO_P1_6
#define STATUS_RX_LED_PIN GPIO_P1_5
*/

#define STATUS_TX_LED_PIN GPIO_P3_4
#define STATUS_RX_LED_PIN GPIO_P3_5
#define HEARTBEAT_PIN GPIO_P4_7
#define TLV563X_LDAC_PIN GPIO_P1_7

#endif