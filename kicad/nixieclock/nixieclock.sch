EESchema Schematic File Version 4
EELAYER 30 0
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
L nixieclock-rescue:IN-14-nixieclock-rescue N1
U 1 1 5C6AF2ED
P 4400 4450
F 0 "N1" H 4300 5175 45  0000 L BNN
F 1 "IN-14" H 4400 4450 45  0001 L BNN
F 2 "nixie:nixies-us-IN-14" H 4430 4600 20  0001 C CNN
F 3 "" H 4400 4450 60  0001 C CNN
	1    4400 4450
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:IN-14-nixieclock-rescue N2
U 1 1 5C6AF38C
P 6450 4450
F 0 "N2" H 6350 5175 45  0000 L BNN
F 1 "IN-14" H 6450 4450 45  0001 L BNN
F 2 "nixie:nixies-us-IN-14" H 6480 4600 20  0001 C CNN
F 3 "" H 6450 4450 60  0001 C CNN
	1    6450 4450
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:IN-14-nixieclock-rescue N3
U 1 1 5C6AF445
P 8550 4450
F 0 "N3" H 8450 5175 45  0000 L BNN
F 1 "IN-14" H 8550 4450 45  0001 L BNN
F 2 "nixie:nixies-us-IN-14" H 8580 4600 20  0001 C CNN
F 3 "" H 8550 4450 60  0001 C CNN
	1    8550 4450
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:IN-14-nixieclock-rescue N4
U 1 1 5C6AF49B
P 10600 4450
F 0 "N4" H 10500 5175 45  0000 L BNN
F 1 "IN-14" H 10600 4450 45  0001 L BNN
F 2 "nixie:nixies-us-IN-14" H 10630 4600 20  0001 C CNN
F 3 "" H 10600 4450 60  0001 C CNN
	1    10600 4450
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:74141-nixieclock-rescue U3
U 1 1 5C6AF51F
P 1800 6050
F 0 "U3" H 1800 6050 50  0000 C CNN
F 1 "74141" H 2100 5450 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 1800 6050 60  0001 C CNN
F 3 "" H 1800 6050 60  0001 C CNN
	1    1800 6050
	1    0    0    -1  
$EndComp
NoConn ~ 4800 4050
NoConn ~ 4800 4950
NoConn ~ 6850 4050
NoConn ~ 6850 4950
NoConn ~ 8950 4050
NoConn ~ 8950 4950
NoConn ~ 11000 4050
NoConn ~ 11000 4950
$Comp
L nixieclock-rescue:ATMEGA88PA-PU-nixieclock-rescue U2
U 1 1 5C6B0EC5
P 1500 3600
F 0 "U2" H 750 4850 50  0000 L BNN
F 1 "ATMEGA88PA-PU" H 1900 2200 50  0000 L BNN
F 2 "Package_DIP:DIP-28_W7.62mm_Socket_LongPads" H 1500 3600 50  0001 C CIN
F 3 "" H 1500 3600 50  0001 C CNN
	1    1500 3600
	1    0    0    -1  
$EndComp
Text Label 950  5900 0    60   ~ 0
A
Text Label 950  6000 0    60   ~ 0
B
Text Label 950  6100 0    60   ~ 0
C
Text Label 950  6200 0    60   ~ 0
D
Text Label 2600 3350 0    60   ~ 0
A
Text Label 2600 3450 0    60   ~ 0
B
Text Label 2600 3550 0    60   ~ 0
C
Text Label 2600 3650 0    60   ~ 0
D
$Comp
L nixieclock-rescue:L7805-nixieclock-rescue U1
U 1 1 5C6B124F
P 850 -1750
F 0 "U1" H 700 -1625 50  0000 C CNN
F 1 "L7805" H 850 -1625 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 875 -1900 50  0001 L CIN
F 3 "" H 850 -1800 50  0001 C CNN
	1    850  -1750
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR04
U 1 1 5C6B13EE
P 850 -1350
F 0 "#PWR04" H 850 -1600 50  0001 C CNN
F 1 "GND" H 850 -1500 50  0000 C CNN
F 2 "" H 850 -1350 50  0001 C CNN
F 3 "" H 850 -1350 50  0001 C CNN
	1    850  -1350
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:+12V-nixieclock-rescue #PWR01
U 1 1 5C6B1499
P 300 -1950
F 0 "#PWR01" H 300 -2100 50  0001 C CNN
F 1 "+12V" H 300 -1810 50  0000 C CNN
F 2 "" H 300 -1950 50  0001 C CNN
F 3 "" H 300 -1950 50  0001 C CNN
	1    300  -1950
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:+5V-nixieclock-rescue #PWR05
U 1 1 5C6B1545
P 1500 -2000
F 0 "#PWR05" H 1500 -2150 50  0001 C CNN
F 1 "+5V" H 1500 -1860 50  0000 C CNN
F 2 "" H 1500 -2000 50  0001 C CNN
F 3 "" H 1500 -2000 50  0001 C CNN
	1    1500 -2000
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:+5V-nixieclock-rescue #PWR02
U 1 1 5C6B17A0
P 550 2100
F 0 "#PWR02" H 550 1950 50  0001 C CNN
F 1 "+5V" H 550 2240 50  0000 C CNN
F 2 "" H 550 2100 50  0001 C CNN
F 3 "" H 550 2100 50  0001 C CNN
	1    550  2100
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR03
U 1 1 5C6B19C4
P 800 4200
F 0 "#PWR03" H 800 3950 50  0001 C CNN
F 1 "GND" H 800 4050 50  0000 C CNN
F 2 "" H 800 4200 50  0001 C CNN
F 3 "" H 800 4200 50  0001 C CNN
	1    800  4200
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:Crystal-nixieclock-rescue Y1
U 1 1 5C6B1D8D
P 2750 3050
F 0 "Y1" H 2750 3200 50  0000 C CNN
F 1 "32.768kHz" H 2750 2900 50  0000 C CNN
F 2 "Crystal:Crystal_C38-LF_D3.0mm_L8.0mm_Horizontal" H 2750 3050 50  0001 C CNN
F 3 "" H 2750 3050 50  0001 C CNN
	1    2750 3050
	0    -1   -1   0   
