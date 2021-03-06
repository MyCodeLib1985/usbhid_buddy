EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:microchip-ic
LIBS:usb
LIBS:ldo
LIBS:tactile
LIBS:leds
LIBS:reference
LIBS:switching_charge_pump
LIBS:dac_spi
LIBS:silabs
LIBS:esd_protection
LIBS:digital_switches
LIBS:open-project
LIBS:usbhid_daq-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_02X05 P6
U 1 1 56F72303
P 3200 2350
F 0 "P6" H 3200 2650 50  0000 C CNN
F 1 "CONN_02X05" H 3200 2050 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_2x05" H 3200 1150 50  0001 C CNN
F 3 "" H 3200 1150 50  0000 C CNN
	1    3200 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 56F724F0
P 2800 2000
F 0 "#PWR016" H 2800 1750 50  0001 C CNN
F 1 "GND" H 2800 1850 50  0000 C CNN
F 2 "" H 2800 2000 50  0000 C CNN
F 3 "" H 2800 2000 50  0000 C CNN
	1    2800 2000
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR017
U 1 1 56F7252B
P 3600 2700
F 0 "#PWR017" H 3600 2550 50  0001 C CNN
F 1 "+3.3V" H 3600 2840 50  0000 C CNN
F 2 "" H 3600 2700 50  0000 C CNN
F 3 "" H 3600 2700 50  0000 C CNN
	1    3600 2700
	-1   0    0    1   
$EndComp
$Comp
L REF3325AIDBZR U5
U 1 1 56F725D1
P 2850 5200
F 0 "U5" H 2850 5500 60  0000 C CNN
F 1 "REF3325AIDBZR" H 2850 5100 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2800 5100 60  0001 C CNN
F 3 "http://www.mouser.com/ds/2/405/ref3325-443764.pdf" H 2800 5100 60  0001 C CNN
F 4 "595-REF3325AIDBZR" H 2850 5200 60  0001 C CNN "Supplier Part Number"
	1    2850 5200
	1    0    0    -1  
$EndComp
Text GLabel 2250 5050 0    60   Input ~ 0
VBUS
$Comp
L C C13
U 1 1 56F72C9D
P 3750 5300
F 0 "C13" H 3775 5400 50  0000 L CNN
F 1 "100nF" H 3775 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3788 5150 50  0001 C CNN
F 3 "" H 3750 5300 50  0000 C CNN
	1    3750 5300
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 56F72D12
P 4200 5300
F 0 "C14" H 4225 5400 50  0000 L CNN
F 1 "1uF" H 4225 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4238 5150 50  0001 C CNN
F 3 "" H 4200 5300 50  0000 C CNN
	1    4200 5300
	1    0    0    -1  
$EndComp
$Comp
L TPS60241 U4
U 1 1 56F72DE3
P 7150 5550
F 0 "U4" H 7250 6400 60  0000 C CNN
F 1 "TPS60241" H 7250 5600 60  0000 C CNN
F 2 "switching_charge_pump:VSSOP8-DGK" H 7150 5550 60  0001 C CNN
F 3 "http://www.mouser.com/ds/2/405/tps60241-451686.pdf" H 7150 5550 60  0001 C CNN
F 4 "595-TPS60241DGKR" H 7150 5550 60  0001 C CNN "Supplier Part Number"
	1    7150 5550
	1    0    0    -1  
$EndComp
Text GLabel 6700 5350 0    60   Input ~ 0
VBUS
$Comp
L C C4
U 1 1 56F7305B
P 6050 5250
F 0 "C4" H 6075 5350 50  0000 L CNN
F 1 "1uF" H 6075 5150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6088 5100 50  0001 C CNN
F 3 "" H 6050 5250 50  0000 C CNN
	1    6050 5250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 56F730DE
P 5750 5100
F 0 "C2" H 5775 5200 50  0000 L CNN
F 1 "1uF" H 5775 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5788 4950 50  0001 C CNN
F 3 "" H 5750 5100 50  0000 C CNN
	1    5750 5100
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 56F732FF
P 8150 5250
F 0 "C5" H 8175 5350 50  0000 L CNN
F 1 "1uF" H 8175 5150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8188 5100 50  0001 C CNN
F 3 "" H 8150 5250 50  0000 C CNN
	1    8150 5250
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 56F733C0
P 8450 5100
F 0 "C9" H 8475 5200 50  0000 L CNN
F 1 "1uF" H 8475 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8488 4950 50  0001 C CNN
F 3 "" H 8450 5100 50  0000 C CNN
	1    8450 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 56F7379B
