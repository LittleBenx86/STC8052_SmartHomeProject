#ifndef __I2C_H_
#define __I2C_H_

#include "IOConfig.h"
#include "Delay.h"

/****************************
 * start I2C bus
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
extern void start();

/****************************
 * stop I2C bus
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
extern void stop();

/****************************
 * I2C slaver ack response
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
void ackResponse();

/****************************
 * nack response (master)
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
extern void nackResponse();


/****************************
 * I2C initial
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
extern void initI2C();

/****************************
 * write a byte to I2C SDA line
 * @param dat :the data papared to write
 * @author Unicorn
 * @date 2017-12-21
 */
extern void writeByte(uchar dat);

/****************************
 * read a byte from I2C SDA line
 * @param none
 * @author Unicorn
 * @date 2017-12-21
 */
extern uchar readByte();

/****************************
 * write a byte to specified address of I2C device's register
 * @param addr :the specified address,dat :the data papared to write,wcmd :write commamd
 * @author Unicorn
 * @date 2017-12-21
 */
extern void writeByte2Addr(uchar addr, uint addrL, uchar dat, uchar wcmd, bit flag);

/****************************
 * read a byte from specified address of I2C device's register
 * @param addr :the specified address,dat :the data papared to write,wcmd :write commamd, rcmd :read command
 * @author Unicorn
 * @date 2017-12-21
 */
extern uchar readByteFromAddr(uchar addr, uint addrL, uchar wcmd, uchar rcmd, bit flag);

/****************************
 * write an array to specified address of I2C device's register
 * @param addr :the specified address, arr :the array papared to write,wcmd :write commamd, rcmd :read command, num :array length, wcmd :write commamd
 * @author Unicorn
 * @date 2017-12-21
 */
extern void writeArray(uchar *arr, uchar addr, uint addrL, uchar num, uchar wcmd, bit flag);

/****************************
 * read an array from specified address of I2C device's register
 * @param arr :the return value(Throught the pointer return) addr :device address, num array's length, wcmd :write command, rcmd :read command
 * @author Unicorn
 * @date 2017-12-21
 */
extern void readArray(uchar *arr, uchar addr, uint addrL, uchar num, uchar wcmd, uchar rcmd, bit flag);


#endif