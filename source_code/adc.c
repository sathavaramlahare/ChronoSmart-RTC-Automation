#include<lpc21xx.h>
#include"Defines.h"
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
//ADC clk frequency is lessthan 4.5MHZ
#define ADCCLK 3000000 
// Clock divider value for ADC
#define CLK_DIV ((PCLK/ADCCLK)-1)
// Power Down bit position in ADCR register
#define PDN 1<<21
// ADC clock divider value shifted to correct position
#define CLKDIV_VALUE CLK_DIV<<8
// Start conversion bit
#define START_CONV 1<<24
// ADC conversion completion bit
#define DONE_BIT 31
// ADC result bit position
#define Result 6
// ADC channel selection values
#define CH0 0x01
#define CH1 0x02
#define CH2 0x04
#define CH3 0x08
// PINSEL1 configuration values for ADC pins
#define AIN0 0x00400000
#define AIN1 0x01000000
#define AIN2 0x04000000
#define AIN3 0x10000000

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