P 7750 5550
F 0 "#PWR018" H 7750 5300 50  0001 C CNN
F 1 "GND" H 7750 5400 50  0000 C CNN
F 2 "" H 7750 5550 50  0000 C CNN
F 3 "" H 7750 5550 50  0000 C CNN
	1    7750 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 56F73944
P 3750 5700
F 0 "#PWR019" H 3750 5450 50  0001 C CNN
F 1 "GND" H 3750 5550 50  0000 C CNN
F 2 "" H 3750 5700 50  0000 C CNN
F 3 "" H 3750 5700 50  0000 C CNN
	1    3750 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 56F73A06
P 3400 5250
F 0 "#PWR020" H 3400 5000 50  0001 C CNN
F 1 "GND" H 3400 5100 50  0000 C CNN
F 2 "" H 3400 5250 50  0000 C CNN
F 3 "" H 3400 5250 50  0000 C CNN
	1    3400 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 56F73AE7
P 5750 5400
F 0 "#PWR021" H 5750 5150 50  0001 C CNN
F 1 "GND" H 5750 5250 50  0000 C CNN
F 2 "" H 5750 5400 50  0000 C CNN
F 3 "" H 5750 5400 50  0000 C CNN
	1    5750 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 56F73D98
P 8450 5400
F 0 "#PWR022" H 8450 5150 50  0001 C CNN
F 1 "GND" H 8450 5250 50  0000 C CNN
F 2 "" H 8450 5400 50  0000 C CNN
F 3 "" H 8450 5400 50  0000 C CNN
	1    8450 5400
	1    0    0    -1  
$EndComp
$Comp
L TLV5630 U3
U 1 1 56F7400D
P 7500 2550
F 0 "U3" H 7400 3350 60  0000 C CNN
F 1 "TLV5630" H 7450 1850 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 7500 2550 60  0001 C CNN
F 3 "http://www.mouser.com/ds/2/405/tlv5630-447773.pdf" H 7500 2550 60  0001 C CNN
F 4 "595-TLV5630IPW" H 7500 2550 60  0001 C CNN "Supplier Part Number"
	1    7500 2550
	1    0    0    -1  
$EndComp
Text HLabel 6450 1950 0    60   Input ~ 0
SPI_SCLK
Text HLabel 6450 2050 0    60   Input ~ 0
SPI_SIMO
Text HLabel 6450 2150 0    60   Output ~ 0
SPI_SOMI
Text HLabel 6450 2250 0    60   Input ~ 0
SPI_CS
Text HLabel 5700 2650 0    60   Input ~ 0
MCU_LDAC
$Comp
L R R4
U 1 1 56F7475F
P 5850 2950
F 0 "R4" V 5930 2950 50  0000 C CNN
F 1 "0R" V 5850 2950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5780 2950 50  0001 C CNN
F 3 "" H 5850 2950 50  0000 C CNN
	1    5850 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 56F74813
P 5850 3300
F 0 "#PWR023" H 5850 3050 50  0001 C CNN
F 1 "GND" H 5850 3150 50  0000 C CNN
F 2 "" H 5850 3300 50  0000 C CNN
F 3 "" H 5850 3300 50  0000 C CNN
	1    5850 3300
	1    0    0    -1  
$EndComp
Text GLabel 5550 4900 0    60   Input ~ 0
VBUS
$Comp
L +5V #PWR024
U 1 1 56F75102
P 8650 4900
F 0 "#PWR024" H 8650 4750 50  0001 C CNN
F 1 "+5V" H 8650 5040 50  0000 C CNN
F 2 "" H 8650 4900 50  0000 C CNN
F 3 "" H 8650 4900 50  0000 C CNN
	1    8650 4900
	0    1    1    0   
$EndComp
$Comp
L C C7
U 1 1 56F759A2
P 6300 3450
F 0 "C7" H 6325 3550 50  0000 L CNN
F 1 "100nF" H 6325 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6338 3300 50  0001 C CNN
F 3 "" H 6300 3450 50  0000 C CNN
	1    6300 3450
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 56F75A03
P 6900 3450
F 0 "C8" H 6925 3550 50  0000 L CNN
F 1 "1uF" H 6925 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6938 3300 50  0001 C CNN
F 3 "" H 6900 3450 50  0000 C CNN
	1    6900 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 56F75B1E
