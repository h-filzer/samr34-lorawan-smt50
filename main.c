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

/* Messages are sent every 20s to respect the duty cycle on each channel */
#define PERIOD (5U)

void rtc_cb(void *arg)
{
    (void)arg;
}

void _prepare_next_alarm(void)
{

    // ztimer_t timeout = {.callback = rtc_cb, .arg = "Hello ztimer!"};
    // ztimer_set(ZTIMER_MSEC, &timeout, 5000);
    ztimer_periph_rtc_init(ZTIMER_MSEC);
    struct tm time;
    rtc_get_time(&time);
    /* set initial alarm */
    time.tm_sec += PERIOD;
    mktime(&time);
    rtc_set_alarm(&time, rtc_cb, NULL);
    pm_blocker_t blocker = pm_get_blocker();
    printf("Blocker val %ld , pwr modeblocker: %hhn ", blocker.val_u32, blocker.val_u8);

    gpio_clear(TCXO_PWR_PIN);
    pm_set(1);
    puts("Wakeup after ");
    gpio_set(TCXO_PWR_PIN);
}

void _send_message(void)
{
}

void sender(void)
{

    ztimer_periph_rtc_init(ZTIMER_MSEC);
    ztimer_spin(ZTIMER_MSEC, 3000);

    while (1)
    {
        //  gpio_set(TCXO_PWR_PIN);
        /* Trigger the message send */

        puts("Try Sending.....");
        _send_message();
        /* Schedule the next wake-up alarm */
        puts("Prepare alarm.....");
        _prepare_next_alarm();
        puts("Alarm prepared.....");
    }
}

int main(void)
{

    puts("=====================================");
    puts(CONFIG_LORAMAC_DEV_EUI_DEFAULT);
    pm_unblock(0);
    sender();
    return 0;
}