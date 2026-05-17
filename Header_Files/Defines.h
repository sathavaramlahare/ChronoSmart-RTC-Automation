//KEYPAD FUNCTION DECLARATIONS 
void KPM_INIT(void);
int colscan(void);
int rowcheck(void);
int colcheck(void);
int keyscan(void);

//RTC GLOBAL VARIABLES
extern int hour,min,sec,date,month,year,current_time;
extern unsigned int day;
//extern char Day[7][4]={"sun","mon","tue","wed","thu","fri","sat"};

//RTC FUNCTION DECLARATIONS
void RTC_INIT(void);
void LCD_INIT(void);
void SetRTCTime(int,int,int);
void SetRTCDate(int,int,int);
void SetRTCDay(unsigned int);

void DisplayRTCDay(unsigned int*);
void GetRTCTime(int*,int*,int*);
void GetRTCDate(int*,int*,int*);
void GetRTCDay(unsigned int *);
void DisplayRTCTime(int,int,int);
void DisplayRTCDate(int,int,int);

// DEVICE TIME VARIABLES
void controldevices(void);
extern int on_hour1,on_min1,on_sec1;
extern int off_hour1,off_min1,off_sec1;

extern int on_hour2,on_min2,on_sec2;
extern int off_hour2,off_min2,off_sec2;

extern int Device_1_ON_Time;
extern int Device_1_OFF_Time;
extern int Device_2_ON_Time;
extern int Device_2_OFF_Time;

//SYSTEM STATUS VARIABLE
extern int system_lock;

//ADC FUNCTION DECLARATIONS 
void INIT_ADC(void);
void Read_ADC(char chno,int *Adcval,float *eAR);

//MENU FUNCTION DECLARATIONS
void Change_password(void);
int Menu(void);
int check_password(void);
void Settings_Menu(void);
void Device_Menu(void);
void time_edit(void);
void date_edit(void);
void day_edit(void);
void Device1_edit(void);
void Device2_edit(void);
void view(void);
void Device1(void);
void Device2(void);
void Date(void);
void Time(void);
void rtcday(void);
void ontime1(void);
void offtime1(void);
void ontime2(void);
void offtime2(void);	
void temp_edit(void);

//DELAY FUNCTION DECLARATIONS
void delay_us(unsigned int dly);
void delay_ms(unsigned int dly);
void delay_s(unsigned int dly);

//LCD FUNCTION DECLARATIONS
void write_lcd(int data);
void cmd_lcd(int data);
void char_lcd(int data);
void LCD_INIT(void);
void str_lcd(char *str);
void int_LCD(int n);
void float_lcd(float f,int nDP);
void neg_lcd(int n);
