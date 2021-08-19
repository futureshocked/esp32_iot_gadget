EESchema Schematic File Version 4
LIBS:ESP32 Project Make an IoT Gadget-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ESP32 Dev Kit with 2.8\" touch display and BME280 sensor"
Date "2019-02-18"
Rev "1.3"
Comp "Tech Explorations"
Comment1 "Includes SD Card module"
Comment2 "Incldes TFT display with the ILI9341 controller"
Comment3 "Includes Touch"
Comment4 "Includes BME280 sensor"
$EndDescr
$Comp
L Connector:Conn_01x14_Male J1
U 1 1 5C6A44CD
P 3800 3500
F 0 "J1" H 3906 4278 50  0000 C CNN
F 1 "2.8\" TFT SPI with touch 240x320" H 3930 4530 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x14_P2.54mm_Vertical" H 3800 3500 50  0001 C CNN
F 3 "~" H 3800 3500 50  0001 C CNN
	1    3800 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5C6A45C6
P 1970 4170
F 0 "J2" H 1942 4050 50  0000 R CNN
F 1 "SD Card" H 1942 4141 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1970 4170 50  0001 C CNN
F 3 "~" H 1970 4170 50  0001 C CNN
	1    1970 4170
	-1   0    0    1   
$EndComp
Text Label 1770 4270 2    50   ~ 0
SD_CS
Text Label 1770 4170 2    50   ~ 0
MOSI
Text Label 1770 4070 2    50   ~ 0
MISO
Text Label 1770 3970 2    50   ~ 0
SCK
Text Label 4000 4200 0    50   ~ 0
VCC
Text Label 4000 4100 0    50   ~ 0
GND
Text Label 4000 4000 0    50   ~ 0
TFT_CS
Text Label 4000 3900 0    50   ~ 0
TFT_RESET
Text Label 4000 3800 0    50   ~ 0
TFT_DC
Text Label 4000 3700 0    50   ~ 0
MOSI
Text Label 4000 3600 0    50   ~ 0
SCK
Text Label 4000 3400 0    50   ~ 0
MISO
Text Label 4000 3300 0    50   ~ 0
SCK
Text Label 4000 3200 0    50   ~ 0
TOUCH_CS
Text Label 4000 3100 0    50   ~ 0
MOSI
Text Label 4000 3000 0    50   ~ 0
MISO
Text Label 4000 2900 0    50   ~ 0
TOUCH_IRQ
NoConn ~ 4000 2900
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5C6ABDC9
P 1970 3620
F 0 "J3" H 1942 3500 50  0000 R CNN
F 1 "BME280" H 1942 3591 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1970 3620 50  0001 C CNN
F 3 "~" H 1970 3620 50  0001 C CNN
	1    1970 3620
	-1   0    0    1   
$EndComp
Text Label 1770 3720 2    50   ~ 0
VIN
Text Label 1770 3620 2    50   ~ 0
GND
Text Label 1770 3520 2    50   ~ 0
SCL
Text Label 1770 3420 2    50   ~ 0
SDA
Text Label 6850 3250 0    50   ~ 0
SDA
Text Label 6850 2950 0    50   ~ 0
SCL
Text Label 6850 2750 0    50   ~ 0
GND
Text Label 5250 2750 2    50   ~ 0
VIN
Text Label 6850 3550 0    50   ~ 0
SCK
Text Label 6850 3450 0    50   ~ 0
MISO
Text Label 6850 2850 0    50   ~ 0
MOSI
Text Label 6850 3950 0    50   ~ 0
SD_CS
Text Label 5250 4550 2    50   ~ 0
VCC
Text Label 4000 3500 0    50   ~ 0
VCC
Text Label 5250 4050 2    50   ~ 0
GND
Text Label 6850 4250 0    50   ~ 0
TFT_CS
Text Label 6850 4150 0    50   ~ 0
TFT_RESET
Text Label 6850 4050 0    50   ~ 0
TFT_DC
Text Label 6850 3650 0    50   ~ 0
TOUCH_CS
Wire Wire Line
	5010 4550 5250 4550
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5C6BBE6E
P 4800 4050
F 0 "#FLG0101" H 4800 4125 50  0001 C CNN
F 1 "PWR_FLAG" V 4800 4178 50  0000 L CNN
F 2 "" H 4800 4050 50  0001 C CNN
F 3 "~" H 4800 4050 50  0001 C CNN
	1    4800 4050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5C6BBE94
