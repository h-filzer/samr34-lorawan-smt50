## RIOT OS on BastWan

Samll example to demonstrate running RIOT OS on a [BastWan Board](https://github.com/ElectronicCats/BastWAN/).
The example includes:
- Usage of GPIO
- Usage of ADC
- Sleep Mode
- LoraWan, joining to Chirpstack and sending Messages



UF2 bootloader was removed so you need to connect UART to be able to use Serial communication. Will retest with UF2 later and update RIOT board definition to support flashing and serial over UF2.

Regarding LowPower the Device consumes about 115uA in sleep mode with RAM retention which is quite high but i was not able to measure the mcu power consumption alone so the value is for the whole board (LDO, LiPo Charger, Vbatt voltage devider, Crypto, MCU ..).

Untested:
- LoraWan receive
- LoraWan adr
- I2C
- Crypto Chip
- ...

### Installing

A PR against RIOT OS to support the BastWan board is in progress. For now you can use the [bastwan Branch](https://github.com/h-filzer/RIOT/tree/bastwan).
- setup arm toolchain
- Clone this Repo
- Clone https://github.com/h-filzer/RIOT.git and switch to bastwan branch
- `DEVEUI=<YOUR_DEV_EUID> APPKEY=<YOUR_APPKEY> make all flash term`

## Ressources

My simple sensor setup is using a [smt50](http://www.truebner.de/smt50) for measuring soil humidity and soil temperature. See schematic folder.

[rak4260 schematic](https://downloads.rakwireless.com/LoRa/RAK4260/Hardware-Specification/RAK4260_VB_Schematic_20190807.pdf)

[samr datasheet](https://www.mouser.de/datasheet/2/268/SAMR34_R35_Low_Power_LoRa_Sub_GHz_SiP_Data_Sheet_D-1507280.pdf)


[antenna switch](https://www.mouser.de/datasheet/2/472/SKY13373_460LF_201264N-1524768.pdf)

[bastwan schematic](https://github.com/ElectronicCats/BastWAN/blob/master/Hardware/Bast_WAN.pdf)

[bc546](https://www.componentsinfo.com/bc546-transistor-pinout-equivalent/)


## Erasing flash

While developing and experimenting with low lower and sleep modes the device did not wake up again which blocks reflashing.

Luckily RIOT OS comes with edbg tool so someone can erase the flash by running 

`for _ in {1..1000}; do ./edbg/edbg -b -e -t samr34; done` 

and pressing the reset button quite often. It will eventually erase the chip. Dirty but working...