P 6300 3750
F 0 "#PWR025" H 6300 3500 50  0001 C CNN
F 1 "GND" H 6300 3600 50  0000 C CNN
F 2 "" H 6300 3750 50  0000 C CNN
F 3 "" H 6300 3750 50  0000 C CNN
	1    6300 3750
	1    0    0    -1  
$EndComp
Text Label 6500 1950 0    60   ~ 0
SPI_SCLK
Text Label 6500 2050 0    60   ~ 0
SPI_SIMO
Text Label 6500 2150 0    60   ~ 0
SPI_SOMI
Text Label 6500 2250 0    60   ~ 0
SPI_CS
$Comp
L GND #PWR026
U 1 1 56F76176
P 8100 3250
F 0 "#PWR026" H 8100 3000 50  0001 C CNN
F 1 "GND" H 8100 3100 50  0000 C CNN
F 2 "" H 8100 3250 50  0000 C CNN
F 3 "" H 8100 3250 50  0000 C CNN
	1    8100 3250
	1    0    0    -1  
$EndComp
Text Label 7950 1950 0    60   ~ 0
DAC_OUTA
Text Label 7950 2050 0    60   ~ 0
DAC_OUTB
Text Label 7950 2150 0    60   ~ 0
DAC_OUTC
Text Label 7950 2250 0    60   ~ 0
DAC_OUTD
Text Label 7950 2350 0    60   ~ 0
DAC_OUTE
Text Label 7950 2450 0    60   ~ 0
DAC_OUTF
Text Label 7950 2550 0    60   ~ 0
DAC_OUTG
Text Label 7950 2650 0    60   ~ 0
DAC_OUTH
Text Label 3400 5050 0    60   ~ 0
DAC_REF_V2_5
Text Label 8000 2850 0    60   ~ 0
DAC_REF_V2_5
$Comp
L +3.3V #PWR027
U 1 1 5701F7D9
P 6750 3100
F 0 "#PWR027" H 6750 2950 50  0001 C CNN
F 1 "+3.3V" H 6750 3240 50  0000 C CNN
F 2 "" H 6750 3100 50  0000 C CNN
F 3 "" H 6750 3100 50  0000 C CNN
	1    6750 3100
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR028
U 1 1 5701FA81
P 6750 2450
F 0 "#PWR028" H 6750 2300 50  0001 C CNN
F 1 "+3.3V" H 6750 2590 50  0000 C CNN
F 2 "" H 6750 2450 50  0000 C CNN
F 3 "" H 6750 2450 50  0000 C CNN
	1    6750 2450
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR029
U 1 1 57037761
P 6200 3100
F 0 "#PWR029" H 6200 2950 50  0001 C CNN
F 1 "+5V" H 6200 3240 50  0000 C CNN
F 2 "" H 6200 3100 50  0000 C CNN
F 3 "" H 6200 3100 50  0000 C CNN
	1    6200 3100
	0    -1   -1   0   
$EndComp
Text Label 3550 2250 0    60   ~ 0
DAC_OUTA
Text Label 3550 2150 0    60   ~ 0
DAC_OUTB
Text Label 2450 2250 0    60   ~ 0
DAC_OUTC
Text HLabel 8450 2650 2    60   Input ~ 0
ADC0_IN
Text HLabel 8450 2550 2    60   Input ~ 0
ADC1_IN
Text HLabel 8450 2450 2    60   Input ~ 0
ADC2_IN
Text HLabel 8450 2350 2    60   Input ~ 0
ADC3_IN
Text HLabel 8450 2250 2    60   Input ~ 0
ADC4_IN
Text HLabel 8450 2150 2    60   Input ~ 0
ADC5_IN
Text HLabel 8450 2050 2    60   Input ~ 0
ADC6_IN
Text HLabel 8450 1950 2    60   Input ~ 0
ADC7_IN
Text Label 3550 2350 0    60   ~ 0
DAC_OUTH
Text Label 3550 2450 0    60   ~ 0
DAC_OUTG
Text Label 2450 2550 0    60   ~ 0
DAC_OUTF
Text Label 2450 2450 0    60   ~ 0
DAC_OUTE
Text Label 2450 2350 0    60   ~ 0
DAC_OUTD
Wire Wire Line
	2450 5050 2250 5050
