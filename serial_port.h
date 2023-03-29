#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "declarations.h"
#include <pic16f877a.h>
#include <stdint.h>
#include <pic.h>

Buffer buffer;
uint16_t gi_adconv = 0;
uint8_t gi_pisca = 100;

void submit();
int le_ad(void);
uint isRequestReady();
void __interrupt() isr(void);

#endif