#include "LCD12864.h"

/****************************
 * @author Unicorn
 * @date 2017-12-20
 */
 
/*******************************************************************************
* @function         : LCD12864_Busy
* @brief	        : check the lcd12864 is busy
* @param            : none
* @retval           : 1: freedom £¬0 : busy
* read status: rs=0, rw=1, e=1, output LCD12864 D0~D7=status
* BF=1:busy, BF=0:freedom
*******************************************************************************/
uchar LCD12864_Busy(void)
{
	uchar i = 0;

	LCD12864_RS = 0;   	//command mode
	LCD12864_RW = 1;	//read mode

	LCD12864_EN = 1;
	delayMs(1);

	while((LCD12864_DATA_PORT & 0x80) == 0x80)	//check value
	{
		i++;
		if(i > 100)
		{
			LCD12864_EN = 0;
			return 0;	   //timeout
		}
	}

	LCD12864_EN = 0;

	return 1;
}

/*******************************************************************************
* @function        : LCD12864_WriteCmd
* @brief	       : LCD12864 write command
* @param           : cmd : lcd12864 instruction
* @retval          : none
* write command:   rs=0, rw=0, e=0, D0~D7=cmd, e=1 create high level to write command
*******************************************************************************/
void LCD12864_WriteCmd(uchar cmd)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		delayMs(1);
		i++;
		if( i>100)
		{
			return;	   //timeout
		}	
	}
	
	LCD12864_RS = 0;     //command mode
	LCD12864_RW = 0;     //write mode
	LCD12864_EN = 0;     //init en

	LCD12864_DATA_PORT = cmd;   //set datas

	LCD12864_EN = 1;		   //write
	delayMs(5);
	LCD12864_EN = 0;    					
}

/*******************************************************************************
* @function        : LCD12864_WriteData
* @brief		   : LCD12864 write datas
* @param           : dat
* @retval          : none
* LCD12864 write datas:   rs=1, rw=0, e=0, D0~D7=dat, e=1 create high level to output datas
*******************************************************************************/
void LCD12864_WriteData(uchar dat)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		delayMs(1);
		i++;
		if( i>100)
		{
			return;	   //timeout
		}	
	}

	LCD12864_RS = 1;     //data mode
	LCD12864_RW = 0;     //write mode
	LCD12864_EN = 0;     //init en

	LCD12864_DATA_PORT = dat;   //set data

	LCD12864_EN = 1;		   //write
	delayMs(5);
	LCD12864_EN = 0;    
}


/*******************************************************************************
* @function        : LCD12864_ReadData
* @brief		   : read datas from lcd12864
* @param           : none
* @retval          : the read values
*******************************************************************************/
/*#ifdef LCD12864_PICTURE//drawing mode

uchar LCD12864_ReadData(void)
{
	uchar i, readValue;

	i = 0;
	while( LCD12864_Busy() == 0)
	{
		delayMs(1);
		i++;
		if( i>100)
		{
			return 0;	   //timeout
		}	
	}

	LCD12864_RS = 1;       //command mode
	LCD12864_RW = 1;
	LCD12864_EN = 0;
	delayMs(1);  //wait

	LCD12864_EN = 1;
	delayMs(1);
	readValue = LCD12864_DATA_PORT;
	LCD12864_EN = 0;

	return readValue;
}

#endif*/

/*******************************************************************************
* @function        : LCD12864_Init
* @brief	       : LCD12864 init
* @param           : none
* @retval          : none
*******************************************************************************/
void LCD12864_Init()
{
	LCD12864_WriteCmd(BASIC_OP_CMD);  //general command
	LCD12864_WriteCmd(ON_SHOW_CLOSE_PTR_CMD);  //show on, but close the cursor show
	LCD12864_WriteCmd(SCREEN_CLR_CMD);  //clear the screen
}

/*******************************************************************************
* @function        : LCD12864_ClearScreen
* @brief		   : under the drawing mode, none one could use 01h to clear the screen
* @param           : none
* @retval          : none
*******************************************************************************/
/*#ifdef LCD12864_PICTURE//drawing mode

void LCD12864_ClearScreen(void)
{
	uchar i,j;

	LCD12864_WriteCmd(0x34);	  //open dthe extend instruction

	for(i=0;i<32;i++)			  //you need to write 32 times for the reason that there are 32 square plaid
	{
		LCD12864_WriteCmd(0x80+i);		  //coordinate y
		LCD12864_WriteCmd(0x80);		  //coordinate x
for(j=0;j<32;j++)		  //x:16bit you need to write 2byte for once
		{						  //the address would auto increase 
			LCD12864_WriteData(0xFF);	  
		}
	}

	LCD12864_WriteCmd(0x36);	 //0x36 open the extend instruction
	LCD12864_WriteCmd(0x30);	 //back to the general instruction
}

#endif*/

/*******************************************************************************
* @function        : LCD12864_SetWindow
* @brief		   : setting the coordinate
* @param           : x, y
* @retval          : none
*******************************************************************************/
void LCD12864_SetWindow(uchar row, uchar col)
{
	uchar pos;//the original coodinate
	
	switch(row){
		case 0:
			row = FIRST_ROW;// first row 80H
			break;
		case 1:
			row = SECOND_ROW; //second row 90H
			break;
		case 2:
			row = THIRD_ROW;//third row 88H
			break;
		case 3:
			row = FOURTH_ROW;//fourth row 98h
			break;
		default:
			break;
	}
	
	pos = row + col;
	LCD12864_WriteCmd(pos);
}

/*******************************************************************************
* @function        : LCD12864_WriteArray
* @brief		   :LCD12864 write an array of unsigned char to show on screen
* @param           : arr -- the unsigned char array that will be show on
* @retval          : none
*******************************************************************************/
void LCD12864_WriteArray(uchar *arr, uchar row, uchar col){
	uchar i = 0;
	LCD12864_SetWindow(row, col);
	while(arr != 0 && *(arr++) != '\0'){
		LCD12864_WriteData(*(arr - 1));
		i++;
		if(i + col >= 16){
			i = col = 0;
			LCD12864_SetWindow(++row, 0);
		}
	}
}
