EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
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
LIBS:nixies-us
LIBS:nixie_breadboard-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L IN-14 N1
U 1 1 5C2B38DA
P 3650 2450
F 0 "N1" H 3550 3175 45  0000 L BNN
F 1 "IN-14" H 3650 2450 45  0001 L BNN
F 2 "nixies-us:nixies-us-IN-14" H 3680 2600 20  0001 C CNN
F 3 "" H 3650 2450 60  0001 C CNN
	1    3650 2450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x10 J1
U 1 1 5C2B3944
P 2950 2450
F 0 "J1" H 2950 2950 50  0000 C CNN
F 1 "Conn_01x10" H 2950 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 2950 2450 50  0001 C CNN
F 3 "" H 2950 2450 50  0001 C CNN
	1    2950 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3150 2050 3350 2050
Wire Wire Line
	3150 2150 3350 2150
Wire Wire Line
	3150 2250 3350 2250
Wire Wire Line
	3150 2350 3350 2350
Wire Wire Line
	3150 2450 3350 2450
Wire Wire Line
	3150 2550 3350 2550
Wire Wire Line
	3150 2650 3350 2650
Wire Wire Line
	3150 2750 3350 2750
Wire Wire Line
	3150 2850 3350 2850
Wire Wire Line
	3150 2950 3350 2950
$Comp
L Conn_01x05 J2
U 1 1 5C2B3A60
P 4900 2750
F 0 "J2" H 4900 3050 50  0000 C CNN
F 1 "Conn_01x05" H 4900 2400 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 4900 2750 50  0001 C CNN
F 3 "" H 4900 2750 50  0001 C CNN
	1    4900 2750
	1    0    0    1   
$EndComp
Wire Wire Line
	4050 2050 4550 2050
Wire Wire Line
	4550 2050 4550 2650
Wire Wire Line
	4050 2950 4300 2950
Wire Wire Line
	4300 2950 4300 2750
Wire Wire Line
	4300 2750 4700 2750
$Comp
L LED D1
U 1 1 5C2B3C97
P 3700 3400
F 0 "D1" H 3700 3500 50  0000 C CNN
F 1 "LED" H 3700 3300 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 3700 3400 50  0001 C CNN
F 3 "" H 3700 3400 50  0001 C CNN
	1    3700 3400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5C2B3CEE
P 4300 2550
F 0 "R1" V 4350 2750 50  0000 C CNN
F 1 "22k" V 4300 2550 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4230 2550 50  0001 C CNN
F 3 "" H 4300 2550 50  0001 C CNN
	1    4300 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 2550 4150 2550
Wire Wire Line
	4450 2550 4700 2550
$Comp
L R R2
U 1 1 5C2B3EBE
P 4300 3400
F 0 "R2" V 4350 3600 50  0000 C CNN
F 1 "390" V 4300 3400 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4230 3400 50  0001 C CNN
F 3 "" H 4300 3400 50  0001 C CNN
	1    4300 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3400 4150 3400
Wire Wire Line
	4450 3400 4550 3400
$Comp
L GND #PWR01
U 1 1 5C2B40B5
P 3200 3500
F 0 "#PWR01" H 3200 3250 50  0001 C CNN
F 1 "GND" H 3200 3350 50  0000 C CNN
F 2 "" H 3200 3500 50  0001 C CNN
F 3 "" H 3200 3500 50  0001 C CNN
	1    3200 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3500 3200 3400
Wire Wire Line
	3200 3400 3550 3400
$Comp
L GND #PWR02
U 1 1 5C2B4121
P 4400 2950
F 0 "#PWR02" H 4400 2700 50  0001 C CNN
F 1 "GND" H 4400 2800 50  0000 C CNN
F 2 "" H 4400 2950 50  0001 C CNN
F 3 "" H 4400 2950 50  0001 C CNN
	1    4400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3400 4550 2950
Wire Wire Line
	4550 2950 4700 2950
Wire Wire Line
	4400 2850 4700 2850
Wire Wire Line
	4550 2650 4700 2650
Wire Wire Line
	4400 2950 4400 2850
$EndSCHEMATC