$EndComp
$Comp
L nixieclock-rescue:MPSA42-nixieclock-rescue Q1
U 1 1 5C6B204C
P 3850 2050
F 0 "Q1" H 4050 2125 50  0000 L CNN
F 1 "MPSA42" H 4050 2050 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 4050 1975 50  0001 L CIN
F 3 "" H 3850 2050 50  0001 L CNN
	1    3850 2050
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R5
U 1 1 5C6B26F3
P 2750 2500
F 0 "R5" V 2700 2650 50  0000 C CNN
F 1 "10k" V 2750 2500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2680 2500 50  0001 C CNN
F 3 "" H 2750 2500 50  0001 C CNN
	1    2750 2500
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R10
U 1 1 5C6B27D4
P 3950 1650
F 0 "R10" V 4030 1650 50  0000 C CNN
F 1 "1M" V 3950 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3880 1650 50  0001 C CNN
F 3 "" H 3950 1650 50  0001 C CNN
	1    3950 1650
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R11
U 1 1 5C6B28D4
P 4600 1650
F 0 "R11" V 4680 1650 50  0000 C CNN
F 1 "R" V 4600 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4530 1650 50  0001 C CNN
F 3 "" H 4600 1650 50  0001 C CNN
	1    4600 1650
	0    -1   -1   0   
$EndComp
$Comp
L nixieclock-rescue:MPSA92-nixieclock-rescue Q2
U 1 1 5C6B293C
P 4250 1450
F 0 "Q2" H 4450 1525 50  0000 L CNN
F 1 "MPSA92" H 4450 1450 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 4450 1375 50  0001 L CIN
F 3 "" H 4250 1450 50  0001 L CNN
	1    4250 1450
	1    0    0    1   
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR011
U 1 1 5C6B2FF8
P 3950 2300
F 0 "#PWR011" H 3950 2050 50  0001 C CNN
F 1 "GND" H 3950 2150 50  0000 C CNN
F 2 "" H 3950 2300 50  0001 C CNN
F 3 "" H 3950 2300 50  0001 C CNN
	1    3950 2300
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R6
U 1 1 5C6B38EA
P 2750 2600
F 0 "R6" V 2700 2750 50  0000 C CNN
F 1 "10k" V 2750 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2680 2600 50  0001 C CNN
F 3 "" H 2750 2600 50  0001 C CNN
	1    2750 2600
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R7
U 1 1 5C6B399D
P 2750 2700
F 0 "R7" V 2700 2850 50  0000 C CNN
F 1 "10k" V 2750 2700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2680 2700 50  0001 C CNN
F 3 "" H 2750 2700 50  0001 C CNN
	1    2750 2700
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R8
U 1 1 5C6B39DD
P 2750 2800
F 0 "R8" V 2700 2950 50  0000 C CNN
F 1 "10k" V 2750 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2680 2800 50  0001 C CNN
F 3 "" H 2750 2800 50  0001 C CNN
	1    2750 2800
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:MPSA42-nixieclock-rescue Q3
U 1 1 5C6B3C08
P 6000 2050
F 0 "Q3" H 6200 2125 50  0000 L CNN
F 1 "MPSA42" H 6200 2050 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 6200 1975 50  0001 L CIN
F 3 "" H 6000 2050 50  0001 L CNN
	1    6000 2050
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R13
U 1 1 5C6B3C0E
P 6100 1650
F 0 "R13" V 6180 1650 50  0000 C CNN
F 1 "1M" V 6100 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6030 1650 50  0001 C CNN
F 3 "" H 6100 1650 50  0001 C CNN
	1    6100 1650
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R14
U 1 1 5C6B3C1A
P 6750 1650
F 0 "R14" V 6830 1650 50  0000 C CNN
F 1 "R" V 6750 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6680 1650 50  0001 C CNN
F 3 "" H 6750 1650 50  0001 C CNN
	1    6750 1650
	0    -1   -1   0   
