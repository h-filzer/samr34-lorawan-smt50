#include "smt50.h"

#include <stdio.h>
#include "periph/adc.h"
#include "analog_util.h"
#include "cayenne_lpp.h"

static bool initializedADC = false;

float measure(adc_t line)
{
    float measurements = 0.0;
    for (int i = 0; i < ADC_SAMPLES; i++)
    {
        int32_t sample = adc_sample(line, ADC_RES);
        measurements += adc_util_mapf(sample, ADC_RES, 0.0, ADC_VREF);
    }
    return measurements / ADC_SAMPLES;
}

float measureSoilHumidity(adc_t line)
{
    float normalizedSoilHumidity = ((measure(line) * 50) / 3.0);
    return normalizedSoilHumidity;
}

float measureVbatt(adc_t line)
{
    // R3= 980k; R4=1.3m -> u0= (sample * (R3+R4))/R4);
    float normalizedVoltage = ((measure(line) * 2.28) / 1.3);
    //printf("Converted %f\n", normalizedVoltage);
    return normalizedVoltage;
}

float measureSoilTemperature(adc_t line)
{
    float normalizedHumidity = (measure(line) - 0.5) * 100;
    //printf("Converted %f\n", normalizedVoltage);
    return normalizedHumidity;
}

void _print_buffer(cayenne_lpp_t *lpp)
{
    for (uint8_t i = 0; i < lpp->cursor; ++i)
    {
        printf("%02X ", lpp->buffer[i]);
    }
    puts("");
}

void gatherSensorData(cayenne_lpp_t *lpp)
{
    if (!initializedADC)
    {
        for (int line = 1; line <= 2; line++)
        {
            if (adc_init(ADC_LINE(line)) < 0)
            {
                printf("Initialization of ADC_LINE(%u) failed\n", line);
                return;
            }
        }
        initializedADC = true;
    }

    float vBatt = measureVbatt(ADC_LINE(0));
    float soilHumidity = measureSoilHumidity(ADC_LINE(1));
    float soilTemperature = measureSoilTemperature(ADC_LINE(2));
    printf("Vbatt: %f\nHum: %f\nTemp: %f\n", vBatt, soilHumidity, soilTemperature);
    cayenne_lpp_add_analog_input(lpp, 1, vBatt);
    cayenne_lpp_add_relative_humidity(lpp, 3, soilHumidity);
    cayenne_lpp_add_temperature(lpp, 5, soilTemperature);
    _print_buffer(lpp);
}