P 5010 4550
F 0 "#FLG0102" H 5010 4625 50  0001 C CNN
F 1 "PWR_FLAG" V 5010 4678 50  0000 L CNN
F 2 "" H 5010 4550 50  0001 C CNN
F 3 "~" H 5010 4550 50  0001 C CNN
	1    5010 4550
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5C6BBF6C
P 5050 2750
F 0 "#FLG0103" H 5050 2825 50  0001 C CNN
F 1 "PWR_FLAG" V 5050 2878 50  0000 L CNN
F 2 "" H 5050 2750 50  0001 C CNN
F 3 "~" H 5050 2750 50  0001 C CNN
	1    5050 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 2750 5250 2750
$Comp
L Device:LED D1
U 1 1 5C6CAD32
P 9600 2510
F 0 "D1" H 9592 2255 50  0000 C CNN
F 1 "IO16" H 9592 2346 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9600 2510 50  0001 C CNN
F 3 "~" H 9600 2510 50  0001 C CNN
	1    9600 2510
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5C6CADBA
P 10560 2720
F 0 "R1" H 10630 2766 50  0000 L CNN
F 1 "330" H 10630 2675 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10490 2720 50  0001 C CNN
F 3 "~" H 10560 2720 50  0001 C CNN
	1    10560 2720
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0101
U 1 1 5C6CB2AE
P 10560 3060
F 0 "#PWR0101" H 10560 2860 50  0001 C CNN
F 1 "GNDPWR" H 10564 2906 50  0000 C CNN
F 2 "" H 10560 3010 50  0001 C CNN
F 3 "" H 10560 3010 50  0001 C CNN
	1    10560 3060
	1    0    0    -1  
$EndComp
Wire Wire Line
	10560 2870 10560 3060
$Comp
L Device:Jumper JP1
U 1 1 5C6CB7C4
P 10160 2510
F 0 "JP1" H 10160 2774 50  0000 C CNN
F 1 "IO16" H 10160 2683 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10160 2510 50  0001 C CNN
F 3 "~" H 10160 2510 50  0001 C CNN
	1    10160 2510
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 2510 9860 2510
Wire Wire Line
	10460 2510 10560 2510
Wire Wire Line
	10560 2510 10560 2570
Text Label 3120 4250 0    50   ~ 0
IO12
Text Label 5250 3950 2    50   ~ 0
IO12
Text Label 5250 3850 2    50   ~ 0
IO14
Text Label 5250 3750 2    50   ~ 0
IO27
Text Label 5250 3650 2    50   ~ 0
IO26
Text Label 5250 3550 2    50   ~ 0
IO25
Text Label 5250 3450 2    50   ~ 0
IO33
Text Label 5250 3350 2    50   ~ 0
IO32
Text Label 5250 3250 2    50   ~ 0
IO35
Text Label 5250 3150 2    50   ~ 0
IO34
Text Label 6850 3850 0    50   ~ 0
IO16
Text Label 6850 3750 0    50   ~ 0
IO17
Text Label 9450 2510 2    50   ~ 0
IO16
Text Label 3120 4150 0    50   ~ 0
IO14
Text Label 3120 4050 0    50   ~ 0
IO16
Text Label 3120 3950 0    50   ~ 0
IO17
Text Label 3120 3650 0    50   ~ 0
IO27
Text Label 3120 3750 0    50   ~ 0
IO26
Text Label 3120 3850 0    50   ~ 0
IO25
Text Label 3120 3450 0    50   ~ 0
IO33
Text Label 3120 3550 0    50   ~ 0
IO32
Text Label 3120 3250 0    50   ~ 0
IO35
Text Label 3120 3350 0    50   ~ 0
IO34
Text Label 3120 3150 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x14_Male J4
U 1 1 5C6CE104
P 2920 3550
F 0 "J4" H 3040 4380 50  0000 C CNN
F 1 "GPIO" H 3040 4290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x14_P2.54mm_Vertical" H 2920 3550 50  0001 C CNN
F 3 "~" H 2920 3550 50  0001 C CNN
	1    2920 3550
	1    0    0    -1  
