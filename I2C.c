#include "I2C.h"

/****************************
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */

/*******************************************************************************
* @function         : start 
* @brief	          : starting the I2C bus and notifying all I2C device
* @param            : none
* @retval           : none
*******************************************************************************/
void start(){
	SDA = 1;
	delay5Us();
	SCLK = 1;
	delay5Us();
	SDA = 0;
	delay5Us();
}

/*******************************************************************************
* @function         : stop 
* @brief	        	: stop I2C bus
* @param            : none
* @retval           : none
*******************************************************************************/
void stop(){
	SDA = 0;
	delay5Us();
	SCLK = 1;
	delay5Us();
	SDA = 1;
	delay5Us();	
}

/*******************************************************************************
* @function         : ackResponse
* @brief	          : I2C slaver ack response 
* @param            : none
* @retval           : none
*******************************************************************************/
void ackResponse(){
	uchar i;
	SCLK = 1; delay5Us();
	while((SDA == 1) && (i++ < 250)); 
	SCLK = 0;	delay5Us();	
}

/*******************************************************************************
* @function         : nackResponse
* @brief	          : nack response (master)
* @param            : none
* @retval           : none
*******************************************************************************/
void nackResponse(){
	SCLK = 1;
	delay5Us();
	SDA = 1;
	SCLK = 0;
  delay5Us();
}


/*******************************************************************************
* @function         : initI2C
* @brief	          : initial the I2C bus
* @param            : none
* @retval           : none
*******************************************************************************/
void initI2C(){
	SDA = 1;
	delay5Us();
	SCLK = 1;
	delay5Us();
}

/*******************************************************************************
* @function         : writeByte
* @brief	          : write a byte to I2C SDA line
* @param            : dat : data/command
* @retval           : none
*******************************************************************************/
void writeByte(uchar dat){
	uchar i, temp;
	temp = dat;
	for(i = 0; i < 8; i++){
		temp <<= 1;//repeatly sent 8bit data to CY
		SCLK = 0;//SCLK=0, allow to change the SDA line status
		delay5Us();
		SDA = CY;//sent the data on CY to SDA line
		delay5Us();
		SCLK = 1;//SCLK=1, hold the SDA line status to sent data
		delay5Us();
	}
	//master waits ack response from slaver after 1byte has been send
	SCLK = 0;//allow to change the SDA line status
	delay5Us();
	SDA = 1;//master waits ack response from slaver, SDA = 1 means that it accpet ack response. after while, if SDA = 1 means that it has received ack resposne
	delay5Us();
}

/*******************************************************************************
* @function         : readByte
* @brief	          : read a byte from I2C SDA line
* @param            : none
* @retval           : dat : return data
*******************************************************************************/
uchar readByte(){
	uchar i, j, k;
	SCLK = 0;//allow to change the SDA line status
	delay5Us();
	for(i = 0; i < 8; i++){
		SCLK = 1;// could not change the SDA line status
		delay5Us();//delay for stable
		j = SDA;//read the SDA line status
		k = (k << 1) | j;//get 1bit data
		SCLK = 0;//allow to change the SDA line status and waiting for next 1bit
		delay5Us();
	}
	return k;
}

/*******************************************************************************
* @function         : writeByte2Addr
* @brief	          : write a byte to specified address of I2C device's register.
* @param            : addr : specified address ,dat : data, wcmd : write command
*	                    flag=0 addr range: 0x00~0xff flag=1 addr range : 0x0000~0xffff 
* @retval           : none
*******************************************************************************/
void writeByte2Addr(uchar addr, uint addrL, uchar dat, uchar wcmd, bit flag){
	start();
	writeByte(wcmd);//write command
	if(0 == flag){//addr range : 0x00~0xff
		ackResponse();
		writeByte(addr);//specified address
		} else if(1 == flag){//addr range : 0x0000~0xffff
		ackResponse();
		writeByte(addrL / 256);//specified address's high 8bit
		ackResponse();
		writeByte(addrL % 256);//specified address's low 8bit
	}
	ackResponse();
	writeByte(dat);//write data
	stop();
}

/*******************************************************************************
* @function         : readByteFromAddr
* @brief	          : read a byte from specified address of I2C device's register
* @param            : addr :the specified address,dat :the data papared to write,wcmd :write commamd, rcmd :read command
*	                    flag=0 addr range : 0x00~0xff ,flag=1 addr range : 0x0000~0xffff 
* @retval           : dat : return data
*******************************************************************************/
uchar readByteFromAddr(uchar addr, uint addrL, uchar wcmd, uchar rcmd, bit flag){
	uchar dat;
	start();
	writeByte(wcmd);//write command
	if(0 == flag){//addr range : 0x00~0xff
		ackResponse();
		writeByte(addr);//specified address
		ackResponse();
		} else if(1 == flag){//addr range : 0x0000~0xffff
		ackResponse();
		writeByte(addrL / 256);//specified address's high 8bit
		ackResponse();
		writeByte(addrL % 256);//specified address's low 8bit
		ackResponse();
	}
	start();
	writeByte(rcmd);//read command
	ackResponse();
	dat = readByte();//read data
	ackResponse();
	nackResponse();
	stop();
	return dat;
}

/*******************************************************************************
* @function         : writeArray
* @brief	          : write an array to specified address of I2C device's register
* @param            : addr :the specified address, arr :the array papared to write,wcmd :write commamd, rcmd :read command, num :array length, wcmd :write commamd
*	                    flag=0 addr range: 0x00~0xff flag=1 addr range : 0x0000~0xffff 
* @retval           : none
*******************************************************************************/
void writeArray(uchar *arr, uchar addr, uint addrL, uchar num, uchar wcmd, bit flag){
	uchar i;
	for(i = 0; i < num; i++){
		writeByte2Addr(addr + i, addrL + i, *(arr + i), wcmd, flag);
		delayMs(15);
	}
}

/*******************************************************************************
* @function         : readArray
* @brief	          : read an array from specified address of I2C device's register
* @param            : arr :the return value(Throught the pointer return) addr :device address, num array's length, wcmd :write command, rcmd :read command
*	                    flag=0 addrΪ0x00~0xff flag=1 addrΪ0x0000~0xffff 
* @retval           : arr : return data
*******************************************************************************/
void readArray(uchar *arr, uchar addr, uint addrL, uchar num, uchar wcmd, uchar rcmd, bit flag){
	uchar i;
	for(i = 0; i < num; i++){
		*(arr + i) = readByteFromAddr(addr + i, addrL + i, wcmd, rcmd, flag);
	}
}
