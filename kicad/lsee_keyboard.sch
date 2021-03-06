EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:lsee
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:lsee_keyboard-cache
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
L C C2
U 1 1 54A5BA6A
P 3850 3200
F 0 "C2" H 3850 3300 40  0000 R CNN
F 1 "22p" H 3856 3115 40  0000 R CNN
F 2 "" H 3888 3050 30  0000 C CNN
F 3 "" H 3850 3200 60  0000 C CNN
	1    3850 3200
	0    1    1    0   
$EndComp
$Comp
L CRYSTAL Y1
U 1 1 54A5BAE9
P 4300 3500
F 0 "Y1" H 4300 3650 39  0000 C CNN
F 1 "12MHz" H 4300 3350 39  0000 C CNN
F 2 "" H 4300 3500 60  0000 C CNN
F 3 "" H 4300 3500 60  0000 C CNN
	1    4300 3500
	0    1    1    0   
$EndComp
$Comp
L ATMEGA328-P IC1
U 1 1 54A8221A
P 5500 3300
F 0 "IC1" H 4750 4550 40  0001 L BNN
F 1 "ATMEGA328" H 6000 4550 40  0000 L BNN
F 2 "" H 5500 3300 30  0000 C CIN
F 3 "" H 5500 3300 60  0000 C CNN
	1    5500 3300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54A829C4
P 3750 4250
F 0 "R2" V 3830 4250 40  0000 C CNN
F 1 "68" V 3757 4251 40  0000 C CNN
F 2 "" V 3680 4250 30  0000 C CNN
F 3 "" H 3750 4250 30  0000 C CNN
	1    3750 4250
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 54A82A64
P 3750 4500
F 0 "R1" V 3830 4500 40  0000 C CNN
F 1 "68" V 3757 4501 40  0000 C CNN
F 2 "" V 3680 4500 30  0000 C CNN
F 3 "" H 3750 4500 30  0000 C CNN
	1    3750 4500
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 54A831D2
P 3750 4850
F 0 "R3" V 3830 4850 40  0000 C CNN
F 1 "1.5k" V 3757 4851 40  0000 C CNN
F 2 "" V 3680 4850 30  0000 C CNN
F 3 "" H 3750 4850 30  0000 C CNN
	1    3750 4850
	0    1    1    0   
$EndComp
Text Label 2400 1650 1    39   ~ 0
DATA-
Text Label 2600 1650 1    39   ~ 0
DATA+
Text Label 3200 1650 1    39   ~ 0
GND
Text Label 3400 1650 1    39   ~ 0
VCC
$Comp
L C C1
U 1 1 54A8472E
P 4050 2450
F 0 "C1" H 4050 2550 40  0000 R CNN
F 1 "47n" H 4056 2365 40  0000 R CNN
F 2 "" H 4088 2300 30  0000 C CNN
F 3 "" H 4050 2450 60  0000 C CNN
	1    4050 2450
	-1   0    0    1   
$EndComp
Text Label 7650 2100 3    60   ~ 0
COLUMNS_RIGHT
Text Label 7650 3000 3    60   ~ 0
COLUMNS_LEFT
Text Label 7650 4050 3    60   ~ 0
ROWS
$Comp
L ZENER Z1
U 1 1 54A83452
P 2900 2550
F 0 "Z1" H 2900 2650 39  0000 C CNN
F 1 "3.6V" H 2900 2450 40  0000 C CNN
F 2 "" H 2900 2550 60  0000 C CNN
F 3 "" H 2900 2550 60  0000 C CNN
	1    2900 2550
	-1   0    0    1   
