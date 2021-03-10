/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example demonstrating the use of LoRaWAN with RIOT
 *
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "msg.h"
#include "thread.h"
#include "fmt.h"

#include "periph/rtc.h"

// #include "net/loramac.h"
// #include "semtech_loramac.h"
#include "pm_layered.h"
#include "board.h"
#include "ztimer.h"
#include "shell.h"
#include "shell_commands.h"
#include "periph/gpio.h"
#include "ztimer/periph_rtc.h"
#include "periph/rtc.h"
#include "lorawan.h"
#include "cayenne_lpp.h"
#include "periph/adc.h"

#include "smt50.h"

#define ENABLE_DEBUG 1
#include "debug.h"

/* Messages are sent every 300s to respect the duty cycle on each channel */
#define SLEEP_DURATION (300U)

#define SENSOR_SWITCH GPIO_PIN(PB, 22)

static bool initializedADC = false;

void initSensorSwitch(void)
{
    gpio_init(SENSOR_SWITCH, GPIO_OUT);
    gpio_clear(SENSOR_SWITCH);
}

void prepareSleep(void)
{
    gpio_clear(TCXO_PWR_PIN);
    gpio_clear(SENSOR_SWITCH);
}

void postSleep(void)
{
    gpio_set(TCXO_PWR_PIN);
    gpio_set(SENSOR_SWITCH);
    ztimer_spin(ZTIMER_MSEC, 300);
}

void rtc_cb(void *arg)
{
    (void)arg;
    DEBUG_PUTS("Timeer Wakeup");
}

void sleepUtilNextAlarm(void)
{

    ztimer_t timeout = {.callback = rtc_cb, .arg = "Hello ztimer!"};
    ztimer_set(ZTIMER_MSEC, &timeout, SLEEP_DURATION * 1000);
    DEBUG_PUTS("Go to sleep...............");
    pm_set(1);
}

void gatherSensorData(cayenne_lpp_t *lpp)
{
    if (!initializedADC)
    {
        for (int line = 0; line <= 2; line++)
        {
            if (adc_init(ADC_LINE(line)) < 0)
            {
                DEBUG_PRINT("Initialization of ADC_LINE(%u) failed\n", line);
                return;
            }
        }
        initializedADC = true;
    }

    float vBatt = measureVbatt(ADC_LINE(0));
    float soilHumidity = measureSoilHumidity(ADC_LINE(2));
    float soilTemperature = measureSoilTemperature(ADC_LINE(1));
    DEBUG_PRINT("Vbatt: %f\nHum: %f\nTemp: %f\n", vBatt, soilHumidity, soilTemperature);
    cayenne_lpp_add_analog_input(lpp, 1, vBatt);
    cayenne_lpp_add_relative_humidity(lpp, 3, soilHumidity);
    cayenne_lpp_add_temperature(lpp, 5, soilTemperature);
}

semtech_loramac_t loramac;
int main(void)
{

    DEBUG_PUTS("=====================================");
    DEBUG_PUTS(CONFIG_LORAMAC_DEV_EUI_DEFAULT);
    initSensorSwitch();
    ztimer_init();
    pm_unblock(0);
    joinNetwork(&loramac, 3);

    while (true)
    {
        cayenne_lpp_t lpp = {0};
        postSleep();
        gatherSensorData(&lpp);
        sendData(&loramac, &lpp);
        prepareSleep();
        sleepUtilNextAlarm();
        }

    return 0;
}