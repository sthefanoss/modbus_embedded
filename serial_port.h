#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "declarations.h"
#include <pic16f877a.h>
#include <stdint.h>
#include <pic.h>

uchar gc_rx[20], gc_c = 0;
uint16_t gi_adconv = 0;
uint8_t gi_pisca = 100;
uchar c_texto[16], c_i;
unsigned int i_crc, i_crc2;

void sub_tx(uchar, uchar *);
uint f_crc(uchar, uchar *);
int le_ad(void);
void __interrupt() isr(void);

#endif