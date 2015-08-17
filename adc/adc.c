#include "adc.h"

#include <avr/io.h>

inline void adcEnable(void)
{
    ADCSRA |= (1 << ADEN);
}

inline void adcDisable(void)
{
    ADCSRA &= ~(1 << ADEN);
}

inline void adcEnableInterurpt(void)
{
    ADCSRA |= (1 << ADIE);
}

inline void adcDisableInterrupt(void)
{
    ADCSRA &= ~(1 << ADIE);
}

inline void adcSetPrescaler(ADC_PRESCLAER prescaler)
{
    ADCSRA |= prescaler;
}

inline void adcSetResultFormat(ADC_RESULT_FORMAT resultFormat)
{
    ADMUX |= resultFormat << 5;
}

inline void adcSetVoltageReference(ADC_VOLTAGE_REFERENCE voltageReference)
{
    ADMUX |= voltageReference << 6;
}

inline void adcSelectChannel(ADC_CHANNEL channel)
{
    ADMUX = (ADMUX & 0b11110000) | channel;
}

inline void adcStartConvert(ADC_CHANNEL channel)
{
    adcSelectChannel(channel);
	ADCSRA |= (1 << ADSC);
}

inline unsigned int adcReadLeftAdjusted(void)
{
    return ((ADCH << 2) | (ADCL >> 6));
}

inline unsigned int adcReadRightAdjusted(void)
{
    return ((ADCH << 8) | ADCL);
}

inline unsigned int adcRead(void)
{
    return ADC;
}
