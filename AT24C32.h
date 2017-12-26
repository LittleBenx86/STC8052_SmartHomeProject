#ifndef __AT24C32_H_
#define __AT24C32_H_

#include "IOConfig.h"
#include "I2C.h"

extern void recordUsrNameAndPassword(uchar *name, uchar *pwd, uchar times);

extern uchar getUsrNameAndPassword(uchar *name, uchar *pwd);

extern void recordAdminNameAndPassword(uchar *name, uchar *pwd);

extern void getAdminNameAndPassword(uchar *name, uchar *pwd);

#endif
