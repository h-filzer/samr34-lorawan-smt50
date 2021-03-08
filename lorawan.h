#ifndef LORA_H
#define LORA_H

#include <inttypes.h>
#include "semtech_loramac.h"
#include "cayenne_lpp.h"


uint8_t joinNetwork(semtech_loramac_t *loramac, uint8_t reties);
uint8_t sendData(semtech_loramac_t *loramac, cayenne_lpp_t *lpp);


#endif /* LORA_H */