#include "lorawan.h"
#include <inttypes.h>
#include "fmt.h"
#include "semtech_loramac.h"

#include "ztimer.h"

#define ENABLE_DEBUG 1
#include "debug.h"

#ifndef INITIAL_DATARATE
#define INITIAL_DATARATE LORAMAC_DR_5
#endif

#define JOIN_RETRY_PERIOD (5U * 1000) // 5000 ms
static uint8_t deveui[LORAMAC_DEVEUI_LEN];
static uint8_t appeui[LORAMAC_APPEUI_LEN];
static uint8_t appkey[LORAMAC_APPKEY_LEN];

static bool loramacInitialized = false;

void setupLoraParams(semtech_loramac_t *loramac)
{
    fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
    fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
    fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);

    if (!loramacInitialized)
    {
        semtech_loramac_init(loramac);
        semtech_loramac_set_dr(loramac, INITIAL_DATARATE);
        semtech_loramac_set_deveui(loramac, deveui);
        semtech_loramac_set_appeui(loramac, appeui);
        semtech_loramac_set_appkey(loramac, appkey);
        loramacInitialized = true;
    }
}

uint8_t joinNetwork(semtech_loramac_t *loramac, uint8_t reties)
{

    (void)*loramac;
    (void)reties;
    uint8_t joinStatus = 0;
    setupLoraParams(loramac);
    bool hasJoined = false;
    for (int currentTry = 0; currentTry <= reties; currentTry++)
    {
        if (hasJoined)
        {
            DEBUG_PUTS("Network already joined!");
            break;
        }
        DEBUG_PUTS("Starting join procedure");
        uint8_t joinStatus = semtech_loramac_join(loramac, LORAMAC_JOIN_OTAA);
        switch (joinStatus)
        {
        case SEMTECH_LORAMAC_JOIN_SUCCEEDED:
            DEBUG_PUTS("Network joined!");
            hasJoined = true;
            break;

        case SEMTECH_LORAMAC_ALREADY_JOINED:
            DEBUG_PUTS("Network already joined!");
            hasJoined = true;
            break;

        default:
            DEBUG_PRINT("Not Joined, reason %d; Delaying for %d", joinStatus, JOIN_RETRY_PERIOD);
            ztimer_spin(ZTIMER_MSEC, JOIN_RETRY_PERIOD);
            break;
        }
    }
    return joinStatus;
}

uint8_t sendData(semtech_loramac_t *loramac, cayenne_lpp_t *lpp)
{
    DEBUG_PUTS("Sending...");
    uint8_t ret = semtech_loramac_send(loramac,
                                       lpp->buffer, lpp->cursor);

    if (ret != SEMTECH_LORAMAC_TX_DONE)
    {
        DEBUG_PRINT("Cannot send, ret code: %d\n", ret);
        return 1;
    }
    return 0;
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>

// #include "msg.h"
// #include "thread.h"
// #include "fmt.h"

// #include "periph/rtc.h"

// #include "net/loramac.h"
// #include "semtech_loramac.h"

// /* Messages are sent every 20s to respect the duty cycle on each channel */
// #define PERIOD (20U)

// #define SENDER_PRIO (THREAD_PRIORITY_MAIN - 1)
// static kernel_pid_t sender_pid;
// static char sender_stack[THREAD_STACKSIZE_MAIN / 2];

// semtech_loramac_t loramac;

// static const char *message = "This is RIOT!";

// static uint8_t deveui[LORAMAC_DEVEUI_LEN];
// static uint8_t appeui[LORAMAC_APPEUI_LEN];
// static uint8_t appkey[LORAMAC_APPKEY_LEN];

// static void rtc_cb(void *arg)
// {
//     (void)arg;
//     msg_t msg;
//     msg_send(&msg, sender_pid);
// }

// static void _prepare_next_alarm(void)
// {
//     struct tm time;
//     rtc_get_time(&time);
//     /* set initial alarm */
//     time.tm_sec += PERIOD;
//     mktime(&time);
//     rtc_set_alarm(&time, rtc_cb, NULL);
// }

// static void _send_message(void)
// {
//     printf("Sending: %s\n", message);
//     /* Try to send the message */
//     uint8_t ret = semtech_loramac_send(&loramac,
//                                        (uint8_t *)message, strlen(message));
//     if (ret != SEMTECH_LORAMAC_TX_DONE)
//     {
//         printf("Cannot send message '%s', ret code: %d\n", message, ret);
//         return;
//     }
// }

// static void *sender(void *arg)
// {
//     (void)arg;

//     msg_t msg;
//     msg_t msg_queue[8];
//     msg_init_queue(msg_queue, 8);

//     while (1)
//     {
//         msg_receive(&msg);

//         /* Trigger the message send */
//         _send_message();

//         /* Schedule the next wake-up alarm */
//         _prepare_next_alarm();
//     }

//     /* this should never be reached */
//     return NULL;
// }

// int main(void)
// {
//     puts("LoRaWAN Class A low-power application");
//     puts("=====================================");

//     /* Convert identifiers and application key */
//     fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
//     fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
//     fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);

//     /* Initialize the loramac stack */
//     semtech_loramac_init(&loramac);
//     semtech_loramac_set_deveui(&loramac, deveui);
//     semtech_loramac_set_appeui(&loramac, appeui);
//     semtech_loramac_set_appkey(&loramac, appkey);

//     /* Use a fast datarate, e.g. BW125/SF7 in EU868 */
//     semtech_loramac_set_dr(&loramac, LORAMAC_DR_5);

//     /* Start the Over-The-Air Activation (OTAA) procedure to retrieve the
//      * generated device address and to get the network and application session
//      * keys.
//      */
//     puts("Starting join procedure");
//     if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED)
//     {
//         puts("Join procedure failed");
//         return 1;
//     }
//     puts("Join procedure succeeded");

//     /* start the sender thread */
//     sender_pid = thread_create(sender_stack, sizeof(sender_stack),
//                                SENDER_PRIO, 0, sender, NULL, "sender");

//     /* trigger the first send */
//     msg_t msg;
//     msg_send(&msg, sender_pid);
//     return 0;
// }
