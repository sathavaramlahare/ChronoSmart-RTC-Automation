#include"delay.h"
#include"device.h"
#include"menu.h"
#include"lcd.h"
#include"RTC.h"
#include"keypad.h"
#include"defines.h"
#include<string.h>
// External array storing day names
extern char Day[7][4];
char key;
int i;
// External temperature threshold variable
extern int temp_threshold;
//Removes the previously entered character from LCD display while taking keypad input.
void backspace()
{
    if(i>0)			 
		   {
			   i--;
			   cmd_lcd(0x10);//Move cursor left
			   char_lcd(' ');//Clear character
			   cmd_lcd(0x10);//Move cursor left again
			 }
}
//Converts total seconds into HH:MM:SS format and displays the time on LCD.
void DisplayTimeFromSeconds(int total_sec)
{
    int h, m, s;

    h = total_sec / 3600;
    m = (total_sec % 3600) / 60;
    s = total_sec % 60;
    // Display hours
    char_lcd(h/10 + '0');
    char_lcd(h%10 + '0');
    char_lcd(':');
    // Display minutes
    char_lcd(m/10 + '0');
    char_lcd(m%10 + '0');
    char_lcd(':');
    //display seconds
    char_lcd(s/10 + '0');
    char_lcd(s%10 + '0');
}
//Reads numeric keypad input from user.
int get_2digit(int digits)
{
	int value=0;
	char key;
	i=0;
	while(1)
	{
	key=keyscan();
	// Backspace operation
	if(key=='#')
  {
		 backspace();
		 value=value/10;
	}
  // Accept only numeric keys			
	else if(key>='0' && key<='9')
	{
		if(i<digits)
		{
	    char_lcd(key);
	    value=value*10+(key-'0');
	    i++;
		}
	}
	// Confirm input using '*'
	else if(key=='*')
	{
		while(colscan()); //wait for switch release
		if(i==0)
			 return -1;
			else
				break;
	 }
  while(colscan());
  }
	return value;
}

//Allows user to change system password after verifying old password.
void Change_password(void)
{
	extern char password[5];
	char key;
	char old_pass[5];
  char new_pass[5];
	 i=0;
	//Checking the old password with the entered passowrd
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	str_lcd("old pass:");
	cmd_lcd(0xc0);
	//check_password();
	while(i<4)
	{
	   key=keyscan();
		// Backspace support
	   if(key=='#')
	   {
		   backspace();
		 }
		// Accept numeric digits
		else if(key>='0' && key<='9')
		{
			 old_pass[i]=key;
			 char_lcd(key);
			 delay_ms(50);
			 cmd_lcd(0x10);
			 char_lcd('*');
			 i++;
		 }
		 while(colscan());
	}
	old_pass[i]='\0';
  // Verify old password
	if(strcmp(old_pass,password)!=0)
	{
	   cmd_lcd(0x01);
	   cmd_lcd(0x80);
	   str_lcd("Wrong password");
	   delay_ms(1000);
	   return;
	}
	else
	{ 
	// Ask for new password
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	str_lcd("new pass(4digi):");
	cmd_lcd(0xc0);
	i=0;
	 while(1)
		{
			 key=keyscan();
			 if(key=='#')
			 {
				 backspace();
			 }
			else if(key>='0' && key <='9')
			{
				if(i<4)
				{
			   new_pass[i]=key;
			   char_lcd(key);
			   delay_ms(50);
			   cmd_lcd(0x10);
			   char_lcd('*');
			   i++;
				}
			}
	  else
		{
			cmd_lcd(0x01);
			str_lcd("Invalid");
			delay_ms(1000);
			cmd_lcd(0x01);
			str_lcd("New pass(4dig):");
			cmd_lcd(0xc0);
			i=0;
		}
				while(colscan());
		    if(i==4)
					break;
	}
	  new_pass[i]='\0';
	  //Store new password
		strcpy(password,new_pass);
	}
}