$EndComp
$Comp
L ZENER Z2
U 1 1 54A83711
P 2900 2200
F 0 "Z2" H 2900 2300 39  0000 C CNN
F 1 "3.6V" H 2900 2100 40  0000 C CNN
F 2 "" H 2900 2200 60  0000 C CNN
F 3 "" H 2900 2200 60  0000 C CNN
	1    2900 2200
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 54A83550
P 3850 3800
F 0 "C3" H 3850 3900 40  0000 R CNN
F 1 "22p" H 3856 3715 40  0000 R CNN
F 2 "" H 3888 3650 30  0000 C CNN
F 3 "" H 3850 3800 60  0000 C CNN
	1    3850 3800
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH S1
U 1 1 54A843A4
P 9250 3950
F 0 "S1" H 9400 4060 50  0000 C CNN
F 1 "SW_PUSH" H 9250 3870 50  0001 C CNN
F 2 "" H 9250 3950 60  0000 C CNN
F 3 "" H 9250 3950 60  0000 C CNN
	1    9250 3950
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH S3
U 1 1 54A84563
P 10450 3950
F 0 "S3" H 10600 4060 50  0000 C CNN
F 1 "SW_PUSH" H 10450 3870 50  0001 C CNN
F 2 "" H 10450 3950 60  0000 C CNN
F 3 "" H 10450 3950 60  0000 C CNN
	1    10450 3950
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH S4
U 1 1 54A84577
P 10450 4400
F 0 "S4" H 10600 4510 50  0000 C CNN
F 1 "SW_PUSH" H 10450 4320 50  0001 C CNN
F 2 "" H 10450 4400 60  0000 C CNN
F 3 "" H 10450 4400 60  0000 C CNN
	1    10450 4400
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH S2
U 1 1 54A8458B
P 9250 4400
F 0 "S2" H 9400 4510 50  0000 C CNN
F 1 "SW_PUSH" H 9250 4320 50  0001 C CNN
F 2 "" H 9250 4400 60  0000 C CNN
F 3 "" H 9250 4400 60  0000 C CNN
	1    9250 4400
	1    0    0    -1  
$EndComp
$Comp
L DIODE D3
U 1 1 54A84598
P 9950 3950
F 0 "D3" H 9950 4050 40  0000 C CNN
F 1 "DIODE" H 9950 3850 40  0001 C CNN
F 2 "" H 9950 3950 60  0000 C CNN
F 3 "" H 9950 3950 60  0000 C CNN
	1    9950 3950
	1    0    0    -1  
$EndComp
$Comp
L DIODE D4
U 1 1 54A84655
P 9950 4400
F 0 "D4" H 9950 4500 40  0000 C CNN
F 1 "DIODE" H 9950 4300 40  0001 C CNN
F 2 "" H 9950 4400 60  0000 C CNN
F 3 "" H 9950 4400 60  0000 C CNN
	1    9950 4400
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 54A84950
P 8750 3950
F 0 "D1" H 8750 4050 40  0000 C CNN
F 1 "DIODE" H 8750 3850 40  0001 C CNN
F 2 "" H 8750 3950 60  0000 C CNN
F 3 "" H 8750 3950 60  0000 C CNN
	1    8750 3950
	1    0    0    -1  
$EndComp
$Comp
L DIODE D2
U 1 1 54A84964
P 8750 4400
F 0 "D2" H 8750 4500 40  0000 C CNN
F 1 "DIODE" H 8750 4300 40  0001 C CNN
F 2 "" H 8750 4400 60  0000 C CNN
F 3 "" H 8750 4400 60  0000 C CNN
	1    8750 4400
	1    0    0    -1  
$EndComp
Text Label 2650 1200 0    157  ~ 31
USB
Wire Wire Line
	3200 3200 3650 3200
Connection ~ 3200 3200
Wire Wire Line
	3200 3800 3650 3800
Connection ~ 3200 3800
Wire Wire Line
	4050 3200 4600 3200
Connection ~ 4300 3200
Wire Wire Line
	4050 3800 4600 3800
Connection ~ 4300 3800
Wire Wire Line
	3400 2200 4600 2200
Wire Wire Line
	3400 1700 3400 2200
Wire Wire Line
	2600 4250 3500 4250
Wire Wire Line
	2600 1700 2600 4250
Wire Wire Line
	2400 4500 3500 4500
Wire Wire Line
	2400 1700 2400 4500
Wire Wire Line
	4000 4250 4600 4250
Wire Wire Line
	4000 4500 4600 4500
Wire Wire Line
	4600 2300 4450 2300
Wire Wire Line
	4450 2300 4450 2200
Connection ~ 4450 2200
Wire Wire Line
	6750 4850 6750 4050
Connection ~ 6750 4050
Wire Wire Line
	4000 4850 6750 4850
Wire Wire Line
	6500 4150 7450 4150
Wire Wire Line
	6500 4250 7450 4250
Wire Wire Line
	6500 4350 7450 4350
Wire Wire Line
	6500 2200 7450 2200
Wire Wire Line
	7450 2300 6500 2300
Wire Wire Line
	7450 2400 6500 2400
Wire Wire Line
	7450 2500 6500 2500
Wire Wire Line
	6500 3050 7450 3050
Wire Wire Line
	7450 3150 6500 3150
Wire Wire Line
	7450 3250 6500 3250
