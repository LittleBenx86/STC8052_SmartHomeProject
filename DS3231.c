#include "DS3231.h"

/*******************************************
 * @author Unicorn
 * @date 2017-12-22
 */

code unsigned char WeekTab[] = {//the week table of leap year & month
  (3 << 5) + 31,//January
  (6 << 5) + 29,//February
  (0 << 5) + 31,//March
  (3 << 5) + 30,//April
  (5 << 5) + 31,//May
  (1 << 5) + 30,//June
  (3 << 5) + 31,//July
  (6 << 5) + 31,//August
  (1 << 5) + 30,//Setember
  (4 << 5) + 31,//October
  (0 << 5) + 30,//November
  (2 << 5) + 31 //December
};


/*******************************************************************************
* @function        : ds3231 modify a byte
* @brief	       : modify a byte to ds3231's specified address register
* @param           : addr : the specified address, val : the new byte value
* @retval          : none
*******************************************************************************/
void DS3231ModifyByte(uchar addr, uchar val){
	writeByte2Addr(addr, 0, (val / 10 * 16 + val % 10), DS3231_Write_Address, 0);
}

/*******************************************************************************
* @function        : ds3231 read a byte
* @brief	       : master through the I2C read a byte from ds3231's specified address register
* @param           : addr : the specified address
* @retval          : the read byte
*******************************************************************************/
uchar DS3231ReadByte(uchar addr){
	return readByteFromAddr(addr, 0, DS3231_Write_Address, DS3231_Read_Address, 0);
}

/*******************************************************************************
* @function        : ds3231 read a byte
* @brief	       : master through the I2C read a byte from ds3231's specified address register
* @param           : addr : the specified address
* @retval          : the read byte
*******************************************************************************/
void DS3231ReadTimes(uint *ptr){
	uchar temp, i;
	DS3231ModifyByte(DS3231_STATUS, 0x00);//disable the alarm clock interruption

	for(i = 0; i < 7; i++){
		temp = DS3231ReadByte(DS3231_SECOND + i);
		*ptr++ = (temp / 16 * 10 + temp % 16);//hex to dec(decimalism)
	}
}

/*******************************************************************************
* @function        : ds3231 read a byte about temperature
* @brief	       : master through the I2C read a byte about temperature from ds3231's specified address register of temperature
* @param           : ptr : the temperature array
* @retval          : temperature value
*******************************************************************************/
void DS3231ReadTmp(uint *ptr){
	uchar temp, i;
	DS3231ModifyByte(DS3231_STATUS, 0x00);//disable the alarm clock interruption

	DS3231ModifyByte(DS3231_CONTROL, 0x20);//conver the temperature datas in 0x11 & 0x12 register

	for(i = 0; i < 2; i++){
		temp = DS3231ReadByte(DS3231_TMPH + i);
		if(i == 0)
			*ptr++ = temp;
		else if(i == 1 && (ptr[0] & 0x80) == 0)
			*ptr = (temp >> 6) * 25;
		else
			*ptr = temp;
	}
}

/*******************************************************************************
* @function        : ds3231 read a byte about its working status
* @brief	       : master through the I2C read a byte from ds3231's specified address register about ds3231's working status
* @param           : addr : the specified address
* @retval          : the byte of working status
*******************************************************************************/
uchar DS3231ReadAByteOfStatus(uchar addr){
	return DS3231ReadByte(addr);
}

/*******************************************************************************
* @function        : set time's datas to ds3231
* @brief	       : master through the I2C to write some datas about time to ds3231's specified address register od time
* @param           : ptr : the pointer of time's array
* @retval          : none
*******************************************************************************/
void DS3231SetTimes(uint *ptr){
	uchar i;
	for(i = 0; i < 7; i++){
		DS3231ModifyByte(DS3231_SECOND + i, *(ptr + i));
	}
	autoWeek(*(ptr + 6), *(ptr + 5), *(ptr + 4));
}

/*******************************************************************************
* @function        : ds3231 initial
* @brief	       : init the ds3231
* @param           : none
* @retval          : none
*******************************************************************************/
void DS3231Init(){
	DS3231ModifyByte(DS3231_HOUR, 0x00);//setting use 24-hour format(0-23)
	DS3231ModifyByte(DS3231_CONTROL, 0x04);//control register initial,stop to output square wave, disable the alarm clock
	DS3231ModifyByte(DS3231_STATUS, 0x00);//status register initial,stop to output square wave, disable the alarm clock
}

/*******************************************************************************
* @function        : auto-adjust week register value
* @brief	       : master through the I2C auto-modify ds3231's specified address register of weekday
* @param           : y: year's value, m : month's value, d : day's value
* @retval          : the read byte
*******************************************************************************/
void autoWeek(uchar y, uchar m, uchar d){
	uchar week, day;
	day = WeekTab[m - 1];
	week = day >> 5;
	day &= 0x1f;
	if((m < 3) && (y & 0x03)){//nonleap year
		if(2 == m) day--;
		week++;
	}
	y = y + (y >> 2);
	week = (week + y + d + 2) % 7 + 1;
	DS3231ModifyByte(DS3231_WEEK, week);
}


