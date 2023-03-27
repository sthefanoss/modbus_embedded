#include "serial_port.h"

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
        if (gc_c<sizeof (gc_rx))//se houver espaço coloca no buffer
        {
            gc_rx[gc_c] = RCREG;
            gc_c++;
        }
    }
}

/*----------------------------------------
sub_tx
Descrição: envia o gc_buffer para a saída serial
Entrada: c_max, indica o nº de dados a serem
 enviados
----------------------------------------*/
void sub_tx(uchar c_max, uchar *c_buffer) {
    uchar c_i;

    //espera o buffer ser esvaziado
    while (!TXSTAbits.TRMT);

    for (c_i = 0; c_i < c_max; c_i++) {
        while (!TRMT);
        TXREG = c_buffer[c_i];
    }
    //espera o buffer ser esvaziado
    while (!TXSTAbits.TRMT);
}

/*----------------------------------------
fcn_crc
Descrição: calcula o CRC da matriz gc_buffer.
Entrada: c_max, indica o nº de dados a serem
 pegos da matriz gc_buffer para o cálculo do CRC.
----------------------------------------*/
uint f_crc(uchar c_max, uchar *c_buffer) {
    uint i_CRC = 0xffff;
    uchar c_i, c_j;

    for (c_i = 0; c_i < c_max; c_i++)//6bytes
    {
        i_CRC = i_CRC^c_buffer[c_i];
        for (c_j = 0; c_j < 8; c_j++) {
            if (!(i_CRC & 1))
                i_CRC = i_CRC >> 1; //antes eram 2 rotações. Tenho q verificar isto
            else {
                i_CRC = i_CRC >> 1;
                i_CRC = i_CRC^0xa001;
            }
        }
    }
    return i_CRC;
}

int le_ad(void) {
    uint8_t adconv;

    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    adconv = ADRESH;
    adconv <<= 8;
    adconv += ADRESL;
    return adconv;
}