$EndComp
Text Label 3120 2950 0    50   ~ 0
VIN
Text Label 3120 3050 0    50   ~ 0
VCC
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 5C6CE65F
P 1980 3060
F 0 "J5" H 1952 2940 50  0000 R CNN
F 1 "I2C spare" H 1952 3031 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1980 3060 50  0001 C CNN
F 3 "~" H 1980 3060 50  0001 C CNN
	1    1980 3060
	-1   0    0    1   
$EndComp
Text Label 1780 3160 2    50   ~ 0
VIN
Text Label 1780 3060 2    50   ~ 0
GND
Text Label 1780 2960 2    50   ~ 0
SCL
Text Label 1780 2860 2    50   ~ 0
SDA
$Comp
L Device:LED D3
U 1 1 5C88663B
P 7950 3720
F 0 "D3" H 7942 3465 50  0000 C CNN
F 1 "PWR" H 7942 3556 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7950 3720 50  0001 C CNN
F 3 "~" H 7950 3720 50  0001 C CNN
	1    7950 3720
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5C886797
P 8700 3930
F 0 "R2" H 8770 3976 50  0000 L CNN
F 1 "330" H 8770 3885 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8630 3930 50  0001 C CNN
F 3 "~" H 8700 3930 50  0001 C CNN
	1    8700 3930
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0102
U 1 1 5C88699B
P 8700 4420
F 0 "#PWR0102" H 8700 4220 50  0001 C CNN
F 1 "GNDPWR" H 8704 4266 50  0000 C CNN
F 2 "" H 8700 4370 50  0001 C CNN
F 3 "" H 8700 4370 50  0001 C CNN
	1    8700 4420
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3720 8700 3720
Wire Wire Line
	8700 3720 8700 3780
Wire Wire Line
	8700 4080 8700 4420
Text Label 7800 3720 2    50   ~ 0
VIN
$Comp
L Device:LED D2
U 1 1 5C88780D
P 7940 2520
F 0 "D2" H 7932 2265 50  0000 C CNN
F 1 "IO17" H 7932 2356 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7940 2520 50  0001 C CNN
F 3 "~" H 7940 2520 50  0001 C CNN
	1    7940 2520
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5C887813
P 8900 2730
F 0 "R3" H 8970 2776 50  0000 L CNN
F 1 "330" H 8970 2685 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8830 2730 50  0001 C CNN
F 3 "~" H 8900 2730 50  0001 C CNN
	1    8900 2730
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0103
U 1 1 5C887819
P 8900 3070
F 0 "#PWR0103" H 8900 2870 50  0001 C CNN
F 1 "GNDPWR" H 8904 2916 50  0000 C CNN
F 2 "" H 8900 3020 50  0001 C CNN
F 3 "" H 8900 3020 50  0001 C CNN
	1    8900 3070
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2880 8900 3070
$Comp
L Device:Jumper JP2
U 1 1 5C887820
P 8500 2520
F 0 "JP2" H 8500 2784 50  0000 C CNN
F 1 "IO17" H 8500 2693 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8500 2520 50  0001 C CNN
F 3 "~" H 8500 2520 50  0001 C CNN
	1    8500 2520
	1    0    0    -1  
$EndComp
Wire Wire Line
	8090 2520 8200 2520
Wire Wire Line
	8800 2520 8900 2520
Wire Wire Line
	8900 2520 8900 2580