$EndComp
$Comp
L nixieclock-rescue:MPSA92-nixieclock-rescue Q4
U 1 1 5C6B3C20
P 6400 1450
F 0 "Q4" H 6600 1525 50  0000 L CNN
F 1 "MPSA92" H 6600 1450 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 6600 1375 50  0001 L CIN
F 3 "" H 6400 1450 50  0001 L CNN
	1    6400 1450
	1    0    0    1   
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR013
U 1 1 5C6B3C2B
P 6100 2300
F 0 "#PWR013" H 6100 2050 50  0001 C CNN
F 1 "GND" H 6100 2150 50  0000 C CNN
F 2 "" H 6100 2300 50  0001 C CNN
F 3 "" H 6100 2300 50  0001 C CNN
	1    6100 2300
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:MPSA42-nixieclock-rescue Q5
U 1 1 5C6B3DA4
P 8100 2050
F 0 "Q5" H 8300 2125 50  0000 L CNN
F 1 "MPSA42" H 8300 2050 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 8300 1975 50  0001 L CIN
F 3 "" H 8100 2050 50  0001 L CNN
	1    8100 2050
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R16
U 1 1 5C6B3DAA
P 8200 1650
F 0 "R16" V 8280 1650 50  0000 C CNN
F 1 "1M" V 8200 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8130 1650 50  0001 C CNN
F 3 "" H 8200 1650 50  0001 C CNN
	1    8200 1650
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R17
U 1 1 5C6B3DB6
P 8850 1650
F 0 "R17" V 8930 1650 50  0000 C CNN
F 1 "R" V 8850 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8780 1650 50  0001 C CNN
F 3 "" H 8850 1650 50  0001 C CNN
	1    8850 1650
	0    -1   -1   0   
$EndComp
$Comp
L nixieclock-rescue:MPSA92-nixieclock-rescue Q6
U 1 1 5C6B3DBC
P 8500 1450
F 0 "Q6" H 8700 1525 50  0000 L CNN
F 1 "MPSA92" H 8700 1450 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 8700 1375 50  0001 L CIN
F 3 "" H 8500 1450 50  0001 L CNN
	1    8500 1450
	1    0    0    1   
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR015
U 1 1 5C6B3DC7
P 8200 2300
F 0 "#PWR015" H 8200 2050 50  0001 C CNN
F 1 "GND" H 8200 2150 50  0000 C CNN
F 2 "" H 8200 2300 50  0001 C CNN
F 3 "" H 8200 2300 50  0001 C CNN
	1    8200 2300
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:MPSA42-nixieclock-rescue Q7
U 1 1 5C6B3F72
P 10150 2050
F 0 "Q7" H 10350 2125 50  0000 L CNN
F 1 "MPSA42" H 10350 2050 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 10350 1975 50  0001 L CIN
F 3 "" H 10150 2050 50  0001 L CNN
	1    10150 2050
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R19
U 1 1 5C6B3F78
P 10250 1650
F 0 "R19" V 10330 1650 50  0000 C CNN
F 1 "1M" V 10250 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 10180 1650 50  0001 C CNN
F 3 "" H 10250 1650 50  0001 C CNN
	1    10250 1650
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R20
U 1 1 5C6B3F84
P 10900 1650
F 0 "R20" V 10980 1650 50  0000 C CNN
F 1 "R" V 10900 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 10830 1650 50  0001 C CNN
F 3 "" H 10900 1650 50  0001 C CNN
	1    10900 1650
	0    -1   -1   0   
