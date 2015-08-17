#ifndef _ADC_H__
#define _ADC_H__

typedef enum
{
	ADC_PRESCALER2      = 0b001,
    ADC_PRESCALER4      = 0b010,
    ADC_PRESCALER8      = 0b011,
    ADC_PRESCALER16     = 0b100,
    ADC_PRESCALER32     = 0b101,
    ADC_PRESCALER64     = 0b110,
    ADC_PRESCALER128    = 0b111
} ADC_PRESCLAER;

typedef enum
{
    ADC_RIGHT_ADJUSTED = 0,
    ADC_LEFT_ADJUSTED = 1
} ADC_RESULT_FORMAT;

typedef enum
{
    ADC_VR_AREF = 0b00,
    ADC_VR_AVCC = 0b01,
    ADC_VR_INTERNAL = 0b11
} ADC_VOLTAGE_REFERENCE;

typedef enum
{
	ADC_CHANNEL0 = 0,
	ADC_CHANNEL1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
    ADC_CHANNEL8,
    ADC_TEMP_SENSOR = 0b1000,
    ADC_1_1V = 0b1110,
    ADC_GND = 0b1111
} ADC_CHANNEL;

inline void adcEnable(void);
inline void adcDisable(void);
inline void adcEnableInterurpt(void);
inline void adcDisableInterrupt(void);
inline void adcSetPrescaler(ADC_PRESCLAER prescaler);
inline void adcSetResultFormat(ADC_RESULT_FORMAT resultFormat);
inline void adcSetVoltageReference(ADC_VOLTAGE_REFERENCE voltageReference);
inline void adcSelectChannel(ADC_CHANNEL channel);
inline void adcStartConvert(ADC_CHANNEL channel);
inline unsigned int adcReadLeftAdjusted(void);
inline unsigned int adcReadRightAdjusted(void);
inline unsigned int adcRead(void);

#endif /* _ADC_H__ */
