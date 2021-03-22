#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fmt.h"

#include "pm_layered.h"
#include "board.h"
#include "ztimer.h"
#include "periph/gpio.h"
#include "lorawan.h"
#include "cayenne_lpp.h"
#include "periph/adc.h"

#include "sensors.h"

#define ENABLE_DEBUG 1
#include "debug.h"

/* Messages are sent every SLEEP_DURATION to respect the duty cycle on each channel */
#define SLEEP_DURATION (20U)

#define SENSOR_SWITCH GPIO_PIN(PB, 22)

static bool initializedADC = false;

void initSensorSwitch(void)
{
    gpio_init(SENSOR_SWITCH, GPIO_OUT);
    gpio_clear(SENSOR_SWITCH);
}

void prepareSleep(void)
{
    gpio_clear(TX_OUTPUT_SEL_PIN);
    gpio_clear(TX_SWITCH_PWR_PIN);
    gpio_clear(TCXO_PWR_PIN);
    gpio_clear(SENSOR_SWITCH);
}

void postSleep(void)
{
    gpio_set(TX_OUTPUT_SEL_PIN);
    gpio_set(TX_SWITCH_PWR_PIN);
    gpio_set(TCXO_PWR_PIN);
    gpio_set(SENSOR_SWITCH);
    ztimer_spin(ZTIMER_MSEC, 300);
}

void rtc_cb(void *arg)
{
    (void)arg;
    DEBUG_PUTS("Wakeup from sleep...");
}

void sleepUtilNextAlarm(void)
{

    ztimer_t timeout = {.callback = rtc_cb, .arg = "Hello ztimer!"};
    ztimer_set(ZTIMER_MSEC, &timeout, SLEEP_DURATION * 1000);
    DEBUG_PRINT("Go to sleep for %u Seconds\n", SLEEP_DURATION);
    pm_set(1);
}

void gatherSensorData(cayenne_lpp_t *lpp)
{
    if (!initializedADC)
    {
        for (u_int8_t line = 0; line < ADC_NUMOF; line++)
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
    ztimer_spin(ZTIMER_MSEC, 300);
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