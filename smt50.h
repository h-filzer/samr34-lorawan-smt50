#ifndef SMT50_H
#define SMT50_H

#include "periph/adc.h"
#include "cayenne_lpp.h"

#define ADC_RES ADC_RES_12BIT
#define ADC_SAMPLE_DELAY (50u) /* 500 ms */
#define ADC_SAMPLES 100
#define ADC_VREF 3.3

void gatherSensorData(cayenne_lpp_t *lpp);

float measureSoilTemperature(adc_t line);

float measureVbatt(adc_t line);

float measureSoilHumidity(adc_t line);


#endif /* STM50_H */
