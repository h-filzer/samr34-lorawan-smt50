#include "smt50.h"

#include "periph/adc.h"
#include "analog_util.h"

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
    float normalizedSoilHumidity = ((measure(line) * 50.0) / 3.0);
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
