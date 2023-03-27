#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>
#include "declarations.h"
#include "lcd.h"
#include "serial_port.h"

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
    CREN = 1; //hab. recep��o
    TXEN = 1; //hab. transmissao
    PEIE = 1; //hab. int. de perf�ricos
    RCIE = 1; //int. da recep��o
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