Text Label 7790 2520 2    50   ~ 0
IO17
$Comp
L Device:LED D4
U 1 1 5C888751
P 9620 3780
F 0 "D4" H 9612 3525 50  0000 C CNN
F 1 "IO12" H 9612 3616 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9620 3780 50  0001 C CNN
F 3 "~" H 9620 3780 50  0001 C CNN
	1    9620 3780
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 5C888757
P 10580 3990
F 0 "R5" H 10650 4036 50  0000 L CNN
F 1 "330" H 10650 3945 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10510 3990 50  0001 C CNN
F 3 "~" H 10580 3990 50  0001 C CNN
	1    10580 3990
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0104
U 1 1 5C88875D
P 10580 4330
F 0 "#PWR0104" H 10580 4130 50  0001 C CNN
F 1 "GNDPWR" H 10584 4176 50  0000 C CNN
F 2 "" H 10580 4280 50  0001 C CNN
F 3 "" H 10580 4280 50  0001 C CNN
	1    10580 4330
	1    0    0    -1  
$EndComp
Wire Wire Line
	10580 4140 10580 4330
$Comp
L Device:Jumper JP3
U 1 1 5C888764
P 10180 3780
F 0 "JP3" H 10180 4044 50  0000 C CNN
F 1 "IO12" H 10180 3953 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10180 3780 50  0001 C CNN
F 3 "~" H 10180 3780 50  0001 C CNN
	1    10180 3780
	1    0    0    -1  
$EndComp
Wire Wire Line
	9770 3780 9880 3780
Wire Wire Line
	10480 3780 10580 3780
Wire Wire Line
	10580 3780 10580 3840
Text Label 9470 3780 2    50   ~ 0
IO12
Text Label 9320 5430 0    50   ~ 0
IO14
$Comp
L Device:R R4
U 1 1 5C88968F
P 9130 5870
F 0 "R4" H 9200 5916 50  0000 L CNN
F 1 "10K" H 9200 5825 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9060 5870 50  0001 C CNN
F 3 "~" H 9130 5870 50  0001 C CNN
	1    9130 5870
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0105
U 1 1 5C88994D
P 9130 6150
F 0 "#PWR0105" H 9130 5950 50  0001 C CNN
F 1 "GNDPWR" H 9134 5996 50  0000 C CNN
F 2 "" H 9130 6100 50  0001 C CNN
F 3 "" H 9130 6100 50  0001 C CNN
	1    9130 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9130 6020 9130 6150
Wire Wire Line
	7880 5220 7600 5220
Wire Wire Line
	7600 5620 7880 5620
Wire Wire Line
	8880 5220 9130 5220
Wire Wire Line
	9130 5220 9130 5430
Wire Wire Line
	9130 5620 8880 5620
Wire Wire Line
	7600 5220 7600 5440
Text Label 7380 5440 2    50   ~ 0
VIN
Wire Wire Line
	7380 5440 7600 5440
Connection ~ 7600 5440
Wire Wire Line
	7600 5440 7600 5620
Wire Wire Line
	9320 5430 9130 5430
Connection ~ 9130 5430
Wire Wire Line
	9130 5430 9130 5620
Wire Wire Line
	9130 5720 9130 5620
Connection ~ 9130 5620
$Comp
L power:GNDPWR #PWR0106
U 1 1 5C88E051
P 4800 4080
F 0 "#PWR0106" H 4800 3880 50  0001 C CNN
F 1 "GNDPWR" H 4804 3926 50  0000 C CNN
F 2 "" H 4800 4030 50  0001 C CNN
F 3 "" H 4800 4030 50  0001 C CNN
	1    4800 4080
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4050 4800 4080
Wire Wire Line
	4800 4050 5250 4050
Connection ~ 4800 4050
$Comp
L freetronics_schematic:SW_DPST SW1
U 1 1 5C89767B
P 8380 5420
F 0 "SW1" H 8380 5930 70  0000 C CNN
F 1 "SW_DPST" H 8380 5809 70  0000 C CNN
F 2 "BC Miniproject SMD v5 (KiCad 5):SW_PUSHBUTTON_PTH_PD" H 8380 5420 60  0001 C CNN
F 3 "" H 8380 5420 60  0000 C CNN
	1    8380 5420
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x19_Female J6
U 1 1 5CEFC242
P 2380 5720
F 0 "J6" H 2272 4595 50  0000 C CNN
F 1 "Left devkit header" H 2272 4686 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 2380 5720 50  0001 C CNN
F 3 "~" H 2380 5720 50  0001 C CNN
	1    2380 5720
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x19_Female J7
U 1 1 5CEFEFFE
P 3840 5700
F 0 "J7" H 3732 4575 50  0000 C CNN
F 1 "Right devkit header" H 3732 4666 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 3840 5700 50  0001 C CNN
F 3 "~" H 3840 5700 50  0001 C CNN
	1    3840 5700
	-1   0    0    1   
