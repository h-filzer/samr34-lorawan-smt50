# name of your application
APPLICATION = Rak4260-bastwan-lora-smt50

# If no BOARD is found in the environment, use this default:
BOARD ?= bastwan
#PROGRAMMER ?= edbg
TERMFLAGS=-s 115200 -p /dev/ttyACM1

DEVEUI ?= 0000000000000000
APPKEY ?= 00000000000000000000000000000000
APPEUI ?= 0000000000000000

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP


# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

DRIVER ?= sx1276
LORA_REGION ?= EU868

USEPKG += semtech-loramac
USEPKG += cayenne-lpp

USEMODULE += ztimer 
USEMODULE += ztimer_msec 
USEMODULE += pm_layered
USEMODULE += periph_gpio
USEMODULE += periph_adc
USEMODULE += analog_util
USEMODULE += fmt
USEMODULE += cayenne-lpp
#USEMODULE += printf_float
USEMODULE += $(DRIVER)


include $(RIOTBASE)/Makefile.include

ifndef CONFIG_KCONFIG_USEMODULE_LORAWAN
  # OTAA compile time configuration keys
  CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
  CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
  CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"
endif
