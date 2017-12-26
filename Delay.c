#include "Delay.h"

/****************************
 * @author Unicorn
 * @date 2017-12-20
 */

/*******************************************************************************
* @function        : delay
* @brief		   : adaptive millmeter-level delay
* @param           : xms 
* @retval          : none
*******************************************************************************/
void delayMs(uint xms){
	uint i;
	do{
		i = OSC_MAIN / 9600;
		while(--i);
	}while(--xms);
}

/*******************************************************************************
* @function        : delay
* @brief		   : adaptive osc 5us delay
* @param           : none
* @retval          : none
*******************************************************************************/
void delay5Us(){
	#if OSC_MAIN == 11059200UL
		_nop_();
	#elif OSC_MAIN == 12000000UL
		_nop_();
	#elif OSC_MAIN == 22118400UL
		_nop_(); _nop_(); _nop_();
	#endif
}

/*******************************************************************************
* @function        : delay
* @brief		   : adaptive osc 100us delay
* @param           : none
* @retval          : none
*******************************************************************************/
void delay100Us(){
	uchar i, j;
	#if OSC_MAIN == 11059200UL
		_nop_(); _nop_();
		i = 2;
	  j = 15;
	#elif OSC_MAIN == 12000000UL
		i = 2;
		j = 39;
	#elif OSC_MAIN == 22118400UL
		i = 3;
		j = 82;
	#endif
	do{
		while(--j);
	}while(--i);
}

