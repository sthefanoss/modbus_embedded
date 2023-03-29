#include "handlers.h"

void handleRequest1(Request* request, Response* response) {
}

void handleRequest3(Request* request, Response* response) {
}

void handleRequest5(Request* request, Response* response) {
    if (request->dataSize != 4) {
        response->function |= 0x80;
        response->data[0] = 3;
        response->dataSize = 1;
        return;
    }

    uint16_t address = joinHL(request->data[0], request->data[1]);
    uint16_t value = joinHL(request->data[2], request->data[3]);

    if (address != RELAY1 && address != RELAY2) {
        response->function |= 0x80;
        response->data[0] = 2;
        response->dataSize = 1;
        return;
    }

    if (value != 0xFF00 && value != 0x0000) {
        response->function |= 0x80;
        response->data[0] = 3;
        response->dataSize = 1;
        return;
    }

    if (address == RELAY1) {
        RC1 = (value == 0xFF00);
    } else { // RELAY2
        RC2 = (value == 0xFF00);
    }
}

void handleRequest6(Request* request, Response* response) {
}

void handleRequest15(Request* request, Response* response) {
}

void handleRequest16(Request* request, Response* response) {
}

void handleInvalidFunctionCode(Request* request, Response* response) {
}