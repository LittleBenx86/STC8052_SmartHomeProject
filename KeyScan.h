#ifndef __KEY_SCAN_H_
#define __KEY_SCAN_H_

#include "IOConfig.h"
#include "Delay.h"

/****************************
 * @author Unicorn
 * @date 2017-12-20
 */

/****************************
 * the keyboard scan
 * @author Unicorn
 * @date 2017-12-20
 */
extern uchar keyScanGetVal();

/****************************
 * key value change to ascii value
 * @author Unicorn
 * @date 2017-12-20
 */
extern uchar keyValToChar(uchar keyVal);

#endif
