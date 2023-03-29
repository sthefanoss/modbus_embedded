#include "handlers.h"

void handleRequest1(Request* request, Response* response) {
}

void handleRequest3(Request* request, Response* response) {
}

void handleRequest5(Request* request, Response* response) {
    /*
    if (request->dataSize != 4) {
        response->function |= 0x80;
        response->data[0] = 3;
        return;
    }

    uchar address = joinHL(request->data[0], request->data[1]);
    uchar value = joinHL(request->data[2], request->data[3]);

    if (address != 0x08 || address != 0x09) {
        response->function |= 0x80;
        response->data[0] = 2;
        return;
    }

    if (value != 0xFF00 || value != 0x0000) {
        response->function |= 0x80;
        response->data[0] = 0xFFF2;
        return;
    }

    if (address == 0x08) {
        RC1 = value == 0xFF00;
    } else {
        RC2 = value == 0xFF00;
    }
     */
}

void handleRequest6(Request* request, Response* response) {
}

void handleRequest15(Request* request, Response* response) {
}

void handleRequest16(Request* request, Response* response) {
}

void handleInvalidRequest(Request* request, Response* response) {
}