$EndComp
$Comp
L nixieclock-rescue:MPSA92-nixieclock-rescue Q8
U 1 1 5C6B3F8A
P 10550 1450
F 0 "Q8" H 10750 1525 50  0000 L CNN
F 1 "MPSA92" H 10750 1450 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 10750 1375 50  0001 L CIN
F 3 "" H 10550 1450 50  0001 L CNN
	1    10550 1450
	1    0    0    1   
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR017
U 1 1 5C6B3F95
P 10250 2300
F 0 "#PWR017" H 10250 2050 50  0001 C CNN
F 1 "GND" H 10250 2150 50  0000 C CNN
F 2 "" H 10250 2300 50  0001 C CNN
F 3 "" H 10250 2300 50  0001 C CNN
	1    10250 2300
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R9
U 1 1 5C6B8086
P 3950 1250
F 0 "R9" V 3900 1400 50  0000 C CNN
F 1 "10k" V 3950 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3880 1250 50  0001 C CNN
F 3 "" H 3950 1250 50  0001 C CNN
	1    3950 1250
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R12
U 1 1 5C6B8140
P 6100 1250
F 0 "R12" V 6050 1400 50  0000 C CNN
F 1 "10k" V 6100 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6030 1250 50  0001 C CNN
F 3 "" H 6100 1250 50  0001 C CNN
	1    6100 1250
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R15
U 1 1 5C6B81DA
P 8200 1250
F 0 "R15" V 8150 1400 50  0000 C CNN
F 1 "10k" V 8200 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8130 1250 50  0001 C CNN
F 3 "" H 8200 1250 50  0001 C CNN
	1    8200 1250
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R18
U 1 1 5C6B82ED
P 10250 1250
F 0 "R18" V 10200 1400 50  0000 C CNN
F 1 "10k" V 10250 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 10180 1250 50  0001 C CNN
F 3 "" H 10250 1250 50  0001 C CNN
	1    10250 1250
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:LED-nixieclock-rescue D3
U 1 1 5C6B84A7
P 2100 -1500
F 0 "D3" H 2100 -1400 50  0000 C CNN
F 1 "LED" H 2100 -1600 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm_Clear" H 2100 -1500 50  0001 C CNN
F 3 "" H 2100 -1500 50  0001 C CNN
	1    2100 -1500
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:LED-nixieclock-rescue D4
U 1 1 5C6B8559
P 2100 -1300
F 0 "D4" H 2100 -1200 50  0000 C CNN
F 1 "LED" H 2100 -1400 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm_Clear" H 2100 -1300 50  0001 C CNN
F 3 "" H 2100 -1300 50  0001 C CNN
	1    2100 -1300
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:LED-nixieclock-rescue D5
U 1 1 5C6B85DD
P 2100 -1100
F 0 "D5" H 2100 -1000 50  0000 C CNN
F 1 "LED" H 2100 -1200 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm_Clear" H 2100 -1100 50  0001 C CNN
F 3 "" H 2100 -1100 50  0001 C CNN
	1    2100 -1100
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:LED-nixieclock-rescue D6
U 1 1 5C6B865A
P 2100 -900
F 0 "D6" H 2100 -800 50  0000 C CNN
F 1 "LED" H 2100 -1000 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm_Clear" H 2100 -900 50  0001 C CNN
F 3 "" H 2100 -900 50  0001 C CNN
	1    2100 -900
	-1   0    0    1   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R1
U 1 1 5C6B87B6
P 1700 -1500
F 0 "R1" V 1650 -1350 50  0000 C CNN
F 1 "390" V 1700 -1500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1630 -1500 50  0001 C CNN
F 3 "" H 1700 -1500 50  0001 C CNN
	1    1700 -1500
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R2
U 1 1 5C6B897A
P 1700 -1300
F 0 "R2" V 1650 -1150 50  0000 C CNN
F 1 "390" V 1700 -1300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1630 -1300 50  0001 C CNN
F 3 "" H 1700 -1300 50  0001 C CNN
	1    1700 -1300
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R3
U 1 1 5C6B8A06
P 1700 -1100
F 0 "R3" V 1650 -950 50  0000 C CNN
F 1 "390" V 1700 -1100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1630 -1100 50  0001 C CNN
F 3 "" H 1700 -1100 50  0001 C CNN
	1    1700 -1100
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:R-nixieclock-rescue R4
U 1 1 5C6B8AC2
P 1700 -900
F 0 "R4" V 1650 -750 50  0000 C CNN
F 1 "390" V 1700 -900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1630 -900 50  0001 C CNN
F 3 "" H 1700 -900 50  0001 C CNN
	1    1700 -900
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR09
U 1 1 5C6B982E
P 2350 -800
F 0 "#PWR09" H 2350 -1050 50  0001 C CNN
F 1 "GND" H 2350 -950 50  0000 C CNN
F 2 "" H 2350 -800 50  0001 C CNN
F 3 "" H 2350 -800 50  0001 C CNN
	1    2350 -800
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:SW_Push_Dual-nixieclock-rescue SW1
U 1 1 5C6C1767
P 1800 900
F 0 "SW1" H 1850 1000 50  0000 L CNN
F 1 "SW_Push_Dual" H 1800 630 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 1800 1100 50  0001 C CNN
F 3 "" H 1800 1100 50  0001 C CNN
	1    1800 900 
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:SW_Push_Dual-nixieclock-rescue SW2
U 1 1 5C6C18DB
P 1800 1450
F 0 "SW2" H 1850 1550 50  0000 L CNN
F 1 "SW_Push_Dual" H 1800 1180 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 1800 1650 50  0001 C CNN
F 3 "" H 1800 1650 50  0001 C CNN
	1    1800 1450
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR08
U 1 1 5C6C22A8
P 2050 1800
F 0 "#PWR08" H 2050 1550 50  0001 C CNN
F 1 "GND" H 2050 1650 50  0000 C CNN
F 2 "" H 2050 1800 50  0001 C CNN
F 3 "" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:+5V-nixieclock-rescue #PWR010
U 1 1 5C6C28CC
P 2700 4400
F 0 "#PWR010" H 2700 4250 50  0001 C CNN
F 1 "+5V" H 2700 4540 50  0000 C CNN
F 2 "" H 2700 4400 50  0001 C CNN
F 3 "" H 2700 4400 50  0001 C CNN
	1    2700 4400
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:Battery_Cell-nixieclock-rescue BT1
U 1 1 5C6C2B7F
P 550 3950
F 0 "BT1" H 650 4050 50  0000 L CNN
F 1 "Battery_Cell" H 650 3950 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_103_1x20mm" V 550 4010 50  0001 C CNN
F 3 "" V 550 4010 50  0001 C CNN
	1    550  3950
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:D-nixieclock-rescue D2
U 1 1 5C6C2CE8
P 550 3450
F 0 "D2" H 550 3550 50  0000 C CNN
F 1 "D" H 550 3350 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 550 3450 50  0001 C CNN
F 3 "" H 550 3450 50  0001 C CNN
	1    550  3450
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:D-nixieclock-rescue D1
U 1 1 5C6C3283
P 550 2300
F 0 "D1" H 550 2400 50  0000 C CNN
F 1 "D" H 550 2200 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 550 2300 50  0001 C CNN
F 3 "" H 550 2300 50  0001 C CNN
	1    550  2300
	0    1    1    0   
