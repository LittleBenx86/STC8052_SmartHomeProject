#include "KeyScan.h"

/*******************************************
 * @author Unicorn
 * @date 2017-12-22
 */

/*******************************************************************************
* @function        : the keyboard scan
* @brief		   : get key value
* @param           : none
* @retval          : keyVal
*******************************************************************************/
uchar keyScanGetVal(){
	uchar keyVal = 0, i, temp;
	P1 = 0x0f;
	if(0x0f == P1)
		return keyVal;
	else {
		delayMs(10);//elimination
		for(i = 0; i < 4; i++){
			P1 = _cror_(0x7f, i);//right move a bit to scan the keyboard and monitor the key press situation
			temp = P1;
			temp = temp & 0x0f;
			
			if(0x0f != temp){
				temp = P1;
				if(0 == COL_ONE){
					keyVal = temp;
					break;
				}	
				if(0 == COL_TWO){
					keyVal = temp;
					break;
				}	
				if(0 == COL_THREE){
					keyVal = temp;
					break;
				}	
				if(0 == COL_FOUR){
					keyVal = temp;
					break;
				}	
			}
		}
		
		for(; P1 != 0x0f; P1 = 0x0f);//elimination and waiting for the key release
		return keyVal;
	}
}

/*******************************************************************************
* @function        : key value change to ascii value
* @brief		   : key value change to ascii value
* @param           : keyVal : the return value of keyScanGetVal()
* @retval          : keyVal : after changed value (ascii)
*******************************************************************************/
uchar keyValToChar(uchar keyVal){
	switch(keyVal){
		case 0x00:
			return 0x00;
			break;
		case 0xee:
			keyVal = 'd';//delete 
			break;
		case 0xed:
			keyVal = '#';//quit 
			break;
		case 0xeb:
			keyVal = '0';
			break;
		case 0xe7:
			keyVal = '*';//confirm 
			break;
		case 0xde:
			keyVal = 'c';//custom use to open the door
			break;
		case 0xdd:
			keyVal = '9';
			break;
		case 0xdb:
			keyVal = '8';
			break;
		case 0xd7:
			keyVal = '7';
			break;
		case 0xbe:
			keyVal = 'b';//backstage wake up the LCD12864
			break;
		case 0xbd:
			keyVal = '6';
			break;
		case 0xbb:
			keyVal = '5';
			break;
		case 0xb7:
			keyVal = '4';
			break;
		case 0x7e:
			keyVal = 'a';//admin enter tobackstage 
			break;
		case 0x7d:
			keyVal = '3';
			break;
		case 0x7b:
			keyVal = '2';
			break;
		case 0x77:
			keyVal = '1';
			break;
	}
	
	return keyVal;
}