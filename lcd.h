#ifndef LCD_H
#define LCD_H

#include "declarations.h"
#include <stdio.h>
#include <pic.h>

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

uchar lcdBuffer[16];

void lcd_init(void);
void lcd_cmd(unsigned char val);
void lcd_dat(unsigned char val);
void lcd_str(const char* str);
void printBufferInLcd(const Buffer*);
#endif