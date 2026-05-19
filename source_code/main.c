#include<lpc21xx.h>
#include"Defines.h"
#include"interrupt.h"
#include"adc.h"
#include"lcd.h"
#include"rtc.h"
#include"keypad.h"
#include"menu.h"
void controldevices(void);
//External Interrupt Channel number for EINT0
#define EINT0_CHNO 14

//Device output pins
#define Device_1 24//Port 1.24
#define Device_2 25//port 1.25

//RTC Time variables
int hour,min,sec,date,month,year,current_time;
unsigned int day;
int flag = 0;
char Day[7][4]={"sun","mon","tue","wed","thu","fri","sat"};

//ADC variables
int dval;
float ear;

//Temperature threshold value
int temp_threshold=40;

//Device-1 ON and OFF timing values
int on_hour1=10,on_min1=45,on_sec1=35;
int off_hour1=01,off_min1=5,off_sec1=5;

//Device-2 ON and OFF timing values
int on_hour2=22,on_min2=2,on_sec2=1;
int off_hour2=22,off_min2=4,off_sec2=15;

int Device_1_ON_Time;
int Device_1_OFF_Time;
int Device_2_ON_Time;
int Device_2_OFF_Time;

void temperature_shutdown(void);
void temperature_recover(void);

int main()
{
	 int temp;
	 LCD_INIT();//LCD initialization
   enable_eint0();//Enable external interrupt
	 RTC_INIT();//RTC initialization
	 KPM_INIT();//Keypad initialization
	 INIT_ADC();//ADC initialization
	
	 //Setting direction for the Devices
	 IODIR1|=1<<Device_1;
	 IODIR1|=1<<Device_2;
   
	 //Convert Device-1 ON/OFF timings into seconds
	 Device_1_ON_Time  = on_hour1*3600 + on_min1*60 + on_sec1;
   Device_1_OFF_Time = off_hour1*3600 + off_min1*60 + off_sec1;

   //Convert Device-2 ON/OFF timings into seconds
   Device_2_ON_Time  = on_hour2*3600 + on_min2*60 + on_sec2;
   Device_2_OFF_Time = off_hour2*3600 + off_min2*60 + off_sec2;
	
	//set the initial time hours,minutes,seconds
	SetRTCTime(22,59,58);
  //set the initial RTC date
	SetRTCDate(25,04,2026);
  //set the initial RTC day
	SetRTCDay(2);
	
	while(1)
	{
		//check whether system is locked due to high temperature
		if(system_lock)
    {
			Read_ADC(CH1,&dval,&ear);
      temp=ear*100;
			if(temp < 40)
			{
				temperature_recover();
			}
			continue;
    }

	//Read current RTC time
	GetRTCTime(&hour,&min,&sec);
  //Read current RTC day
	GetRTCDate(&date,&month,&year);
  //Read current RTC day
	GetRTCDay(&day);

	//Display time on LCD	
	cmd_lcd(0x80);
	DisplayRTCTime(hour,min,sec);
  
	//Conevert current time into seconds
	current_time = hour*3600+min*60+sec;

	//Read the value from LM35 sensor,convert and display on LCD
  Read_ADC(CH1,&dval,&ear);

  temp=ear*100;
  //if temperature exceeds threshold
	if(temp>temp_threshold)
	{
			temperature_shutdown();
		      continue;
	}
	//Display temperature on LCD
	cmd_lcd(0x80+9);
	str_lcd("T:");
  if(temp<10)
		char_lcd(' ');
	  int_LCD(temp);
	  //Degree symbol
	  char_lcd(0xDF);	//1101 1111 for displaying the degree synmbol
		char_lcd('C');

	//Display the date,month,year
	    cmd_lcd(0xC0);
	    DisplayRTCDate(date,month,year);
	    char_lcd(30);

	//DisplayRTCDay();
	//Display day on LCD
	str_lcd(  Day[day]);
		
  //Device ON-OFF 
	//Control devices based on timing
  controldevices();
  if(flag)
  {
    flag=0;
		while(1)
		{
		 controldevices();
     if(check_password()==1)
			 break;
	 }
     cmd_lcd(0x01);
	}
 }	
}
//Function to shutdown system during high temperature
void temperature_shutdown()
{
	 if(system_lock==0)
	 {
    // Disable interrupt
    VICIntEnClr = (1<<EINT0_CHNO);
	  //clear interrupt flag
    EXTINT = (1<<0);
    // Turn OFF devices
    IOCLR1 = (1<<Device_1);
    IOCLR1 = (1<<Device_2);
    
    cmd_lcd(0x01);
    cmd_lcd(0x80);
    str_lcd("Temp exceeded!!!");
    system_lock = 1;   // lock system
		 }
}
//Function to recover system after temperature recovery
void temperature_recover()
{
	// Enable interrupt again
	VICIntEnable = (1<<EINT0_CHNO);

	system_lock = 0;
	cmd_lcd(0x01);
	delay_ms(200);
}
//Function to control devices based on ON/OFF timing
void controldevices()
{
	//Read current RTC time
	GetRTCTime(&hour,&min,&sec);
  current_time = hour*3600 + min*60 + sec;
	//Device-1 control
	//Normal timing condition
	if(Device_1_ON_Time < Device_1_OFF_Time)
  {
    if(current_time >= Device_1_ON_Time && current_time < Device_1_OFF_Time)
        IOSET1 = 1<<Device_1;
    else
        IOCLR1 = 1<<Device_1;
   }
	 //Midnight crossing condition
   else
   {
      if(current_time >= Device_1_ON_Time || current_time < Device_1_OFF_Time)
         IOSET1 = 1<<Device_1;
      else
         IOCLR1 = 1<<Device_1;
    }
	 //Device-2 timing
	 //Normal timing condition
   if(Device_2_ON_Time < Device_2_OFF_Time)
   {
     if(current_time >= Device_2_ON_Time && current_time < Device_2_OFF_Time)
        IOSET1 = 1<<Device_2;
     else
        IOCLR1 = 1<<Device_2;
    }
  //Midnight crossing condition
    else
    {
      if(current_time >= Device_2_ON_Time || current_time < Device_2_OFF_Time)
        IOSET1 = 1<<Device_2;
      else
        IOCLR1 = 1<<Device_2;
    }
}