$EndComp
$Comp
L nixieclock-rescue:C-nixieclock-rescue C1
U 1 1 5C6C3F9C
P 500 -1400
F 0 "C1" H 525 -1300 50  0000 L CNN
F 1 "C" H 525 -1500 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 538 -1550 50  0001 C CNN
F 3 "" H 500 -1400 50  0001 C CNN
	1    500  -1400
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 5600 3950 5600
Wire Wire Line
	10150 5600 10150 4950
Wire Wire Line
	10150 4950 10300 4950
Wire Wire Line
	2400 5700 3000 5700
Wire Wire Line
	9250 5700 9250 4050
Wire Wire Line
	9250 4050 10300 4050
Wire Wire Line
	9350 4150 10300 4150
Wire Wire Line
	9350 5800 9350 4150
Wire Wire Line
	2400 5800 3100 5800
Wire Wire Line
	2400 5900 3200 5900
Wire Wire Line
	9450 5900 9450 4250
Wire Wire Line
	9450 4250 10300 4250
Wire Wire Line
	10300 4350 9550 4350
Wire Wire Line
	9550 4350 9550 6000
Wire Wire Line
	9550 6000 7450 6000
Wire Wire Line
	2400 6100 3400 6100
Wire Wire Line
	9650 6100 9650 4450
Wire Wire Line
	9650 4450 10300 4450
Wire Wire Line
	10300 4550 9750 4550
Wire Wire Line
	9750 4550 9750 6200
Wire Wire Line
	9750 6200 7650 6200
Wire Wire Line
	2400 6300 3600 6300
Wire Wire Line
	9850 6300 9850 4650
Wire Wire Line
	9850 4650 10300 4650
Wire Wire Line
	2400 6400 3700 6400
Wire Wire Line
	9950 6400 9950 4750
Wire Wire Line
	9950 4750 10300 4750
Wire Wire Line
	10300 4850 10050 4850
Wire Wire Line
	10050 4850 10050 6500
Wire Wire Line
	10050 6500 7950 6500
Wire Wire Line
	8250 4950 8050 4950
Wire Wire Line
	8050 4950 8050 5600
Connection ~ 8050 5600
Wire Wire Line
	8250 4850 7950 4850
Wire Wire Line
	7950 4850 7950 6500
Connection ~ 7950 6500
Wire Wire Line
	8250 4750 7850 4750
Wire Wire Line
	7850 4750 7850 6400
Connection ~ 7850 6400
Wire Wire Line
	8250 4650 7750 4650
Wire Wire Line
	7750 4650 7750 6300
Connection ~ 7750 6300
Wire Wire Line
	8250 4550 7650 4550
Wire Wire Line
	7650 4550 7650 6200
Connection ~ 7650 6200
Wire Wire Line
	8250 4450 7550 4450
Wire Wire Line
	7550 4450 7550 6100
Connection ~ 7550 6100
Wire Wire Line
	8250 4350 7450 4350
Wire Wire Line
	7450 4350 7450 6000
Connection ~ 7450 6000
Wire Wire Line
	8250 4250 7350 4250
Wire Wire Line
	7350 4250 7350 5900
Connection ~ 7350 5900
Wire Wire Line
	8250 4150 7250 4150
Wire Wire Line
	8250 4050 7150 4050
Wire Wire Line
	7150 4050 7150 5700
Connection ~ 7150 5700
Wire Wire Line
	7250 4150 7250 5800
Connection ~ 7250 5800
Wire Wire Line
	6150 4950 6000 4950
Wire Wire Line
	6000 4950 6000 5600
Connection ~ 6000 5600
Wire Wire Line
	6150 4850 5900 4850
Wire Wire Line
	5900 4850 5900 6500
Connection ~ 5900 6500
Wire Wire Line
	6150 4750 5800 4750