$EndComp
Text Notes 5440 4750 0    50   ~ 0
Left
Text Notes 6470 4740 0    50   ~ 0
Right
Text Label 2580 6620 0    50   ~ 0
VCC
Text Label 2580 6120 0    50   ~ 0
GND
Text Label 2580 6020 0    50   ~ 0
IO12
Text Label 2580 5920 0    50   ~ 0
IO14
Text Label 2580 5820 0    50   ~ 0
IO27
Text Label 2580 5720 0    50   ~ 0
IO26
Text Label 2580 5620 0    50   ~ 0
IO25
Text Label 2580 5520 0    50   ~ 0
IO33
Text Label 2580 5420 0    50   ~ 0
IO32
Text Label 2580 5320 0    50   ~ 0
IO35
Text Label 2580 5220 0    50   ~ 0
IO34
Text Label 2580 4820 0    50   ~ 0
VIN
Text Label 5250 2850 2    50   ~ 0
EN
Text Label 5250 2950 2    50   ~ 0
SENSOR_VP
Text Label 5250 3050 2    50   ~ 0
SENSOR_VN
Text Label 2580 4920 0    50   ~ 0
EN
Text Label 2580 5020 0    50   ~ 0
SENSOR_VP
Text Label 2580 5120 0    50   ~ 0
SENSOR_VN
Text Label 5250 4150 2    50   ~ 0
IO13
Text Label 5250 4250 2    50   ~ 0
SD2
Text Label 5250 4350 2    50   ~ 0
SD3
Text Label 5250 4450 2    50   ~ 0
CMD
Text Label 2580 6220 0    50   ~ 0
IO13
Text Label 2580 6320 0    50   ~ 0
SD2
Text Label 2580 6420 0    50   ~ 0
SD3
Text Label 2580 6520 0    50   ~ 0
CMD
$Comp
L ESP32-DEVKITC-32D:ESP32-DEVKITC-32D U1
U 1 1 5C8960F1
P 6050 3650
F 0 "U1" H 6050 4817 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 6050 4726 50  0000 C CNN
F 2 "Custom_project_footprints:MODULE_ESP32-DEVKITC_PD" H 6050 3650 50  0001 L BNN
F 3 "None" H 6050 3650 50  0001 L BNN
F 4 "Espressif Systems" H 6050 3650 50  0001 L BNN "Field4"
F 5 "None" H 6050 3650 50  0001 L BNN "Field5"
F 6 "Eval Board For Esp-Wroom-32" H 6050 3650 50  0001 L BNN "Field6"
F 7 "ESP32-DEVKITC-32D" H 6050 3650 50  0001 L BNN "Field7"
F 8 "Unavailable" H 6050 3650 50  0001 L BNN "Field8"
	1    6050 3650
	1    0    0    -1  
$EndComp
Text Label 6850 4550 0    50   ~ 0
CLK
Text Label 6850 4450 0    50   ~ 0
SD0
Text Label 6850 4350 0    50   ~ 0
SD1
Text Label 4040 6600 0    50   ~ 0
CLK
Text Label 4040 6500 0    50   ~ 0
SD0
Text Label 4040 6400 0    50   ~ 0
SD1
Text Label 4040 6300 0    50   ~ 0
TFT_CS
Text Label 4040 6200 0    50   ~ 0
TFT_RESET
Text Label 4040 6100 0    50   ~ 0
TFT_DC
Text Label 4040 6000 0    50   ~ 0
SD_CS
Text Label 4040 5900 0    50   ~ 0
IO16
Text Label 4040 5800 0    50   ~ 0
IO17
Text Label 4040 5700 0    50   ~ 0
TOUCH_CS
Text Label 4040 5600 0    50   ~ 0
SCK
Text Label 4040 5500 0    50   ~ 0
MISO
Text Label 4040 5300 0    50   ~ 0
SDA
Text Label 4040 4800 0    50   ~ 0
GND
Text Label 4040 4900 0    50   ~ 0
MOSI
Text Label 4040 5000 0    50   ~ 0
SCL
Text Label 6850 3050 0    50   ~ 0
TXD0
Text Label 6850 3150 0    50   ~ 0
RXD0
Text Label 6850 3350 0    50   ~ 0
GND2
Text Label 4040 5100 0    50   ~ 0
TXD0
Text Label 4040 5200 0    50   ~ 0
RXD0
Text Label 4040 5400 0    50   ~ 0
GND2
$Comp
L Connector:Conn_01x19_Female J8
U 1 1 5D1A24C5
P 1220 5710
F 0 "J8" H 1112 4585 50  0000 C CNN
F 1 "Left devkit GEEKNET" H 1112 4676 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 1220 5710 50  0001 C CNN
F 3 "~" H 1220 5710 50  0001 C CNN
	1    1220 5710
	-1   0    0    1   