//Allows user to edit RTC time(hours, minutes and seconds).
void time_edit()
{
	int hour=0,min=0,sec=0,temp;
		// Read current RTC time
	GetRTCTime(&hour,&min,&sec);
	//Edit hour
	while(1)
	{
	    cmd_lcd(0x01);
	    cmd_lcd(0x80);
	    str_lcd("hour(00-23)");
	    cmd_lcd(0xc0);
	    temp=get_2digit(2);
		  if(temp==-1)
				break;
		if(temp>=00 && temp<=23)
		{
		    hour=temp;
			  break;
		}
		   cmd_lcd(0x01);
		   str_lcd("invalid");
		   delay_ms(1000);
	}

	 //Edit minute
	while(1)
	{
		  cmd_lcd(0x01);
	      str_lcd("min(00-59)");
	      cmd_lcd(0xc0);
		  temp=get_2digit(2);
		  if(temp==-1)
				break;
		  if(temp>=00 && temp<=59)
			{ 
				 min=temp;
			   break;
			}
		 	cmd_lcd(0x01);
		  str_lcd("invalid");
		  delay_ms(1000);
    }
	//Edit second
	 while(1)
	 {
		  cmd_lcd(0x01);
	      str_lcd("sec(00-59)");
	      cmd_lcd(0xc0);
		  temp=get_2digit(2);
		  if(temp==-1)
			{
				break;
			}
		  if(temp>=00 && temp<=59)
			{	
				 sec=temp;
			   break;
			}
			cmd_lcd(0x01);
		  str_lcd("invalid");
		  delay_ms(1000);
	 }
	 //update RTC time
		SetRTCTime(hour,min,sec);
	 	// Display updated time
	  cmd_lcd(0x01);
	  cmd_lcd(0x80);
	  DisplayRTCTime(hour,min,sec);
	  delay_ms(1000);
}
//Allows user to edit RTC date,month and year with validation.
void date_edit()
{
	int date=0,month=0,year=0,temp,max_days;
	// Read current date
	GetRTCDate(&date,&month,&year);

	//Edit date
	while(1)
	{
	   cmd_lcd(0x01);
	   cmd_lcd(0x80);
	   str_lcd("date(01-31)");
	   cmd_lcd(0xc0);
	   temp=get_2digit(2);
		 if(temp==-1)
			 break;
	   if(temp>=01 && temp<=31)
		 {
			 date=temp;
			 break;
		 }
		  cmd_lcd(0x01);
		  str_lcd("invalid");
		  delay_ms(1000);
	}
	   
   //Edit month
	while(1)
	{
	    cmd_lcd(0x01);
		  cmd_lcd(0x80);
	    str_lcd("month(1-12)");
	    cmd_lcd(0xc0);
		  temp=get_2digit(2);
		  if(temp==-1)
				break;
		  if(temp>=01 && temp<=12)
			{
				month=temp;
			  break;
			}
		  cmd_lcd(0x01);
		  str_lcd("invalid");
		  delay_ms(1000);
	}
	//Edit year
	while(1)
	{
		cmd_lcd(0x01);
	  str_lcd("year(2026-4096)");
	  cmd_lcd(0xc0);
		temp=get_2digit(4);
		if(temp==-1)
			break;
		if(temp>=2026 && temp<=4096)
		{
			year=temp;
			break;
		}
		cmd_lcd(0x01);
		str_lcd("invalid");
		delay_ms(1000);
	}
// Calculate maximum days for selected month
if(month==1 || month==3 || month==5 || month==7 ||
       month==8 || month==10 || month==12)
        max_days = 31;

    else if(month==4 || month==6 || month==9 || month==11)
        max_days = 30;

    else if(month==2)
    {
			// Leap year validation
        if((year%4==0 && year%100!=0) || (year%400==0))
            max_days = 29;  // leap year
        else
            max_days = 28;
    }
		// Validate date
    if(date <= max_days)
    {
			 // Update RTC date
        SetRTCDate(date,month,year);
        cmd_lcd(0x01);
        cmd_lcd(0x80);
        DisplayRTCDate(date,month,year);
        delay_ms(1000);
    }
    else
    {
        cmd_lcd(0x01);
        cmd_lcd(0x80);
        str_lcd("Invalid date!");
        delay_ms(1500);
    }
}

