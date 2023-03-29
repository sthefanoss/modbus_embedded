#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>
#include "declarations.h"
#include "handlers.h"
#include "lcd.h"
#include "serial_port.h"
#include "serialization.h"

Request request;
Response response;

void main(void) {
    GIE = 0;
    TRISC = 0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
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

    buffer.size = 0;
    lcd_init();
    __delay_ms(500);
    lcd_str(" teste 1");
    while (1) {
        if (!isRequestReady()) continue;

        desserializeRequest(&buffer, &request);
        printBufferInLcd(&buffer);

        if (!request.crcValid) {
            buffer.size = 0;
            continue;
        }

        if (request.address != DEVICE_ADDRESS) {
            buffer.size = 0;
            continue;
        }

        updateResponse(&request, &response);

        switch (request.function) {
            case 1:
                handleRequest1(&request, &response);
                break;

            case 3:
                handleRequest3(&request, &response);
                break;

            case 5:
                handleRequest5(&request, &response);
                break;

            case 6:
                handleRequest6(&request, &response);
                break;

            case 15:
                handleRequest15(&request, &response);
                break;

            case 16:
                handleRequest16(&request, &response);
                break;

            default:
                handleInvalidRequest(&request, &response);
                break;
        }

        //        serializeResponse(&buffer, &response);
        __delay_ms(50);
        submit();
    }
}
