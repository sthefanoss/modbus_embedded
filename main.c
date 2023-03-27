#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>
#include "lcd.h"
#include "declaracoes.h"

void sub_tx(uchar, uchar *);
uint f_crc(uchar, uchar *);
int le_ad(void);
void __interrupt() isr(void);

uchar gc_rx[20], gc_c = 0;
uint16_t gi_adconv = 0;
uint8_t gi_pisca = 100;
uchar c_texto[16], c_i;
unsigned int i_crc, i_crc2;

void main(void) {
    GIE = 0;
    TRISC = 0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;

    //    TMR1H=55536/256;
    //    TMR1H=55536%256;
    TMR1 = 55536;
    TMR1IE = 1;
    TMR1ON = 1;

    BRGH = 1;
    SPBRG = SPBRG_INIT; //define baud rate
    SYNC = 0; //modo assincrono
    SPEN = 1; //hab serial
    RX9 = 0; //modo 8bits
    CREN = 1; //hab. recepção
    TXEN = 1; //hab. transmissao
    PEIE = 1; //hab. int. de perféricos
    RCIE = 1; //int. da recepção
    TXIE = 0; //int. da transmissao

    CCP1CONbits.CCP1M = 0;
    GIE = 1;

    //configura conversor A/D
    TRISA = 3; //SELECIONA 1 CANAL
    ADCON1 = 0X84; //seleciona o canal 0

    ADCON0bits.CHS = 1;
    ADCON0bits.ADCS = 5;
    //    ADCON0 = 0x40; //seleciona FOSC/8
    ADON = 1;

    RC1 = 0;
    RC2 = 0;
    lcd_init();
    __delay_ms(500);
    lcd_str(" teste");
    while (1) {
        //        if (gi_pisca == 100) {
        //            lcd_str("\f");
        //            sprintf(c_texto, "%u", gi_adconv);
        //            lcd_str(c_texto);
        //            RB1 ^= 1;
        //        }
        if (gc_c >= 8) {
            //sub_tx(8, gc_rx);
            //sprintf(c_texto," \f");
            lcd_str("\f");
            for (c_i = 0; c_i < 8; c_i++) {
                sprintf(c_texto, "%02X", gc_rx[c_i]);
                lcd_str(c_texto);
            }
            gc_c = 0;
            if (gc_rx[0] == 1) {
                switch (gc_rx[1]) {
                    case 5:
                        i_crc = gc_rx[7];
                        i_crc <<= 8;
                        i_crc += gc_rx[6];
                        i_crc2 = f_crc(6, gc_rx);


                        if (i_crc == i_crc2) {

                            if (gc_rx[2] == 0 && gc_rx[3] == 9) {

                                if (gc_rx[4] == 0xff && gc_rx[5] == 0) {
                                    RC2 = 1;

                                }
                                if (gc_rx[4] == 0 && gc_rx[5] == 0) {
                                    RC2 = 0;
                                }
                                __delay_ms(50);
                                sub_tx( 8,gc_rx);
                            } else if (gc_rx[2] == 0 && gc_rx[3] == 10) {

                                if (gc_rx[4] == 0xff && gc_rx[5] == 0) {
                                    RC0 = 1;

                                }
                                if (gc_rx[4] == 0 && gc_rx[5] == 0) {
                                    RC0 = 0;
                                }
                                __delay_ms(50);
                                sub_tx( 8,gc_rx);
                            } else {//configura mensagem de erro

                                gc_rx[1] |= 0x80;
                                gc_rx[2] = 2;
                                i_crc2 = f_crc(3, gc_rx);
                                gc_rx[3] = i_crc2;
                                gc_rx[4] = i_crc2 >> 8;
                                __delay_ms(50);
                                sub_tx( 5,gc_rx);

                            }

                        }

                        break;
                }
            }

        }
        //        __delay_ms(100);
        //        RB1 ^= 1;
    }
    return;
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