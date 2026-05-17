#include "defines.h"
#include "menu.h"
#include "lcd.h"
#include "keypad_defines.h"
//Displays RTC viewing menu.Allows user to view Date, Time, and Day.
void RTC(void)
{
	char key;
	while(1)
	{
	  // Display RTC menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.Date");
		char_lcd(30);
		str_lcd("2.Time");
		cmd_lcd(0xc0);
		str_lcd("3.Day");
		char_lcd(30);
		str_lcd("4.exit");
		key=keyscan();
		if(key=='1'||key=='2'||key=='3'||key=='4')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		{
			case '1': Date();
			          break;
			case '2':Time();
			         break;
			case '3': rtcday();
               break;
			case '4':return;
		 }
		 }
}
}
//Displays device viewing menu.Allows user to select Device1 or Device2.
void Device(void)
{
	char key;
	while(1)
	{
		// Display device menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.Device1");
		cmd_lcd(0xc0);
		str_lcd("2.Device2");
		char_lcd(30);
		str_lcd("3.Back");
		key=keyscan();
		if(key=='1'||key=='2'||key=='3')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		{
			case '1': Device1();
			          break;
			case '2':Device2();
			         break;
			case '3': return;
    }
    }
  }
}
//Displays Device1 ON/OFF timing menu
void Device1()
{
  char key;
	while(1)
	{
		// Display Device1 menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.Ontime");
		cmd_lcd(0xc0);
		str_lcd("2.offtime");
		char_lcd(30);
		str_lcd("3.Back");
		key=keyscan();
		// Validate key
		if(key=='1'||key=='2'||key=='3')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		  {
		   // Display Device1 ON time
			case '1': ontime1();
			          break;
			// Display Device1 OFF time
			case '2':offtime1();
			         break;
			case '3': return;
    }
    }
  }
}
// Displays Device2 ON/OFF timing menu
void Device2()
{
  char key;
	while(1)
	{
		// Display Device2 menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.Ontime");
		cmd_lcd(0xc0);
		str_lcd("2.offtime");
		char_lcd(30);
		str_lcd("3.Back");
		key=keyscan();
		if(key=='1'||key=='2'||key=='3')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		 {
			 // Display Device2 ON time
			case '1': ontime2();
			          break;
			 // Display Device2 OFF time
			case '2':offtime2();
			         break;
			case '3': return;
     }
    }
  }
}
   
// Main menu for settings, device control,viewing data, and exit option 
int Menu(void)
{
	char key;
	while(1)
	{
		// Display main menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.set 2.Device");
		
		cmd_lcd(0xC0);
		str_lcd("3.view 4.Return");
		
		key=keyscan();
		if(key=='1'||key=='2'||key=='3'||key=='4')
		{
			//switch press condition
			while(colscan());
		  switch(key)
			{
				// Open settings menu
				case '1':Settings_Menu();
				         break;
				// Open device settings menu
				case '2':Device_Menu();
				         break;
				// Open view menu
				case '3':view();
				         break;
				case '4': return 0;
			}
		}
	}
}
//Displays settings menu for password,time, date, and day editing
void Settings_Menu(void)
{
	char key;
	while(1)
	{
		// Display settings menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.pass");
		char_lcd(30);
		str_lcd("2.Time");
		cmd_lcd(0xc0);
		str_lcd("3.Dat");
		char_lcd(30);
		str_lcd("4.Day");
		char_lcd(30);
		str_lcd("5.exit");
		key=keyscan();
		if(key=='1' || key== '2' ||key== '3'||key=='4'||key=='5')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		{
			// Change password
			case '1': Change_password();
			           break;
			// Edit RTC time
			case '2': time_edit();	
			          break;
			// Edit RTC date
			case '3': date_edit();
			          break;
			// Edit RTC day
			case '4': day_edit();
			          break;
			// Exit settings menu
			case '5': return;
		}		
	 }
  }
}	
//Displays device configuration menu for editing ON/OFF timings and temperature
void Device_Menu()
{
	char key;
	while(1)
	{
	  // Display device settings menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("5.Dev1");
		char_lcd(30);
		str_lcd("6.Dev2");
		cmd_lcd(0xc0);
		str_lcd("7.Temp");
		char_lcd(30);
		str_lcd("8.Exit");
		key=keyscan();
		if(key=='5'||key=='6'||key=='7'||key=='8')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		{
			// Edit Device1 timings
			case '5': Device1_edit();
			          break;
			// Edit Device2 timings
			case '6':Device2_edit();
			         break;
			// Edit temperature threshold
			case '7': temp_edit();
			          break;
			// Exit device menu
			case '8': return;
		}		
	 }
  }
}
//Menu for viewing the changed parameters
void view()
{
	char key;
	while(1)
	{
		// Display view menu
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		str_lcd("1.RTC");
		char_lcd(30);
		str_lcd("2.Device");
		cmd_lcd(0xc0);
		str_lcd("3.Return");
		key=keyscan();
		if(key=='1'||key=='2'||key=='3')
		{
			//switch press condition
			while(colscan());
		  switch(key)
		 {
			// Open RTC view menu
			case '1': RTC();
			          break;
			// Open Device view menu
			case '2':Device();
			         break;
			// Return to previous menu
			case '3': return;
		 }
	}
}
}
