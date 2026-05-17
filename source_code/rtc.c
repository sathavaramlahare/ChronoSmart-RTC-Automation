#include<lpc21xx.h>
#include "Defines.h"
//Oscillator frequency
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4) 

#define PREINT_VAL ((int)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

//Initializes the RTC peripheral by configuring the prescaler values and enabling RTC clock
void RTC_INIT(void)
{
  //In CCR register reset the clock tick counter
  CCR=1<<1;
	//load integer prescaler value
  PREINT=PREINT_VAL;
	//load fractional prescaler value
  PREFRAC=PREFRAC_VAL;
  //Enable the clock
  CCR=1<<0;
}

//sets the time and store it in registers
void SetRTCTime(int hour,int min,int sec)
{
	HOUR=hour;
	MIN=min;
  SEC=sec;
}
//Reads the current RTC time from RTC registers and stores
void GetRTCTime(int *hour,int *min,int *sec)
{
	*hour=HOUR;
	*min=MIN;
	*sec=SEC;
}
//Display the RTC time on LCD
void	DisplayRTCTime(int hour,int min,int sec)
{
   cmd_lcd(0x80);
	 //Display hour
	 char_lcd(hour/10+48);
	 char_lcd(hour%10+48);
	 char_lcd(':');
	 //display minute
	 char_lcd(min/10+48);
	 char_lcd(min%10+48);
	 char_lcd(':');
	 //display second
	 char_lcd(sec/10+48);
	 char_lcd(sec%10+48);
}
//sets the RTC date values(date,month,year)and store it in RTC registers
void SetRTCDate(int date,int month,int year)
{
	DOM=date;
	MONTH=month;
  YEAR=year;
}
//Reads the current RTC date(date,month,year) from RTC registers and stores pointer to store the current
void GetRTCDate(int *date,int *month,int *year)
{
	*date=DOM;
	*month=MONTH;
	*year=YEAR;
}
//Display the RTC date on LCD
void DisplayRTCDate(int date,int month,int year)
{
   cmd_lcd(0xC0);
	//Display date
	 char_lcd(date/10+48);
	 char_lcd(date%10+48);
	 char_lcd('/');
	 //Display month
	 char_lcd(month/10+48);
	 char_lcd(month%10+48);
	 char_lcd('/');
	 //Display the year
	 int_LCD(year);
}
//Stores the day value into RTC Day register
void SetRTCDay(unsigned int day)
{
   DOW=day;
}
//Reads the current RTC day value from RTC register
void GetRTCDay(unsigned int *day)
{
  *day=DOW;
}
