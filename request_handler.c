#include "request_handler.h"

void f01ReadCoils(Request*, Response*);

void f03ReadHoldingRegisters(Request*, Response*);

void f05WriteSingleCoil(Request*, Response*);

void f06WriteSingleRegister(Request*, Response*);

void f15WriteMultipleCoils(Request*, Response*);

void f16WriteMultipleRegisters(Request*, Response*);

void updateResponse(Request*, Response*);

void updateResponseWithError(Request*, Response*, uchar);

void setCoilValue(uchar, uchar);

uchar getCoilValue(uchar);

void handleRequest(Request* request, Response* response) {
    switch (request->function) {
        case 1:
            f01ReadCoils(request, response);
            break;

        case 3:
            f03ReadHoldingRegisters(request, response);
            break;

        case 5:
            f05WriteSingleCoil(request, response);
            break;

        case 6:
            f06WriteSingleRegister(request, response);
            break;

        case 15:
            f15WriteMultipleCoils(request, response);
            break;

        case 16:
            f16WriteMultipleRegisters(request, response);
            break;

        default:
            updateResponseWithError(request, response, ILLEGAL_FUNCTION_CODE);
            break;
    }
}

void f01ReadCoils(Request* request, Response* response) {
    if (request->dataSize != 4) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_VALUE_CODE);
    }

    uint16_t initialAddress = joinHL(request->data[0], request->data[1]);
    uint16_t coilCount = joinHL(request->data[2], request->data[3]);

    if (initialAddress < COILS_ADDRESS ||
            (initialAddress >= COILS_ADDRESS + COILS_COUNT) ||
            (initialAddress + coilCount > COILS_ADDRESS + COILS_COUNT)) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_ADDRESS_CODE);
    }

    updateResponse(request, response);
    uchar byteCount = (coilCount / 8) + (coilCount % 8 != 0);
    response->dataSize = 1 + byteCount;
    response->data[0] = byteCount;
    for (uint i = 0; i < byteCount; i++)
        response->data[i + 1] = 0;
    uint16_t initialOffset = (uint16_t) ((int) initialAddress - (int) COILS_ADDRESS);
    for (uint16_t i = 0; i < coilCount; i++) {
        uint index = 1 + (i >> 3);
        uint coilValue = getCoilValue(initialOffset + i);
        response->data[index] |= coilValue << (7 - (i % 8));
    }
}

void f03ReadHoldingRegisters(Request* request, Response* response) {
    updateResponse(request, response);
}

void f05WriteSingleCoil(Request* request, Response* response) {
    if (request->dataSize != 4) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_VALUE_CODE);
    }

    uint16_t address = joinHL(request->data[0], request->data[1]);
    uint16_t value = joinHL(request->data[2], request->data[3]);


    if (address < COILS_ADDRESS ||
            (address >= COILS_ADDRESS + COILS_COUNT)) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_ADDRESS_CODE);
    }

    if (value != 0xFF00 && value != 0x0000) {
        return updateResponseWithError(request, response, ILLEGAL_DATA_VALUE_CODE);
    }
    uchar newState = (value == 0xFF00);
    setCoilValue((int) address - (int) COILS_ADDRESS, newState);
    updateResponse(request, response);
}

void f06WriteSingleRegister(Request* request, Response* response) {
    updateResponse(request, response);
}

void f15WriteMultipleCoils(Request* request, Response* response) {
    updateResponse(request, response);
}

void f16WriteMultipleRegisters(Request* request, Response* response) {
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
    response->function = request->function | 0x80;
    response->data[0] = code;
    response->dataSize = 1;
}

void setCoilValue(uchar coilOffset, uchar newState) {
    switch (coilOffset) {
        case 0:
            RB0 = newState; //Precisa usar toggle na placa
            break;
        case 1:
            RB1 = newState;
            break;
        case 2:
            RB2 = newState;
            break;
        case 3:
            RB3 = newState;
            break;
        case 4:
            RB4 = newState;
            break;
        case 5:
            RB5 = newState;
            break;
        case 6:
            RB6 = newState;
            break;
        case 7:
            RB7 = newState;
            break;
        case 8:
            RELAY1_ADDRESS = newState; //precisa usar toggle na placa
            break;
        case 9:
            RELAY2_ADDRESS = newState; //precisa usar toggle na placa
            break;
    }
}

uchar getCoilValue(uchar coilOffset) {
    switch (coilOffset) {
        case 0:
            return RB0;
        case 1:
            return RB1;
        case 2:
            return RB2;
        case 3:
            return RB3;
        case 4:
            return RB4;
        case 5:
            return RB5;
        case 6:
            return RB6;
        case 7:
            return RB7;
        case 8:
            return RELAY1_ADDRESS;
        case 9:
            return RELAY2_ADDRESS;
    }
}