Wire Wire Line
	6900 5350 6700 5350
Wire Wire Line
	7650 4900 8650 4900
Wire Wire Line
	8450 4900 8450 4950
Wire Wire Line
	5550 4900 6900 4900
Wire Wire Line
	5750 4900 5750 4950
Wire Wire Line
	6900 5050 6050 5050
Wire Wire Line
	6050 5050 6050 5100
Wire Wire Line
	6050 5400 6050 5450
Wire Wire Line
	6050 5450 6300 5450
Wire Wire Line
	6300 5450 6300 5150
Wire Wire Line
	6300 5150 6900 5150
Wire Wire Line
	7650 5050 8150 5050
Wire Wire Line
	8150 5050 8150 5100
Wire Wire Line
	7650 5150 7950 5150
Wire Wire Line
	7950 5150 7950 5500
Wire Wire Line
	7950 5500 8150 5500
Wire Wire Line
	8150 5500 8150 5400
Wire Wire Line
	7650 5350 7750 5350
Wire Wire Line
	7750 5350 7750 5550
Wire Wire Line
	3200 5050 4200 5050
Wire Wire Line
	4200 5050 4200 5150
Wire Wire Line
	3750 5150 3750 5050
Connection ~ 3750 5050
Wire Wire Line
	3750 5700 3750 5450
Wire Wire Line
	4200 5450 4200 5550
Wire Wire Line
	4200 5550 3750 5550
Connection ~ 3750 5550
Wire Wire Line
	3200 5150 3400 5150
Wire Wire Line
	3400 5150 3400 5250
Wire Wire Line
	5750 5400 5750 5250
Wire Wire Line
	8450 5400 8450 5250
Wire Wire Line
	7000 1950 6450 1950
Wire Wire Line
	7000 2050 6450 2050
Wire Wire Line
	7000 2150 6450 2150
Wire Wire Line
	7000 2250 6450 2250
Connection ~ 5750 4900
Connection ~ 8450 4900
Wire Wire Line
	7850 3000 8100 3000
Wire Wire Line
	8100 3000 8100 3250
Wire Wire Line
	7850 3100 7950 3100
Wire Wire Line
	7950 3100 7950 3000
Connection ~ 7950 3000
Wire Wire Line
	7850 1950 8450 1950
Wire Wire Line
	7850 2050 8450 2050
Wire Wire Line
	7850 2150 8450 2150
Wire Wire Line
	7850 2250 8450 2250
Wire Wire Line
	7850 2350 8450 2350
Wire Wire Line
	7850 2450 8450 2450
Wire Wire Line
	7850 2550 8450 2550
Wire Wire Line
	7850 2650 8450 2650
Wire Wire Line
	7850 2850 8850 2850
Wire Wire Line
	7000 2450 6750 2450
Wire Wire Line
	7000 2350 6900 2350
Wire Wire Line
	6900 2350 6900 2450
Connection ~ 6900 2450
Wire Wire Line
	5850 3300 5850 3100
Wire Wire Line
	5700 2650 7000 2650
Wire Wire Line
	5850 2800 5850 2650
Connection ~ 5850 2650
Wire Wire Line
	6200 3100 6300 3100
Wire Wire Line
	6300 2900 6300 3300
Wire Wire Line
	6750 3100 6900 3100
Wire Wire Line
	6900 3000 6900 3300
Wire Wire Line
	6300 3750 6300 3600
Wire Wire Line
	6300 3700 6900 3700
Wire Wire Line
	6900 3700 6900 3600
Connection ~ 6300 3700
Wire Wire Line
	7000 3000 6900 3000
Connection ~ 6900 3100
Wire Wire Line
	7000 2900 6300 2900
Connection ~ 6300 3100
Wire Wire Line
	2950 2150 2800 2150
Wire Wire Line
	2800 2150 2800 2000
Wire Wire Line
	3450 2550 3600 2550
Wire Wire Line
	3600 2550 3600 2700
Wire Wire Line
	3450 2450 4050 2450
Wire Wire Line
	3450 2350 4050 2350
Wire Wire Line
	2950 2550 2350 2550
Wire Wire Line
	2950 2450 2350 2450
Wire Wire Line
	3450 2150 4050 2150
Wire Wire Line
	3450 2250 4050 2250
Wire Wire Line
	2950 2250 2350 2250
Wire Wire Line
	2950 2350 2350 2350
$EndSCHEMATC
