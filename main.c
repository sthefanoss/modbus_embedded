#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>
#include "declarations.h"
#include "request_handler.h"
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
    CREN = 1; //hab. recepcao
    TXEN = 1; //hab. transmissao
    PEIE = 1; //hab. int. de perfericos
    RCIE = 1; //int. da recepcao
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
    lcd_str("modbus");
    while (1) {
        // Verifica tamanho do buffer.
        // Espera ate satisfazer condicao.
        if (!isRequestReady()) continue;

        // Limpa lcd e printa entrada na primeira linha.
        // Nao mostra CRC
        lcd_str("\f");
        printBufferInLcd(&buffer);

        // Passa os dados do buffer para a estrutura de requisicao.
        desserializeRequest(&buffer, &request);


        // Valida crc.
        // Limpa buffer e ignora se estiver errado.
        if (!request.crcValid) {
            buffer.size = 0;
            continue;
        }

        // Verifica se o comando eh para este dispositivo.
        // Limpa buffer e ignora se nao for. Broadcast nao tratado.
        if (request.address != DEVICE_ADDRESS) {
            buffer.size = 0;
            continue;
        }

        // Trata cada uma das requisicoes.
        handleRequest(&request, &response);

        // Passa a estrutura da resposta para o buffer.
        serializeResponse(&buffer, &response);

        // Printa saida na segunda linha
        // Nao mostra CRC
        lcd_cmd(L_L2);
        printBufferInLcd(&buffer);

        // Responde a requisicao.
        __delay_ms(50);
        submit();
    }
}