Wire Wire Line
	7450 3350 6500 3350
Wire Wire Line
	7450 3450 6500 3450
Wire Wire Line
	7450 3550 6500 3550
Wire Wire Line
	3200 2700 4600 2700
Connection ~ 3200 2700
Wire Wire Line
	4050 2250 4050 2200
Connection ~ 4050 2200
Wire Wire Line
	3200 2550 3100 2550
Connection ~ 3200 2550
Wire Wire Line
	2400 2550 2700 2550
Connection ~ 2400 2550
Wire Wire Line
	3100 2200 3200 2200
Connection ~ 3200 2200
Wire Wire Line
	2700 2200 2600 2200
Connection ~ 2600 2200
Wire Wire Line
	4050 2700 4050 2650
Connection ~ 4050 2700
Wire Wire Line
	8250 3950 8250 4200
Wire Wire Line
	8250 4200 11150 4200
Wire Wire Line
	9550 4200 9550 3950
Wire Wire Line
	10750 4200 10750 3950
Connection ~ 9550 4200
Connection ~ 10750 4200
Wire Wire Line
	8150 4050 8150 4650
Wire Wire Line
	8150 4650 11150 4650
Wire Wire Line
	10750 4400 10750 4650
Connection ~ 10750 4650
Wire Wire Line
	9550 4650 9550 4400
Connection ~ 9550 4650
Wire Wire Line
	9750 3950 9700 3950
Wire Wire Line
	9700 2600 9700 4900
Connection ~ 9700 3950
Wire Wire Line
	9750 4400 9700 4400
Connection ~ 9700 4400
Wire Wire Line
	8500 2700 8500 4900
Wire Wire Line
	8550 4400 8500 4400
Connection ~ 8500 4400
Wire Wire Line
	8550 3950 8500 3950
Connection ~ 8500 3950
Wire Notes Line
	2200 800  2200 1900
Wire Notes Line
	2200 1900 3600 1900
Wire Notes Line
	3600 1900 3600 800 
Wire Wire Line
	6500 3950 7450 3950
Wire Wire Line
	6500 4050 7450 4050
Wire Wire Line
	6500 2600 7450 2600
Wire Wire Line
	7450 2700 6500 2700
Wire Wire Line
	7750 2700 8500 2700
Wire Wire Line
	7750 2600 9700 2600
Wire Wire Line
	7750 4050 8150 4050
Wire Wire Line
	7750 3950 8250 3950
Wire Wire Line
	7750 2500 8000 2500
Wire Wire Line
	7750 2400 8000 2400
Wire Wire Line
	7750 2300 8000 2300
Wire Wire Line
	7750 2200 8000 2200
Wire Wire Line
	7750 4150 8000 4150
Wire Wire Line
	7750 4250 8000 4250
Wire Wire Line
	7750 4350 8000 4350
Wire Wire Line
	7750 3050 8000 3050
Wire Wire Line
	8000 3150 7750 3150
Wire Wire Line
	7750 3250 8000 3250
Wire Wire Line
	7750 3350 8000 3350
Wire Wire Line
	7750 3450 8000 3450
Wire Wire Line
	7750 3550 8000 3550
Connection ~ 8000 2200
Connection ~ 8000 2300
Connection ~ 8000 2400
Connection ~ 8000 2500
Connection ~ 8000 3050
Connection ~ 8000 3150
Connection ~ 8000 3250
Connection ~ 8000 3350
Connection ~ 8000 3450
Connection ~ 8000 3550
Connection ~ 8000 4150
Connection ~ 8000 4250
Connection ~ 8000 4350
Connection ~ 8000 2600
Connection ~ 8000 2700
Connection ~ 8000 3950
Connection ~ 8000 4050
Wire Wire Line
	3500 4850 2950 4850
Wire Wire Line
	2950 4850 2950 4500
Connection ~ 2950 4500
Wire Wire Line
	3200 1700 3200 3800
$Comp
L LED D5
U 1 1 54A9362C
P 2900 3900
F 0 "D5" H 2900 4000 50  0000 C CNN
F 1 "LED" H 2900 3800 50  0001 C CNN
F 2 "" H 2900 3900 60  0000 C CNN
F 3 "" H 2900 3900 60  0000 C CNN
	1    2900 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 3700 2900 3550
Wire Wire Line
	2900 3550 3200 3550
Connection ~ 3200 3550
Wire Wire Line
	2900 4100 2900 4250
Connection ~ 2900 4250
$EndSCHEMATC
