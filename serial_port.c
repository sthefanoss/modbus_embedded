#include "serial_port.h"

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

int le_ad(void) {
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    return joinHL(ADRESH, ADRESL);
}

uint isRequestReady(void) {
    return buffer.size >= 8;
}

void __interrupt() isr(void) {

    if (TMR1IE && TMR1IF)//timer 1?
    {
        TMR1IF = 0;
        TMR1 = 55536;

        if (gi_pisca) {
            gi_pisca--;
        } else {
            gi_pisca = 100; //a cada 1s
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