#include "declaracoes.h"
//#define _XTAL_FREQ 20000000L

#define LENA  RE1
#define LDAT  RE2
#define LPORT PORTD


#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void lcd_init(void);
void lcd_cmd(unsigned char val);
void lcd_dat(unsigned char val);
void lcd_str(const char* str);

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
