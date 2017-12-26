#ifndef __LCD_12864_H_
#define __LCD_12864_H_

/*
DDRAM£¨data show RAM£©address 0~63:
80H¡¢81H¡¢82H¡¢83H¡¢84H¡¢85H¡¢86H¡¢87H¡¢	88H¡¢89H¡¢8AH¡¢8BH¡¢8CH¡¢8DH¡¢8EH¡¢8FH
90H¡¢91H¡¢92H¡¢93H¡¢94H¡¢95H¡¢96H¡¢97H¡¢	98H¡¢99H¡¢9AH¡¢9BH¡¢9CH¡¢9DH¡¢9EH¡¢9FH
A0H¡¢A1H¡¢A2H¡¢A3H¡¢A4H¡¢A5H¡¢A6H¡¢A7H¡¢	A8H¡¢A9H¡¢AAH¡¢ABH¡¢ACH¡¢ADH¡¢AEH¡¢AFH
B0H¡¢B1H¡¢B2H¡¢B3H¡¢B4H¡¢B5H¡¢B6H¡¢B7H¡¢	B8H¡¢B9H¡¢BAH¡¢BBH¡¢BCH¡¢BDH¡¢BEH¡¢BFH

the relationship between screen and coordinate
first row:80H¡¢81H¡¢82H¡¢83H¡¢84H¡¢85H¡¢86H¡¢87H
second row:90H¡¢91H¡¢92H¡¢93H¡¢94H¡¢95H¡¢96H¡¢97H 
third row:88H¡¢89H¡¢8AH¡¢8BH¡¢8CH¡¢8DH¡¢8EH¡¢8FH
fourth row:98H¡¢99H¡¢9AH¡¢9BH¡¢9CH¡¢9DH¡¢9EH¡¢9FH
*/

#include "IOConfig.h"
#include "Delay.h"

/****************************
 * @author Unicorn
 * @date 2017-12-20
 */

/****************************
 * check the lcd12864 is busy
 * @author Unicorn
 * @date 2017-12-20
 */
extern uchar LCD12864_Busy(void);

/****************************
 * LCD12864 write command
 * @param cmd LCD12864 instruction
 * @author Unicorn
 * @date 2017-12-20
 */
extern void LCD12864_WriteCmd(uchar cmd);

/****************************
 * LCD12864 write datas
 * @param dat the datas papared to write
 * @author Unicorn
 * @date 2017-12-20
 */
extern void LCD12864_WriteData(uchar dat);

/****************************
 * LCD12864 init
 * @author Unicorn
 * @date 2017-12-20
 */
extern void LCD12864_Init(void);

/****************************
 * LCD12864 clear screen
 * @author Unicorn
 * @date 2017-12-20
 */
extern void LCD12864_ClearScreen(void);

/****************************
 * LCD12864 setting coordinate
 * @author Unicorn
 * @date 2017-12-20
 */
extern void LCD12864_SetWindow(uchar x, uchar y);

/****************************
 * LCD12864 write an array of unsigned char to show on screen
 * @author Unicorn
 * @date 2017-12-22
 */
extern void LCD12864_WriteArray(uchar *arr, uchar row, uchar col);

#endif