//Function to edit and update the current day in RTC
void day_edit()
{
	int day,temp1=-1;
	//Get current day value from RTC
	GetRTCDay(&day);
	while(1)
	{
	//Clear LCD and display day edit message
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	str_lcd("day(0-6)");
	cmd_lcd(0xc0);
	while(1)
	{
	key=keyscan();
	//If '#' pressed, clear entered value
	if(key=='#')
{
    if(temp1 != -1)
    {
        temp1 = -1;
        cmd_lcd(0x10);
        char_lcd(' ');
        cmd_lcd(0x10);
    }
}
//Accept only values between 0 and 6
else if(key>='0' && key<='6')
{
    char_lcd(key);
	 //Convert ASCII to integer
    temp1 = key - '0';
}
//If '*' pressed confirm entered day
else if(key=='*')
{
    while(colscan());
    if(temp1 != -1)
    {
        day = temp1;
        break;
    }
}
  while(colscan());
}
	//Store updated day into RTC
  SetRTCDay(day);
  //Display updated day on LCD
	cmd_lcd(0x01);
	cmd_lcd(0x80);
  str_lcd(  Day[day]);
  delay_ms(1000);
  return;
  }
}
//Function to display invalid message on LCD
void invalid_msg()
{
	 	//Clear LCD
    cmd_lcd(0x01);
    //Display invalid text
    str_lcd("invalid");
    delay_ms(1000);
}
////Function to edit ON/OFF time fields like hour/min/sec
void edit_time_field(char *msg,int *value,int min,int max)
{
    int temp;
    while(1)
    {
        cmd_lcd(0x01);
        //Display field name
        str_lcd(msg);
        char_lcd(30);
			  //Display current value
        int_LCD(*value);
        cmd_lcd(0xc0);
        //Get 2-digit user input
        temp = get_2digit(2);
        if(temp == -1)
            break;
        //Check entered value range
        if(temp >= min && temp <= max)
        {
					  //Update value
            *value = temp;
            break;
        }
        //Show invalid message if range fails
        invalid_msg();
    }
}

