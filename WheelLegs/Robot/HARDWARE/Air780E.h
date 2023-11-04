#ifndef __AIR780E_H
#define __AIR780E_H


void Air780E_init(u32 bound);
void Air780ESentByte(uint8_t Byte);
void Air780ESentArr(uint8_t *Array,uint16_t length);
void Air780ESentString(char *String);
int32_t GetAir780EData(void);

#endif
