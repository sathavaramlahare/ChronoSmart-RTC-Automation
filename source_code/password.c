#include"delay.h"
#include"lcd.h"
#include"keypad.h"
#include<string.h>
#include"menu.h"
char password[5]="2222";
// Array to store entered password1
char input[5];
// Counter for wrong password attempts
int cnt=0;
/*Verifies user-entered password.
  Allows maximum 3 wrong attempts.
  If password matches, opens menu.
  If password fails 3 times, system locks temporarily.*/
int check_password(void)
{
   int i=0,k;
   char key;
	 // Allow maximum 3 attempts
   while(cnt<3)
	 {
		   i=0;
		   // Clear LCD and display password prompt
		   cmd_lcd(0x01);
		   cmd_lcd(0x80);
		   str_lcd("Enter the pass:");
		   cmd_lcd(0xc0);
		 	// Read password input
		   while(1)
		  {
				 // Scan keypad key
			   key=keyscan();
			   if(key=='\0')
				    continue;
				 // Backspace operation
				if(key=='#')
			{
				if(i>0)
				{
					i--;
					cmd_lcd(0x10);
					char_lcd(' ');
					cmd_lcd(0x10);
				}
			}
			// Accept only numeric digits
			else if(key>='0' && key<='9')
			{
				// Accept maximum 4 digits
				if(i<4)
				{
			     input[i]=key;
			     char_lcd(key);
			     delay_ms(50);
					 // password hiding
			     cmd_lcd(0x10);
			     char_lcd('*');
			     i++;
				}
			 }
			// '*' key used as ENTER key
			else if(key == '*')   
      {
			  if(i==4)
			  {
           input[i] = '\0';
           break;
			  }				
     }
			// Wait until key release
			while(colscan());
	  }
		    input[i]='\0';
		    cmd_lcd(0x01);
		    delay_ms(100);
		    // Compare entered password with stored password
		    if(strcmp(input,password)==0)
		    {
            // Open menu continuously
			      while(Menu());
					      return 1;
		    }
		    else
		    {      
            // Wrong password message					
			      str_lcd("not matched");
			      delay_ms(1000);
					  // Increment wrong attempt count
			      cnt++;
				    return 0;
		    }
		 }
	      // Lock system after 3 wrong attempts
			  for(k=30;k>0;k--)
			  {
				    cmd_lcd(0x80);
			      str_lcd("Device LOCKED");
			      cmd_lcd(0xc0);
				    str_lcd("Wait:");
				    int_LCD(k);
				    str_lcd("sec");
				    delay_ms(1000);
					  // Clear remaining digits
				    str_lcd("  ");
			   }
				cmd_lcd(0x01);
				// Reset attempt counter
				cnt=0;
				return 0;
}
