#ifndef HANDLERS_H
#define HANDLERS_H

#include "declarations.h"
#include <pic16f877a.h>

void handleRequest1(Request*, Response*);
void handleRequest3(Request*, Response*);
void handleRequest5(Request*, Response*);
void handleRequest6(Request*, Response*);
void handleRequest15(Request*, Response*);
void handleRequest16(Request*, Response*);
void handleInvalidFunctionCode(Request*, Response*);

#endif