$EndComp
Text Label 1420 6610 0    50   ~ 0
VCC
Text Label 1420 6010 0    50   ~ 0
IO12
Text Label 1420 5910 0    50   ~ 0
IO14
Text Label 1420 5810 0    50   ~ 0
IO27
Text Label 1420 5710 0    50   ~ 0
IO26
Text Label 1420 5610 0    50   ~ 0
IO25
Text Label 1420 5510 0    50   ~ 0
IO33
Text Label 1420 5410 0    50   ~ 0
IO32
Text Label 1420 5310 0    50   ~ 0
IO35
Text Label 1420 5210 0    50   ~ 0
IO34
Text Label 1420 4810 0    50   ~ 0
VIN
Text Label 1420 4910 0    50   ~ 0
EN
Text Label 1420 5010 0    50   ~ 0
SENSOR_VP
Text Label 1420 5110 0    50   ~ 0
SENSOR_VN
Text Label 1420 6110 0    50   ~ 0
IO13
Text Label 1420 6210 0    50   ~ 0
SD2
Text Label 1420 6310 0    50   ~ 0
SD3
Text Label 1420 6410 0    50   ~ 0
CMD
Text Label 1420 6510 0    50   ~ 0
VBAT
$Comp
L Connector:Conn_01x06_Female J9
U 1 1 5D1FDCCF
P 4920 5790
F 0 "J9" H 4812 5265 50  0000 C CNN
F 1 "Conn_01x06_Female" H 4812 5356 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4920 5790 50  0001 C CNN
F 3 "~" H 4920 5790 50  0001 C CNN
	1    4920 5790
	-1   0    0    1   
$EndComp
Text Label 5120 5990 0    50   ~ 0
VCC
Text Label 5120 5890 0    50   ~ 0
VBAT
Text Label 5120 5790 0    50   ~ 0
CMD
Text Label 5120 5690 0    50   ~ 0
SD3
Text Label 5120 5590 0    50   ~ 0
SD2
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5D2331A8
P 7220 3350
F 0 "#FLG0104" H 7220 3425 50  0001 C CNN
F 1 "PWR_FLAG" V 7220 3478 50  0000 L CNN
F 2 "" H 7220 3350 50  0001 C CNN
F 3 "~" H 7220 3350 50  0001 C CNN
	1    7220 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	7220 3350 7170 3350
Wire Wire Line
	5260 4150 5250 4150
Text Label 5120 5490 0    50   ~ 0
IO13
$Comp
L power:GNDPWR #PWR?
U 1 1 5D2B2E31
P 7260 3210
F 0 "#PWR?" H 7260 3010 50  0001 C CNN
F 1 "GNDPWR" H 7264 3056 50  0000 C CNN
F 2 "" H 7260 3160 50  0001 C CNN
F 3 "" H 7260 3160 50  0001 C CNN
	1    7260 3210
	-1   0    0    1   
$EndComp
Wire Wire Line
	7260 3210 7260 3280
Wire Wire Line
	7260 3280 7170 3280
Wire Wire Line
	7170 3280 7170 3350
Connection ~ 7170 3350
Wire Wire Line
	7170 3350 6850 3350
$EndSCHEMATC
