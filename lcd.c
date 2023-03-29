#include "lcd.h"

void lcd_wr(unsigned char val) {
    LPORT = val;
}

void lcd_cmd(unsigned char val) {
    LENA = 1;
    lcd_wr(val);
    LDAT = 0;
    __delay_ms(3);
    LENA = 0;
    __delay_ms(3);
    LENA = 1;
}

void lcd_dat(unsigned char val) {
    LENA = 1;
    lcd_wr(val);
    LDAT = 1;
    __delay_ms(3);
    LENA = 0;
    __delay_ms(3);
    LENA = 1;
}

void lcd_init(void) {
    LENA = 0;
    LDAT = 0;
    __delay_ms(20);
    LENA = 1;

    lcd_cmd(L_CFG);
    __delay_ms(5);
    lcd_cmd(L_CFG);
    __delay_ms(1);
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_OFF);
    lcd_cmd(L_ON); //liga;;;;
    lcd_cmd(L_CLR); //limpa
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_L1);
}

void lcd_str(const char* str) {
    unsigned char i = 0;

    while (str[i] != 0) {
        if (str[i] == '\f') {
            lcd_cmd(L_CLR); //limpa
        } else {
            lcd_dat(str[i]);
        }

        i++;
    }
}

void printBufferInLcd(const Buffer* buffer) {
    lcd_str("\f");
    for (uchar i = 0; i < buffer->size; i++) {
        sprintf(lcdBuffer, "%02X", buffer->data[i]);
        lcd_str(lcdBuffer);
    }
}
