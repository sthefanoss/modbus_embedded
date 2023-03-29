#include "serialization.h"

void desserializeRequest(const Buffer* buffer, Request* request) {
    uchar* data = buffer->data;
    uchar size = buffer->size;
    uint16_t crc = joinHL(data[size - 1], data[size - 2]);
    uint16_t evaluatedCrc = getCrc(buffer->size - 2, buffer->data);

    request->address = data[0];
    request->function = data[1];
    request->dataSize = size - 4;
    request->crcValid = crc == evaluatedCrc;
    for (uchar i = 0; i < request->dataSize; i++)
        request->data[i] = buffer->data[i + 2];
}

void serializeResponse(Buffer* buffer, const Response* response) {
    buffer->size = response->dataSize + 4;
    buffer->data[0] = response->address;
    buffer->data[1] = response->function;
    for (uchar i = 0; i < response->dataSize; i++)
        buffer->data[i + 2] = response->data[i];
    uint16_t crc = getCrc(response->dataSize + 2, response->data - 2);
    buffer->data[response->dataSize + 2] = crc;
    buffer->data[response->dataSize + 3] = crc >> 8;
}

void updateResponse(const Request* request, Response* response) {
    response->address = request->address;
    response->function = request->function;
    response->dataSize = request->dataSize;
    for (uchar i = 0; i < request->dataSize; i++)
        response->data[i] = request->data[i];
}

uint16_t getCrc(uchar c_max, uchar *c_buffer) {
    uint16_t i_CRC = 0xffff;
    for (uchar c_i = 0; c_i < c_max; c_i++) {
        i_CRC = i_CRC^c_buffer[c_i];
        for (uchar c_j = 0; c_j < 8; c_j++) {
            if (!(i_CRC & 1))
                i_CRC = i_CRC >> 1; //antes eram 2 rotacoes. Tenho q verificar isto
            else {
                i_CRC = i_CRC >> 1;
                i_CRC = i_CRC^0xa001;
            }
        }
    }
    return i_CRC;
}