#ifndef __DS3231_H_
#define __DS3231_H_

#include "IOConfig.h"
#include "Delay.h"
#include "I2C.h"

/*******************************************
 * @author Unicorn
 * @date 2017-12-22
 */


/****************************
 * ds3231 modify a byte
 * @author Unicorn
 * @date 2017-12-22
 */
extern void DS3231ModifyByte(uchar addr, uchar val);

/****************************
 * ds3231 read a byte
 * @author Unicorn
 * @date 2017-12-22
 */
extern uchar DS3231ReadByte(uchar addr);

/****************************
 * ds3231 read a byte
 * @author Unicorn
 * @date 2017-12-22
 */
extern void DS3231ReadTimes(uint *ptr);

/****************************
 * ds3231 read a byte about its working status
 * @author Unicorn
 * @date 2017-12-22
 */
extern uchar DS3231ReadAByteOfStatus(uchar addr);

/****************************
 * set time's datas to ds3231
 * @author Unicorn
 * @date 2017-12-22
 */
extern void DS3231SetTimes(uint *ptr);

/****************************
 * ds3231 initial
 * @author Unicorn
 * @date 2017-12-22
 */
extern void DS3231Init();

/****************************
 * ds3231 read a byte about temperature
 * @author Unicorn
 * @date 2017-12-22
 */
extern void DS3231ReadTmp(uint *ptr);

/****************************
 * auto-adjust week register value
 * @author Unicorn
 * @date 2017-12-22
 */
extern void autoWeek(uchar y, uchar m, uchar d);


#endif