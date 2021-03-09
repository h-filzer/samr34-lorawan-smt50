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
L Connector_Generic:Conn_01x12 J?
U 1 1 6047C175
P 2600 2100
F 0 "J?" H 2600 2750 50  0000 C CNN
F 1 "Feather_Right" V 2700 2100 50  0000 C CNN
F 2 "" H 2600 2100 50  0001 C CNN
F 3 "~" H 2600 2100 50  0001 C CNN
	1    2600 2100
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J?
U 1 1 6047D033
P 1850 2300
F 0 "J?" H 1800 3150 50  0000 L CNN
F 1 "Feather_Left" V 1950 2250 50  0000 L CNN
F 2 "" H 1850 2300 50  0001 C CNN
F 3 "~" H 1850 2300 50  0001 C CNN
	1    1850 2300
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC546 Q?
U 1 1 6047E975
P 4750 2350
F 0 "Q?" H 4941 2396 50  0000 L CNN
F 1 "BC546" H 4941 2305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4950 2275 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC550-D.pdf" H 4750 2350 50  0001 L CNN
	1    4750 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6047F8FE
P 4250 2350
F 0 "R?" V 4043 2350 50  0000 C CNN
F 1 "4k7" V 4134 2350 50  0000 C CNN
F 2 "" V 4180 2350 50  0001 C CNN
F 3 "~" H 4250 2350 50  0001 C CNN
	1    4250 2350
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 60481815
P 4700 1600
F 0 "J?" H 4618 1917 50  0000 C CNN
F 1 "SMT50" H 4618 1826 50  0000 C CNN
F 2 "" H 4700 1600 50  0001 C CNN
F 3 "~" H 4700 1600 50  0001 C CNN
	1    4700 1600
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 60482C27
P 7200 1850
F 0 "J?" H 7280 1892 50  0000 L CNN
F 1 "Serial" H 7280 1801 50  0000 L CNN
F 2 "" H 7200 1850 50  0001 C CNN
F 3 "~" H 7200 1850 50  0001 C CNN
	1    7200 1850
	1    0    0    -1  
$EndComp
Text Label 2850 1700 0    50   ~ 0
EN
Text Label 2850 1900 0    50   ~ 0
D13
Text Label 2850 2000 0    50   ~ 0
D12
Text Label 2850 2100 0    50   ~ 0
D11
Text Label 2850 2200 0    50   ~ 0
D10
Text Label 2850 2300 0    50   ~ 0
D9
Text Label 2850 2400 0    50   ~ 0
D6
Text Label 2850 2500 0    50   ~ 0
D5
Text Label 2850 2600 0    50   ~ 0
SCL
Text Label 2850 2700 0    50   ~ 0
SDA
Wire Wire Line
	2850 2700 2800 2700
Wire Wire Line
	2800 2600 2850 2600
Wire Wire Line
	2800 2500 2850 2500
Wire Wire Line
	2800 2400 2850 2400
Wire Wire Line
	2800 2300 2850 2300
Wire Wire Line
	2800 2200 2850 2200
Wire Wire Line
	2800 2100 2850 2100
Wire Wire Line
	2800 2000 2850 2000
Wire Wire Line
	2800 1900 2850 1900
Wire Wire Line
	2850 1700 2800 1700
Wire Wire Line
	4850 2150 4900 2150
Text Label 3950 2350 0    50   ~ 0
D6
Wire Wire Line
	3950 2350 4100 2350
Wire Wire Line
	4400 2350 4550 2350
$Comp
L power:GND #PWR?
U 1 1 60496C0C
P 4850 2600
F 0 "#PWR?" H 4850 2350 50  0001 C CNN
F 1 "GND" H 4855 2427 50  0000 C CNN
F 2 "" H 4850 2600 50  0001 C CNN
F 3 "" H 4850 2600 50  0001 C CNN
	1    4850 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2550 4850 2600
$Comp
L bastwan:+3.3V #PWR?
U 1 1 6049859C
P 1300 1450
F 0 "#PWR?" H 1300 1300 50  0001 C CNN
F 1 "+3.3V" H 1315 1623 50  0000 C CNN
F 2 "" H 1300 1450 50  0001 C CNN
F 3 "" H 1300 1450 50  0001 C CNN
	1    1300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1700 1300 1700
Wire Wire Line
	1300 1700 1300 1450
Text Label 1550 2000 2    50   ~ 0
A0
Text Label 1550 2100 2    50   ~ 0
A1
Text Label 1550 2200 2    50   ~ 0
A2
Text Label 1550 2300 2    50   ~ 0
A3
Text Label 1550 2400 2    50   ~ 0
A4
Text Label 1550 2500 2    50   ~ 0
D3
Text Label 1550 2600 2    50   ~ 0
SCK
Text Label 1550 2700 2    50   ~ 0
MOSI
Text Label 1550 2800 2    50   ~ 0
MISO
Text Label 1550 2900 2    50   ~ 0
UART_RX
Text Label 1550 3000 2    50   ~ 0
UART_TX
$Comp
L power:GND #PWR?
U 1 1 6049AB3B
P 1650 3250
F 0 "#PWR?" H 1650 3000 50  0001 C CNN
F 1 "GND" H 1655 3077 50  0000 C CNN
F 2 "" H 1650 3250 50  0001 C CNN
F 3 "" H 1650 3250 50  0001 C CNN
	1    1650 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2000 1650 2000
