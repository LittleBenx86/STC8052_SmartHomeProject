#ifndef __GSM_H_
#define __GSM_H_

#include "IOConfig.h"
#include "Delay.h"

/*******************************************
 * @author Unicorn
 * @date 2017-12-24
 */

/****************************
 * using the uart to send a character
 * @author Unicorn
 * @date 2017-12-24
 */
extern void sendAChar(uchar ch);

/****************************
 * using the uart to send a string(charater array)
 * @author Unicorn
 * @date 2017-12-24
 */
extern void sendArray(uchar *str);

/****************************
 * gsm(comway wg8010) initial
 * @author Unicorn
 * @date 2017-12-24
 */
extern void GSMInit();

/****************************
 * send the message when the thief enter the house without throught password
 * @author Unicorn
 * @date 2017-12-24
 */
extern void sendSMSMode();

#endif
