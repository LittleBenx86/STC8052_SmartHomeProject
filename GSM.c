#include "GSM.h"


/*******************************************
 * @author Unicorn
 * @date 2017-12-24
 */

//send enter character
#define SendLR() sendAChar(0x0D);sendAChar(0x0A);

//the messge
code uchar content[] = "AT^SMSN=13250738627 A_thief_enterned_my_house!Quickly_come_back_and_call_the_polic!"; 

/*******************************************************************************
* @function        : sendAChar
* @brief	         : send a char
* @param           : ch : the character
* @retval          : none
*******************************************************************************/
void sendAChar(uchar ch){
	SBUF = ch;
	while(!TI);
	TI = 0;
}

/*******************************************************************************
* @function        : sendArray
* @brief	         : send character array
* @param           : str : the data pepared to write
* @retval          : none
*******************************************************************************/
void sendArray(uchar *str){
	while(*str != '\0'){
		sendAChar(*str);
		str++;
	}
}

/*******************************************************************************
* @function        : GSMInit
* @brief	       	 : init GSM
* @param           : none
* @retval          : none
*******************************************************************************/
void GSMInit(){
    SCON=0x50; //uart works in mode 1
    TH2=0xFF;           
    TL2=0xFD;   //115200 bps, fosc=11.0592MHz 
    RCAP2H=0xFF;   
    RCAP2L=0xFD; //16bit auto relaod mode 
    TCLK=1;   
    RCLK=1;   
    C_T2=0;  //timer mode
    EXEN2=0; //toggle the T2 to create uart's bps
    TR2=1 ; //run the T2
}

/*******************************************************************************
* @function        : sendSMSMode
* @brief	       	 : sent message
* @param           : none
* @retval          : none
*******************************************************************************/
void sendSMSMode(){
	sendArray(content);
	SendLR();
	delayMs(1000);
}
