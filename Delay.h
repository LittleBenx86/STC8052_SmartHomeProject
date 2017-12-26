#ifndef __DELAY_H_
#define __DELAY_H_

#include "IOConfig.h"

/****************************
 * @author Unicorn
 * @date 2017-12-20
 */

/****************************
 * adaptive millmeter-level delay
 * @author Unicorn
 * @date 2017-12-20
 */
extern void delayMs(uint xms);

/****************************
 * adaptive osc 5us delay
 * @author Unicorn
 * @date 2017-12-20
 */
extern void delay5Us();

/****************************
 * adaptive osc 100us delay
 * @author Unicorn
 * @date 2017-12-20
 */
extern void delay100Us();

#endif
