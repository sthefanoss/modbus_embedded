#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "declarations.h"

void desserializeRequest(const Buffer*, Request*);
void serializeResponse(Buffer*, const Response*);
uint16_t getCrc(uchar, uchar*);

#endif