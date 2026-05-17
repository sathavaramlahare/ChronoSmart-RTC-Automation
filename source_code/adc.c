#include<lpc21xx.h>
#include "adc.h"
#include "delay.h"

//Initializes ADC peripheral and configures ADC pin
void INIT_ADC(void)
{
  //cfg p0.27 as ADC port pin
  PINSEL1|=AIN1;
  //set powerdown mode into operaionalmode
  ADCR|=PDN|CLKDIV_VALUE;
}
//Reads analog value from selected ADC channel and converts it into equivalent analog voltage
void Read_ADC(char chno,int *Adcval,float *eAR)
{
   //Clear previously selected channel bits
   ADCR&=~(255<<0);
   //Select required ADC channel
   ADCR|=chno;
   //Start ADC conversion
   ADCR|=START_CONV;
   //Small delay for conversion stabilization
   delay_us(3);
   //Wait until conversion completes
   while(((ADDR>>DONE_BIT)&1)==0);
   // Stop ADC conversion
   ADCR&=~(START_CONV);
   //Extract 10-bit ADC digital value
   *Adcval=((ADDR>>Result)&1023);
   // Convert digital value to equivalent analog voltage
   *eAR=((3.3/1023)*(*Adcval));
}
