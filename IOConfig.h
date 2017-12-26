#ifndef __IO_CONFIG_H_
#define __IO_CONFIG_H_

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>

/*****************************
 *redefine the keywords
 */
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

//define the fosc of stc89c52rc.Using to the function of delay
#define OSC_MAIN 11059200UL

/****************************
 * LCD12864 IO definition
 * LCD12864's PSB & RST connected to High level as the parallel input and reset disability
 * read status: rs=0, rw=1, e=1, output LCD12864 D0~D7=status word
 * read data: rs=1, rw=1, e=1
 * write command:   rs=0, rw=0, e=0, D0~D7=cmd, e=1   creating the high level to output command
 * write data:   rs=1, rw=0, e=0, D0~D7=dat, e=1      creating the high level to output datas
 * BF=1:busy, BF=0:freedom and ready to pepare the datas 
 * @author Unicorn
 * @date 2017-12-20
 */
sbit LCD12864_RS  =  P0^6;             //(data command) select the register to input
sbit LCD12864_RW  =  P0^5;             //lcd12864 read/write elect
sbit LCD12864_EN  =  P0^7;             //lcd12864 enable
//LCD12864 data port definition
#define LCD12864_DATA_PORT P2

/****************************
 * LCD12864 general purpose commands
 * @author Unicorn
 * @date 2017-12-20
 */
 //clear the screen
#define SCREEN_CLR_CMD 					0x01//adjusting the counter of ddram address to 00h
//the definition of lcd12864's screen rows
#define FIRST_ROW								0x80
#define SECOND_ROW							0x90
#define THIRD_ROW								0x88
#define FOURTH_ROW							0x98
//RE=0
#define BASIC_OP_CMD 						0x30//8bit parallel data input and general purpose commands mode
#define ON_SHOW_CLOSE_PTR_CMD 				0x0c//screen on show but the cursor closed
#define ON_SHOW_ON_PTR_CMD					0x0e//screen and cursor on show
#define ON_SHOW_ON_PTR2_CMD					0x0f//screen on show and cursor reversed display
//RE=1
#define BASIC_OP2_CMD 						0x34//8bit data and extended instructions
#define CLR_PTR_CMD							0x02//it adjusts counter of ddram to 00h and cursor back to original place
#define NEGATION_FIRST_ROW      			0x04//first row reversed display
#define NEGATION_SECOND_ROW					0x05//second row reversed display
#define NEGATION_THIRD_ROW					0x06//third row reversed display
#define NEGATION_FOURTH_ROW					0x07//fourth row reversed display
//lcd12864 sleep mode SL=0, wake up SL=1
#define SLEEP_CMD								0x08
#define WAKE_UP_CMD							0x0c
//lcd12864 screen cursor
#define PTR_LEFT_MOVE						0x10//when cursor on show, this instruction could let it left move
#define PTR_RIGHT_MOVE					0x14//when cursor on show, this instruction could let it right move
#define DISPLAY_LEFT_MOVE				0x18//when cursor on show and the screen is left moving, this instruction could let it left move also
#define DISPLAY_RIGHT_MOVE			0x1c//when cursor on show and the screen is right moving, this instruction could let it right move also

/****************************
 * membrane keyboard
 * @author Unicorn
 * @date 2017-12-20
 */
#define COL_ONE 		P1^0
#define COL_TWO 		P1^1
#define COL_THREE		P1^2
#define COL_FOUR		P1^3

/****************************
 * IIC IO definition
 * @author Unicorn
 * @date 2017-12-21
 */
sbit SCLK = P0^4;
sbit SDA	= P0^3;

/****************************
 * AT24c32 read/write instructions
 * @author Unicorn
 * @date 2017-12-21
 */
#define AT24C02_WRITE_CMD 0xa0//a2 = a1 = a0 = 0, rw = 0 
#define AT24C02_READ_CMD  0xa1//a2 = a1 = a0 = 0, rw = 1 

/****************************
 * admin name & password store address
 * @author Unicorn
 * @date 2017-12-21
 */
#define ADMIN_NAME 				0x0100 //max 16byte
#define ADMIN_PWD  				0x0120 //must 6byte(all number)

/****************************
 * usr name & password store address
 * @author Unicorn
 * @date 2017-12-21
 */
#define USR_NAME 					0x0200 //max 16byte
#define USR_PWD						0x0210 //must 6byte(all number)
#define USR_ERROR_TIMES		0x0280 //1 Byte

/****************************
 * DS3231 read/write instructions
 * @author Unicorn
 * @date 2017-12-21
 */
#define  DS3231_Write_Address         0xd0//the default address of ds3231.Using to select ds3231 and then write data into ds3231's register
#define  DS3231_Read_Address          0xd1
#define  DS3231_SECOND  							0x00//time register's first address
#define  DS3231_MINUTE				      	0x01
#define  DS3231_HOUR				        	0x02
#define  DS3231_WEEK				        	0x03
#define  DS3231_DAY				          	0x04
#define  DS3231_MONTH					      	0x05
#define  DS3231_YEAR				        	0x06
#define  DS3231_CONTROL						  	0x0e//ds3231 control register
#define  DS3231_STATUS				      	0x0f//ds3231 status register
#define  DS3231_TMPH									0x11//high 8bit of temperature register
#define  DS3231_TMPL									0x12//low 8bit of temperature register

/****************************
 * T0 mod1 16bit Timer
 * @author Unicorn
 * @date 2017-12-21
 */
#define TH0_PREVAL  0x4c	        //high 8bit previous value
#define TL0_PREVAL  0xd0	        //low 8bit previous value

/****************************
 * INT0 IO operation
 * @author Unicorn
 * @date 2017-12-22
 */
#define activeINT0()	{ EX0 = 1; }
#define closeINT0() 	{ EX0 = 0; }

/****************************
 * T0 control
 * @author Unicorn
 * @date 2017-12-22
 */
#define runT0()				{ TR0 = 1; }
#define stopT0() 			{ TR0 = 0; }

/****************************
 * ISD1820 the recording chip
 * @author Unicorn
 * @date 2017-12-22
 */
sbit ISD1820PlayL = P0^2;
#define setBitPlayL() 		{ISD1820PlayL = 1;}
#define resetBitPlayL()		{ISD1820PlayL = 0;}

/****************************
 * buzzer
 * @author Unicorn
 * @date 2017-12-22
 */
sbit buzz = P0^1;
#define setBitBuzz()   { buzz = 1; }
#define resetBitBuzz() { buzz = 0; }

/****************************
 * Infrared body sensor
 * @author Unicorn
 * @date 2017-12-22
 */
sbit infrared = P3^2;//interrupt0.When the door do not be opened by password which means that a thief exist;

/****************************
 * electromagnetic lock IO definition
 * @author Unicorn
 * @date 2017-12-22
 */
sbit lock = P3^7;
#define lockOn() { lock = 1; }
#define unlock() { lock = 0; }

#endif
