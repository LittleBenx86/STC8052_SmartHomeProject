#include "AT24C32.h"

void recordUsrNameAndPassword(uchar *name, uchar *pwd, uchar times){
	writeArray(name, 0, USR_NAME, 17, AT24C02_WRITE_CMD, 1);
	writeArray(pwd, 0, USR_PWD, 7, AT24C02_WRITE_CMD, 1);
	writeByte2Addr(0, USR_ERROR_TIMES, times, AT24C02_WRITE_CMD, 1);
}

uchar getUsrNameAndPassword(uchar *name, uchar *pwd){
	readArray(name, 0, USR_NAME, 16, AT24C02_WRITE_CMD, AT24C02_READ_CMD, 1);
	readArray(pwd, 0, USR_PWD, 6, AT24C02_WRITE_CMD, AT24C02_READ_CMD, 1);
	return readByteFromAddr(0, USR_ERROR_TIMES, AT24C02_WRITE_CMD, AT24C02_READ_CMD, 1);
}

void recordAdminNameAndPassword(uchar *name, uchar *pwd){
	writeArray(name, 0, ADMIN_NAME, 17, AT24C02_WRITE_CMD, 1);
	writeArray(pwd, 0, ADMIN_PWD, 7, AT24C02_WRITE_CMD, 1);
}

void getAdminNameAndPassword(uchar *name, uchar *pwd){
	readArray(name, 0, ADMIN_NAME, 16, AT24C02_WRITE_CMD, AT24C02_READ_CMD, 1);
	readArray(pwd, 0, ADMIN_PWD, 6, AT24C02_WRITE_CMD, AT24C02_READ_CMD, 1);
}