#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "declarations.h"
#include <pic16f877a.h>
#include <stdint.h>
#include <pic.h>

Buffer buffer;

void submit();
uint isRequestReady();
void addPeriodicEvent(void *event(uint16_t));
void __interrupt() isr(void);

#endif