//Function to edit Device-1 ON and OFF timings
void Device1_edit()
{
    while(1)
    {
			  //Display menu options
        cmd_lcd(0x01);
        cmd_lcd(0x80);
        str_lcd("1.ON Time");
        cmd_lcd(0xc0);
        str_lcd("2.OFF");
        char_lcd(30);
        str_lcd("3.Back");
        key = keyscan();
        if(key=='1' || key=='2' || key=='3')
        {
            while(colscan());

            switch(key)
            {
                 //Edit on-time
                case '1':

                    edit_time_field("ON hr",&on_hour1,0,23);
                    edit_time_field("ON min",&on_min1,0,59) ;
                    edit_time_field("ON sec",&on_sec1, 0,59);
								    //Convert ON time into total seconds
                    Device_1_ON_Time =on_hour1 * 3600 +on_min1 * 60 + on_sec1;
                    //Display updated ON time
								    cmd_lcd(0x01);
                    cmd_lcd(0x80);
                    DisplayTimeFromSeconds(Device_1_ON_Time);
                    delay_ms(1000);
                    break;

                //Edit off time
                case '2':
                    edit_time_field( "OFF hr",&off_hour1,0,23);
                    edit_time_field("OFF min",&off_min1, 0,59);
                    edit_time_field("OFF sec",&off_sec1, 0,59);
                    //Convert OFF time into total seconds
                    Device_1_OFF_Time =off_hour1 * 3600 +off_min1 * 60 + off_sec1;
                    //Display updated OFF time
								    cmd_lcd(0x01);
                    cmd_lcd(0x80);
                    DisplayTimeFromSeconds(Device_1_OFF_Time);
                    delay_ms(1000);
                    break;
                //Return to previous menu
                case '3':
                    return;
            }
        }
    }
}
//Function to edit Device-2 ON and OFF timings
void Device2_edit()
{
    while(1)
    {
			  //Display menu options
        cmd_lcd(0x01);
        cmd_lcd(0x80);
        str_lcd("1.ON Time");
        cmd_lcd(0xc0);
        str_lcd("2.OFF");
        char_lcd(30);
        str_lcd("3.Back");
        key = keyscan();
        if(key=='1' || key=='2' || key=='3')
        {
            while(colscan());
            switch(key)
            {
                 //Edit on-time
                case '1':

                    edit_time_field("ON hr",&on_hour2,0,23);
                    edit_time_field("ON min",&on_min2,0,59) ;
                    edit_time_field("ON sec",&on_sec2, 0,59);
                    //Convert ON time into total seconds
								    Device_2_ON_Time =on_hour2 * 3600 +on_min2 * 60 + on_sec2;
                    //Display updated ON time
								    cmd_lcd(0x01);
                    cmd_lcd(0x80);
                    DisplayTimeFromSeconds(Device_2_ON_Time);

                    delay_ms(1000);

                    break;

                //Edit off time
                case '2':

                    edit_time_field( "OFF hr",&off_hour2,0,23);
                    edit_time_field("OFF min",&off_min2,0,59);
                    edit_time_field("OFF sec",&off_sec2, 0,59);
                    //Convert OFF time into total seconds
                    Device_2_OFF_Time =off_hour2 * 3600 +off_min2 * 60 + off_sec2;
                    //Display updated OFF time
								    cmd_lcd(0x01);
                    cmd_lcd(0x80);
                    DisplayTimeFromSeconds(Device_2_OFF_Time);
                    delay_ms(1000);
                    break;
                //Return to previous menu
                case '3':
                    return;
            }
        }
    }
}
///Function to edit temperature threshold value
void temp_edit()
{
    int temp;
    while(1)
    {
			  //Clear LCD and display message
        cmd_lcd(0x01);
        cmd_lcd(0x80);
        str_lcd("Set Temp");
        cmd_lcd(0xC0);
        //Get temperature input
        temp = get_2digit(2);
        if(temp == -1)
            return;
        //Check valid temperature range
        if(temp >= 0 && temp <= 99)
        {
					 //Store threshold value
            temp_threshold = temp;
            //Display saved value
            cmd_lcd(0x01);
            str_lcd("Saved: ");
            int_LCD(temp_threshold);
            char_lcd(0xDF);
            char_lcd('C');

            delay_ms(1000);
            return;
        }
        //Display invalid message
        cmd_lcd(0x01);
        str_lcd("Invalid");
        delay_ms(1000);
    }
}
//Function to display current RTC date
void Date(void)
{
	  //Read current date from RTC
    GetRTCDate(&date,&month,&year);
	  //Display date on LCD
    cmd_lcd(0x01);
		cmd_lcd(0x80);
    DisplayRTCDate(date,month,year);
		delay_ms(1000);
}
//Function to display current RTC time
void Time(void)
{
	  //Read current time from RTC
    GetRTCTime(&hour,&min,&sec);
	  //Display time on LCD
    cmd_lcd(0x01);
		cmd_lcd(0x80);
		DisplayRTCTime(hour,min,sec);
		delay_ms(1000);
}
//Function to display current day from RTC
void rtcday(void)
{
	  //Read current day from RTC
    GetRTCDay(&day);
	  //Display day on LCD
    cmd_lcd(0x01);
		cmd_lcd(0x80);
   	str_lcd(  Day[day]);
		delay_ms(1000);
}
//Function to display Device-1 ON time
void ontime1(void)
{
    cmd_lcd(0x01);
		cmd_lcd(0x80);
	  DisplayTimeFromSeconds(Device_1_ON_Time);
		delay_ms(1000);
}
//Function to display Device-1 OFF time
void offtime1(void)
{
   cmd_lcd(0x01);
	 cmd_lcd(0x80);
	 DisplayTimeFromSeconds(Device_1_OFF_Time);
	 delay_ms(1000);
}
//Function to display Device-2 ON time
void ontime2(void)
{
  cmd_lcd(0x01);
	cmd_lcd(0x80);
	DisplayTimeFromSeconds(Device_2_ON_Time);
	delay_ms(1000);
}
//Function to display Device-2 OFF time
void offtime2(void)
{
   cmd_lcd(0x01);
	 cmd_lcd(0x80);
	 DisplayTimeFromSeconds(Device_2_OFF_Time);
	 delay_ms(1000);
}