Wire Wire Line
	5800 4750 5800 6400
Connection ~ 5800 6400
Wire Wire Line
	6150 4650 5700 4650
Wire Wire Line
	5700 4650 5700 6300
Connection ~ 5700 6300
Wire Wire Line
	6150 4550 5600 4550
Wire Wire Line
	5600 4550 5600 6200
Connection ~ 5600 6200
Wire Wire Line
	6150 4450 5500 4450
Wire Wire Line
	5500 4450 5500 6100
Connection ~ 5500 6100
Wire Wire Line
	6150 4350 5400 4350
Wire Wire Line
	5400 4350 5400 6000
Connection ~ 5400 6000
Wire Wire Line
	6150 4250 5300 4250
Wire Wire Line
	5300 4250 5300 5900
Connection ~ 5300 5900
Wire Wire Line
	6150 4150 5200 4150
Wire Wire Line
	5200 4150 5200 5800
Connection ~ 5200 5800
Wire Wire Line
	6150 4050 5100 4050
Wire Wire Line
	5100 4050 5100 5700
Connection ~ 5100 5700
Wire Wire Line
	4100 4950 3950 4950
Wire Wire Line
	3950 4950 3950 5600
Connection ~ 3950 5600
Wire Wire Line
	4100 4850 3800 4850
Wire Wire Line
	3800 4850 3800 6500
Connection ~ 3800 6500
Wire Wire Line
	4100 4750 3700 4750
Wire Wire Line
	3700 4750 3700 6400
Connection ~ 3700 6400
Wire Wire Line
	4100 4650 3600 4650
Wire Wire Line
	3600 4650 3600 6300
Connection ~ 3600 6300
Wire Wire Line
	4100 4550 3500 4550
Wire Wire Line
	3500 4550 3500 6200
Connection ~ 3500 6200
Wire Wire Line
	4100 4450 3400 4450
Wire Wire Line
	3400 4450 3400 6100
Connection ~ 3400 6100
Wire Wire Line
	4100 4350 3300 4350
Wire Wire Line
	3300 4350 3300 6000
Connection ~ 3300 6000
Wire Wire Line
	4100 4250 3200 4250
Wire Wire Line
	3200 4250 3200 5900
Connection ~ 3200 5900
Wire Wire Line
	4100 4150 3100 4150
Wire Wire Line
	3100 4150 3100 5800
Connection ~ 3100 5800
Wire Wire Line
	4100 4050 3000 4050
Wire Wire Line
	3000 4050 3000 5700
Connection ~ 3000 5700
Wire Wire Line
	1200 5900 850  5900
Wire Wire Line
	850  6000 1200 6000
Wire Wire Line
	1200 6100 850  6100
Wire Wire Line
	1200 6200 850  6200
Wire Wire Line
	2850 3350 2500 3350
Wire Wire Line
	2500 3450 2850 3450
Wire Wire Line
	2850 3550 2500 3550
Wire Wire Line
	2850 3650 2500 3650
Wire Wire Line
	850  -1350 850  -1400
Wire Wire Line
	300  -1950 300  -1750
Wire Wire Line
	300  -1750 550  -1750
Wire Wire Line
	1150 -1750 1400 -1750
Wire Wire Line
	1500 -2000 1500 -1750
Wire Wire Line
	600  2500 550  2500
Wire Wire Line
	550  2450 550  2500
Wire Wire Line
	550  2800 600  2800
Connection ~ 550  2500
Wire Wire Line
	850  4000 800  4000
Wire Wire Line
	550  4050 550  4700
Wire Wire Line
	800  4100 850  4100
Connection ~ 800  4100
Wire Wire Line
	2500 3200 2750 3200
Wire Wire Line
	2750 2900 2550 2900
Wire Wire Line
	2550 2900 2550 3100
Wire Wire Line
	2550 3100 2500 3100
Wire Wire Line
	3950 1400 3950 1450
Wire Wire Line
	4050 1450 3950 1450
Connection ~ 3950 1450
Wire Wire Line
	3950 1800 3950 1850
Wire Wire Line
	3950 2250 3950 2300
Wire Wire Line
	3950 1100 3950 1050
Wire Wire Line
	3950 1050 4350 1050
Wire Wire Line
	4350 1650 4450 1650
Wire Wire Line
	6100 1400 6100 1450
Wire Wire Line
	6200 1450 6100 1450
Connection ~ 6100 1450
Wire Wire Line
	6100 1800 6100 1850
Wire Wire Line
	5700 2050 5800 2050
Wire Wire Line
	6100 2250 6100 2300
Wire Wire Line
	6100 1100 6100 1050
Wire Wire Line
	6100 1050 6500 1050
Wire Wire Line
	6500 1650 6600 1650
Wire Wire Line
	8200 1400 8200 1450
Wire Wire Line
	8300 1450 8200 1450
Connection ~ 8200 1450
Wire Wire Line
	8200 1800 8200 1850