Wire Wire Line
	1550 2100 1650 2100
Wire Wire Line
	1550 2200 1650 2200
Wire Wire Line
	1550 2300 1650 2300
Wire Wire Line
	1550 2400 1650 2400
Wire Wire Line
	1550 2500 1650 2500
Wire Wire Line
	1550 2600 1650 2600
Wire Wire Line
	1550 2700 1650 2700
Wire Wire Line
	1550 2800 1650 2800
Wire Wire Line
	1550 2900 1650 2900
Wire Wire Line
	1550 3000 1650 3000
Wire Wire Line
	1650 3100 1650 3250
$Comp
L power:GND #PWR?
U 1 1 604ABB6B
P 1300 1800
F 0 "#PWR?" H 1300 1550 50  0001 C CNN
F 1 "GND" H 1305 1627 50  0000 C CNN
F 2 "" H 1300 1800 50  0001 C CNN
F 3 "" H 1300 1800 50  0001 C CNN
	1    1300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1800 1550 1800
Wire Wire Line
	1650 1900 1550 1900
Wire Wire Line
	1550 1900 1550 1800
Connection ~ 1550 1800
Wire Wire Line
	1550 1800 1300 1800
Text Label 1550 1600 2    50   ~ 0
RST
Wire Wire Line
	1550 1600 1650 1600
$Comp
L power:+BATT #PWR?
U 1 1 604B10EE
P 2900 1500
F 0 "#PWR?" H 2900 1350 50  0001 C CNN
F 1 "+BATT" H 2915 1673 50  0000 C CNN
F 2 "" H 2900 1500 50  0001 C CNN
F 3 "" H 2900 1500 50  0001 C CNN
	1    2900 1500
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR?
U 1 1 604B1B56
P 3200 1500
F 0 "#PWR?" H 3200 1350 50  0001 C CNN
F 1 "VBUS" H 3215 1673 50  0000 C CNN
F 2 "" H 3200 1500 50  0001 C CNN
F 3 "" H 3200 1500 50  0001 C CNN
	1    3200 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1500 3200 1800
Wire Wire Line
	3200 1800 2800 1800
Wire Wire Line
	2900 1500 2900 1600
Wire Wire Line
	2900 1600 2800 1600
Wire Wire Line
	4900 1800 4900 2150
$Comp
L power:+3.3V #PWR?
U 1 1 604BE780
P 5100 1350
F 0 "#PWR?" H 5100 1200 50  0001 C CNN
F 1 "+3.3V" H 5115 1523 50  0000 C CNN
F 2 "" H 5100 1350 50  0001 C CNN
F 3 "" H 5100 1350 50  0001 C CNN
	1    5100 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1350 5100 1500
Wire Wire Line
	5100 1500 4900 1500
Text Label 5150 1600 0    50   ~ 0
A1
Text Label 5150 1700 0    50   ~ 0
A2
Wire Wire Line
	5150 1600 4900 1600
Wire Wire Line
	5150 1700 4900 1700
Text Notes 4600 1500 2    50   ~ 0
brown
Text Notes 4600 1600 2    50   ~ 0
green - temp
Text Notes 4600 1700 2    50   ~ 0
yellow - moisture
Text Notes 4550 1800 2    50   ~ 0
white
Text Label 6900 1750 2    50   ~ 0
UART_RX
Text Label 6900 1850 2    50   ~ 0
UART_TX
$Comp
L power:GND #PWR?
U 1 1 604C6BCF
P 7000 2100
F 0 "#PWR?" H 7000 1850 50  0001 C CNN
F 1 "GND" H 7005 1927 50  0000 C CNN
F 2 "" H 7000 2100 50  0001 C CNN
F 3 "" H 7000 2100 50  0001 C CNN
	1    7000 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2100 7000 1950
Wire Wire Line
	7000 1850 6900 1850
Wire Wire Line
	6900 1750 7000 1750
Wire Notes Line
	3600 500  3600 4150
Text Notes 2900 850  2    118  ~ 0
Bastwan Module
Wire Notes Line
	6100 4150 6100 500 
Text Notes 5350 900  2    118  ~ 0
STM50 Sensor
Wire Notes Line
	8150 4150 8150 500 
Wire Notes Line
	500  4150 8150 4150
Text Notes 7200 900  2    118  ~ 0
Serial
$EndSCHEMATC
