#include<lpc21xx.h>
#include"lcd.h"
#include"delay.h"
//LCD control pins
#define RS 5
#define RW 4
#define EN 6
//LCD Data pins starting position
#define DATA 8
int data;
char str[100];

//Writes command/data to LCD by generating enable pulse
void write_lcd(int data)
{
	//RW->0 for write operation
	IOCLR0=1<<RW;
	//clear display and update command
	IOPIN0=(IOPIN0&~(0XFF<<DATA))|(data<<DATA);
  //enable should be high to low for write operation
	IOSET0=1<<EN;
	delay_us(10);
	IOCLR0=1<<EN;
	delay_ms(2);
}

//Sends command to LCD command register
void cmd_lcd(int data)
{
	//rs-> 0 for setting command register
	IOCLR0=1<<RS;
  //send command
	write_lcd(data);
}

//sends single character data to LCD
void char_lcd(int data)
{
	//RS->1 for data register
	IOSET0=1<<RS;
	//send character
	write_lcd(data);
}

//Initializes LCD in 8-bit mode and configures display settings
void LCD_INIT()
{
  //Configure LCD control pins as output
	IODIR0|=1<<RS;
	IODIR0|=1<<RW;
	IODIR0|=1<<EN;
  //configure LCD data pins as output
	IODIR0|=0XFF<<DATA;
  //Initial power ON delay
	delay_ms(15);
	//LCD initialization sequence
	cmd_lcd(0X30);
	delay_ms(5);
	cmd_lcd(0X30);
	delay_ms(10);
	cmd_lcd(0x30);
	//display settings
	cmd_lcd(0x38);//8 bit mode 2 lines
	cmd_lcd(0x0F);//display ON,cursor ON,blink ON
	cmd_lcd(0x01);//clear lcd
	cmd_lcd(0x06);//shift cursor,shift display
	cmd_lcd(0x0c);//Display ON,Cursor OFF
}
//Displays the string on LCD
void str_lcd(char *str)
{
	while(*str)
	{
		char_lcd(*str++);
	}
}
//Displays integer number on LCD
void int_LCD(int n)
{
  int a[10],i=0;
  if(n==0)
  {
    char_lcd('0');
  }
  else
  {
  while(n)
  {
    a[i++]=(n%10)+48;
    n=n/10;
   }
   for(--i;i>=0;i--)
   {
     char_lcd(a[i]);
   }
   }
}
//Displays floating point number on LCD
void float_lcd(float f,int nDP)
{
  int i,n;
  if(f<0)
  {
    char_lcd('-');
  }
  else
  {
    n=f;
    int_LCD(n);
    char_lcd('.');
   }
   for(i=0;i<=nDP;i++)
   {
     f=(f-n)*10;
	n=f;
	char_lcd(n+48);
   }
}
//Displays negative number on LCD
void neg_lcd(int n)
{
  if(n<0)
  {
    char_lcd('-');
    n=-n;
    int_LCD(n);
   }
}
