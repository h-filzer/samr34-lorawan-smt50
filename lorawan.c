#include "lorawan.h"
#include <inttypes.h>
#include "fmt.h"
#include "semtech_loramac.h"

#include "ztimer.h"

#define ENABLE_DEBUG 0
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
    if (!loramacInitialized)
    {
        fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
        fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
        fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);
        semtech_loramac_init(loramac);
        // Disable Confirmation from Network
        semtech_loramac_set_tx_mode(loramac, LORAMAC_TX_UNCNF);
        semtech_loramac_set_dr(loramac, INITIAL_DATARATE);
        //semtech_loramac_set_adr(loramac, true);
        //semtech_loramac_set_tx_power(loramac, 1);
        semtech_loramac_set_deveui(loramac, deveui);
        semtech_loramac_set_appeui(loramac, appeui);
        semtech_loramac_set_appkey(loramac, appkey);
        loramacInitialized = true;
    }
}

uint8_t joinNetwork(semtech_loramac_t *loramac, uint8_t maxRetries)
{

    (void)*loramac;
    (void)maxRetries;
    uint8_t joinStatus = 0;
    setupLoraParams(loramac);
    bool hasJoined = false;
    for (int currentTry = 0; currentTry <= maxRetries; currentTry++)
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
            DEBUG_PUTS("Network joined! SEMTECH_LORAMAC_JOIN_SUCCEEDED");
            hasJoined = true;
            break;

        case SEMTECH_LORAMAC_ALREADY_JOINED:
            DEBUG_PUTS("Network already joined! SEMTECH_LORAMAC_ALREADY_JOINED");
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
