#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "declarations.h"
#include <pic16f877a.h>
#include <stdint.h>
#include <pic.h>

Buffer buffer;

void submit();
uint isRequestReady();
void addPeriodicEvent(void *event(void));
void __interrupt() isr(void);

#endif