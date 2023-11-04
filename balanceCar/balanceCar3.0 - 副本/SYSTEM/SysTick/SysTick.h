#ifndef _SysTick_H
#define _SysTick_H

#include "sys.h"

void SysTick_Init(u8 SYSCLK);
void tick_delay_ms(u32 nms);
void tick_delay_us(u32 nus);
void tick_delay_xms(u32 nms);


#endif
