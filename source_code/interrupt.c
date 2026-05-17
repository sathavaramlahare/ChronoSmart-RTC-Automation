#include<lpc21xx.h>
#include "Defines.h"
// External interrupt channel number for EINT0
#define EINT0_CHNO 14
// LED connected to indicate interrupt activity
#define EINT0_LED 24
// External flag variable used in main program
extern int flag;
// System lock variable used during over-temperature condition
int system_lock=0;

/*Interrupt Service Routine for external interrupt EINT0.Sets flag when interrupt occurs.
Ignores interrupt if system is locked.*/
void eint0_isr(void)__irq
{
	// Ignore interrupt if system is locked
	if(system_lock)
	{
		// Clear EINT0 interrupt flag
		EXTINT=1<<0;
		//end of interrupt to VIC
		VICVectAddr=0;
		return;
	}
	// Set flag to indicate interrupt occurrence
   flag=1;
	 //END eint0_flag clear the flag
	 EXTINT =1<<0;
	 //end of of the interupt
	 VICVectAddr=0;
}
//Configures and enables external interrupt EINT0
void enable_eint0()
{
	//cfg p0.8 as output
	IODIR0|=1<<EINT0_LED;
	//cfg p0.1 as EINT0
	PINSEL0|=0x0000000C;
	//Select the type of interrupt as irq
	VICIntSelect=0<<EINT0_CHNO;
	//Enable the interrupt source
	VICIntEnable=1<<EINT0_CHNO;
	//Assign the ISR address 
	VICVectAddr0=(unsigned int)eint0_isr;
	//select the slot and assign interrupt channel
	VICVectCntl0=(1<<5)|(EINT0_CHNO);
	//configure interrupt as edge-trigger
	EXTMODE =1<<0;
	//selcting raising edge  1->raising edge 0->falling edge
	//EXTPOLAR =~1<<0;
}