Wire Wire Line
	7800 2050 7900 2050
Wire Wire Line
	8200 2250 8200 2300
Wire Wire Line
	8200 1100 8200 1050
Wire Wire Line
	8200 1050 8600 1050
Wire Wire Line
	8600 1650 8700 1650
Wire Wire Line
	10250 1400 10250 1450
Wire Wire Line
	10350 1450 10250 1450
Connection ~ 10250 1450
Wire Wire Line
	10250 1800 10250 1850
Wire Wire Line
	10250 2250 10250 2300
Wire Wire Line
	10250 1100 10250 1050
Wire Wire Line
	10250 1050 10650 1050
Wire Wire Line
	10650 1650 10750 1650
Wire Wire Line
	5700 2600 5700 2050
Wire Wire Line
	7800 2700 7800 2050
Wire Wire Line
	7000 4550 6850 4550
Wire Wire Line
	9100 4550 8950 4550
Wire Wire Line
	11000 4550 11150 4550
Wire Wire Line
	1850 -1500 1950 -1500
Wire Wire Line
	1850 -1300 1950 -1300
Wire Wire Line
	1850 -1100 1950 -1100
Wire Wire Line
	1850 -900 1950 -900
Wire Wire Line
	2250 -1500 2350 -1500
Wire Wire Line
	2350 -1500 2350 -1300
Wire Wire Line
	2250 -1300 2350 -1300
Connection ~ 2350 -1300
Wire Wire Line
	2250 -1100 2350 -1100
Connection ~ 2350 -1100
Wire Wire Line
	2250 -900 2350 -900
Connection ~ 2350 -900
Wire Wire Line
	1500 -900 1550 -900
Connection ~ 1500 -1750
Wire Wire Line
	1550 -1500 1500 -1500
Connection ~ 1500 -1500
Wire Wire Line
	1550 -1300 1500 -1300
Connection ~ 1500 -1300
Wire Wire Line
	1550 -1100 1500 -1100
Connection ~ 1500 -1100
Wire Wire Line
	9900 2800 9900 2050
Wire Wire Line
	9900 2050 9950 2050
Wire Wire Line
	3550 2050 3650 2050
Wire Wire Line
	2500 2500 2600 2500
Wire Wire Line
	2500 2600 2600 2600
Wire Wire Line
	2500 2700 2600 2700
Wire Wire Line
	2500 2800 2600 2800
Wire Wire Line
	1100 900  1600 900 
Wire Wire Line
	1600 900  1600 1100
Wire Wire Line
	2000 900  2050 900 
Wire Wire Line
	2050 900  2050 1100
Wire Wire Line
	2050 1100 2000 1100
Connection ~ 2050 1100
Wire Wire Line
	2500 4400 2700 4400
Wire Wire Line
	550  3600 550  3750
Connection ~ 550  2800
Wire Wire Line
	550  2100 550  2150
Wire Wire Line
	300  -1400 350  -1400
Connection ~ 300  -1750
Wire Wire Line
	650  -1400 850  -1400
Connection ~ 850  -1400
$Comp
L nixieclock-rescue:CP-nixieclock-rescue C2
U 1 1 5C6C4419
P 1200 -1400
F 0 "C2" H 1225 -1300 50  0000 L CNN
F 1 "CP" H 1225 -1500 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 1238 -1550 50  0001 C CNN
F 3 "" H 1200 -1400 50  0001 C CNN
	1    1200 -1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1350 -1400 1400 -1400
Wire Wire Line
	1400 -1400 1400 -1750
Connection ~ 1400 -1750
Wire Wire Line
	8050 5600 10150 5600
Wire Wire Line
	7950 6500 5900 6500
Wire Wire Line
	7850 6400 9950 6400
Wire Wire Line
	7750 6300 9850 6300
Wire Wire Line
	7650 6200 5600 6200
Wire Wire Line
	7550 6100 9650 6100
Wire Wire Line
	7450 6000 5400 6000
Wire Wire Line
	7350 5900 9450 5900
Wire Wire Line
	7150 5700 9250 5700
Wire Wire Line
	7250 5800 9350 5800
Wire Wire Line
	6000 5600 8050 5600
Wire Wire Line
	5900 6500 3800 6500
Wire Wire Line
	5800 6400 7850 6400
Wire Wire Line
	5700 6300 7750 6300
Wire Wire Line
	5600 6200 3500 6200
Wire Wire Line
	5500 6100 7550 6100
Wire Wire Line
	5400 6000 3300 6000
Wire Wire Line
	5300 5900 7350 5900
Wire Wire Line
	5200 5800 7250 5800
Wire Wire Line
	5100 5700 7150 5700
Wire Wire Line
	3950 5600 6000 5600
Wire Wire Line
	3800 6500 2400 6500
Wire Wire Line
	3700 6400 5800 6400
Wire Wire Line
	3600 6300 5700 6300
Wire Wire Line
	3500 6200 2400 6200
Wire Wire Line
	3400 6100 5500 6100
