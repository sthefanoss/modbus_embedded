#include "serial_port.h"
#define INTERRUPT_COUNT 100

uint16_t interruptCounter = INTERRUPT_COUNT;
uint8_t eventsSize = 0;
void (*events[8])(uint16_t);

/*----------------------------------------
sub_tx
Descrição: envia o gc_buffer para a saída serial
Entrada: c_max, indica o nº de dados a serem
 enviados
----------------------------------------*/
void submit() {
    //espera o buffer ser esvaziado
    while (!TXSTAbits.TRMT);


    for (uchar i = 0; i < buffer.size; i++) {
        while (!TRMT);
        TXREG = buffer.data[i];
    }
    buffer.size = 0;
    //espera o buffer ser esvaziado
    while (!TXSTAbits.TRMT);
}

uint isRequestReady(void) {
    return buffer.size >= 8;
}

void addPeriodicEvent(void *event(uint16_t)) {
    if (eventsSize >= sizeof (events)) {
        return;
    }
    events[eventsSize] = event;
    eventsSize++;
}

void __interrupt() isr(void) {
    if (TMR1IE && TMR1IF)//timer 1?
    {
        TMR1IF = 0;
        TMR1 = 55536;

        if (interruptCounter) {
            interruptCounter--;

        } else {
            interruptCounter = INTERRUPT_COUNT; //a cada 1s
            for (uint i = 0; i < eventsSize; i++)
                events[i](INTERRUPT_COUNT);
        }
    }
    if (RCIF && RCIE) {
        if (OERR || FERR) {
            CREN = 0;
            __delay_us(10);
            CREN = 1;
        }
        if (buffer.size < sizeof (buffer.data))//se houver espaço coloca no buffer
        {
            buffer.data[buffer.size] = RCREG;
            buffer.size++;
        }
    }
}