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