Wire Wire Line
	3300 6000 2400 6000
Wire Wire Line
	3200 5900 5300 5900
Wire Wire Line
	3100 5800 5200 5800
Wire Wire Line
	3000 5700 5100 5700
Wire Wire Line
	550  2500 550  2800
Wire Wire Line
	800  4100 800  4200
Wire Wire Line
	3950 1450 3950 1500
Wire Wire Line
	4350 1050 4350 1250
Wire Wire Line
	6100 1450 6100 1500
Wire Wire Line
	6500 1050 6500 1250
Wire Wire Line
	8200 1450 8200 1500
Wire Wire Line
	8600 1050 8600 1250
Wire Wire Line
	10250 1450 10250 1500
Wire Wire Line
	10650 1050 10650 1250
Wire Wire Line
	2350 -1300 2350 -1100
Wire Wire Line
	2350 -1100 2350 -900
Wire Wire Line
	2350 -900 2350 -800
Wire Wire Line
	1500 -1750 1500 -1500
Wire Wire Line
	1500 -1500 1500 -1300
Wire Wire Line
	1500 -1300 1500 -1100
Wire Wire Line
	1500 -1100 1500 -900
Wire Wire Line
	800  4000 800  4100
Wire Wire Line
	550  2800 550  3300
Wire Wire Line
	300  -1750 300  -1400
Wire Wire Line
	850  -1400 850  -1450
Wire Wire Line
	850  -1400 1050 -1400
Wire Wire Line
	1400 -1750 1500 -1750
Wire Wire Line
	1100 1450 1600 1450
Wire Wire Line
	1600 1650 1600 1450
Connection ~ 1600 1450
Wire Wire Line
	2000 1650 2050 1650
Wire Wire Line
	2000 1450 2050 1450
Connection ~ 2050 1450
Wire Wire Line
	2050 1450 2050 1650
Wire Wire Line
	2050 1100 2050 1450
Wire Wire Line
	2050 1800 2050 1650
Connection ~ 2050 1650
$Comp
L nixieclock-rescue:GND-nixieclock-rescue #PWR07
U 1 1 60896CDF
P 1800 6750
F 0 "#PWR07" H 1800 6500 50  0001 C CNN
F 1 "GND" H 1800 6600 50  0000 C CNN
F 2 "" H 1800 6750 50  0001 C CNN
F 3 "" H 1800 6750 50  0001 C CNN
	1    1800 6750
	1    0    0    -1  
$EndComp
$Comp
L nixieclock-rescue:+5V-nixieclock-rescue #PWR06
U 1 1 608979E3
P 1800 5350
F 0 "#PWR06" H 1800 5200 50  0001 C CNN
F 1 "+5V" H 1800 5490 50  0000 C CNN
F 2 "" H 1800 5350 50  0001 C CNN
F 3 "" H 1800 5350 50  0001 C CNN
	1    1800 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5350 1800 5500
Wire Wire Line
	1800 6600 1800 6750
Connection ~ 1600 900 
Wire Wire Line
	11150 1650 11150 4550
Wire Wire Line
	11050 1650 11150 1650
Wire Wire Line
	9100 4550 9100 1650
Wire Wire Line
	9000 1650 9100 1650
Wire Wire Line
	7000 4550 7000 1650
Wire Wire Line
	6900 1650 7000 1650
Wire Wire Line
	4800 4550 4900 4550
Wire Wire Line
	4900 4550 4900 1650
Wire Wire Line
	4750 1650 4900 1650
Wire Wire Line
	2900 2800 9900 2800
Wire Wire Line
	2900 2700 7800 2700
Wire Wire Line
	2900 2600 5700 2600
Wire Wire Line
	3550 2050 3550 2500
Wire Wire Line
	2900 2500 3550 2500
Wire Wire Line
	2500 4100 2850 4100
Wire Wire Line
	2500 4200 2850 4200
Text Label 2500 4200 0    50   ~ 0
SET_MIN
Text Label 2500 4100 0    50   ~ 0
SET_HOUR
Text Label 1100 900  0    50   ~ 0
SET_HOUR
Text Label 1100 1450 0    50   ~ 0
SET_MIN
Wire Wire Line
	4350 1050 6100 1050
Connection ~ 4350 1050
Connection ~ 6100 1050
Wire Wire Line
	6500 1050 8200 1050
Connection ~ 6500 1050
Connection ~ 8200 1050
Wire Wire Line
	8600 1050 10250 1050
Connection ~ 8600 1050
Connection ~ 10250 1050
$Comp
L power:+VDC #PWR?
U 1 1 608B06FB
P 3950 900
F 0 "#PWR?" H 3950 800 50  0001 C CNN
F 1 "+VDC" H 3950 1175 50  0000 C CNN
F 2 "" H 3950 900 50  0001 C CNN
F 3 "" H 3950 900 50  0001 C CNN
	1    3950 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1050 3950 900 
Connection ~ 3950 1050
$EndSCHEMATC
