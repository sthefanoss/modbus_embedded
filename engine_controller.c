#include "engine_controller.h"

uint16_t timeSpent = 0;

void controlEngineRelays(uint16_t dt) {
    if (RELAY1_ADDRESS && RELAY2_ADDRESS) {
        RELAY1_ADDRESS = 0;
        RELAY2_ADDRESS = 1;
        timeSpent = 0;
        return;
    }

    if (RELAY1_ADDRESS) {
        timeSpent += dt;
    }

    if (RELAY1_ADDRESS && timeSpent >= engineStartDuration) {
        RELAY1_ADDRESS = 0;
        RELAY2_ADDRESS = 1;
        timeSpent = 0;
    }
}
