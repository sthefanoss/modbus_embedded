#include "temperature_controller.h"
#include "declarations.h"

//1023 - 5V ?? fazer conversao
//0 - 1V - 100C 

void updateTemperature(uint16_t dt) {
    ADCON0 = 0x11;
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO == 1);
    currentTemperature = ((((unsigned int) ADRESH) << 2) | (ADRESL >> 6)) >> 1;
}

void controlTemperature(uint16_t dt) {
    if (currentTemperature > temperatureThreshold) {
        FAN_ADDRESS = 1;
        HEATER_ADDRESS = 0;
    } else {
        FAN_ADDRESS = 0;
        HEATER_ADDRESS = 1;
    }
}