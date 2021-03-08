rak4260 schematic https://downloads.rakwireless.com/LoRa/RAK4260/Hardware-Specification/RAK4260_VB_Schematic_20190807.pdf
samr https://www.mouser.de/datasheet/2/268/SAMR34_R35_Low_Power_LoRa_Sub_GHz_SiP_Data_Sheet_D-1507280.pdf
antenna switch https://www.mouser.de/datasheet/2/472/SKY13373_460LF_201264N-1524768.pdf
bastwan https://github.com/ElectronicCats/BastWAN/blob/master/Hardware/Bast_WAN.pdf
bc546 https://www.componentsinfo.com/bc546-transistor-pinout-equivalent/
smt50 http://www.truebner.de/smt50 

erase chip ./edbg/edbg -b -e -t samr34

for _ in {1..1000}; do ./edbg/edbg -b -e -t samr34; done 