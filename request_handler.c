#include "request_handler.h"

void handleRequest1(Request*, Response*);
void handleRequest3(Request*, Response*);
void handleRequest5(Request*, Response*);
void handleRequest6(Request*, Response*);
void handleRequest15(Request*, Response*);
void handleRequest16(Request*, Response*);
void updateResponse(Request*, Response*);
void updateResponseWithError(Request*, Response*, uchar);

void handleRequest(Request* request, Response* response) {
    switch (request->function) {
        case 1:
            handleRequest1(request, response);
            break;

        case 3:
            handleRequest3(request, response);
            break;

        case 5:
            handleRequest5(request, response);
            break;

        case 6:
            handleRequest6(request, response);
            break;

        case 15:
            handleRequest15(request, response);
            break;

        case 16:
            handleRequest16(request, response);
            break;

        default:
            updateResponseWithError(request, response, ILLEGAL_FUNCTION_CODE);
            break;
    }
}

void handleRequest1(Request* request, Response* response) {
    updateResponse(request, response);
}

void handleRequest3(Request* request, Response* response) {
    updateResponse(request, response);
}

void handleRequest5(Request* request, Response* response) {
    if (request->dataSize != 4) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_VALUE_CODE);
    }

    uint16_t address = joinHL(request->data[0], request->data[1]);
    uint16_t value = joinHL(request->data[2], request->data[3]);

    if (address != RELAY1_ADDRESS && address != RELAY2_ADDRESS) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_ADDRESS_CODE);
    }

    if (value != 0xFF00 && value != 0x0000) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_VALUE_CODE);
    }

    if (address == RELAY1_ADDRESS) {
        RC1 = (value == 0xFF00);
    } else { // RELAY2
        RC2 = (value == 0xFF00);
    }

    updateResponse(request, response);
}

void handleRequest6(Request* request, Response* response) {
    updateResponse(request, response);
}

void handleRequest15(Request* request, Response* response) {
    updateResponse(request, response);
}

void handleRequest16(Request* request, Response* response) {
    updateResponse(request, response);
}

void updateResponse(Request* request, Response* response) {
    response->address = request->address;
    response->function = request->function;
    response->dataSize = request->dataSize;
    for (uchar i = 0; i < request->dataSize; i++)
        response->data[i] = request->data[i];
}

void updateResponseWithError(Request* request, Response* response, uchar code) {
    response->address = request->address;
    response->function = request->address | 0x80;
    response->data[0] = code;
    response->dataSize = 1;
}
