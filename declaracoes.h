/* 
 * File:   globais.h
 * Author: julio
 *
 * Created on 14 de Agosto de 2015, 14:57
 */


// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define BAUD 9600L
#define _XTAL_FREQ 8000000L

#define SPBRG_INIT (_XTAL_FREQ/(16UL*BAUD) - 1)//configuração da taxa serial, p/ baixa frequência
#define uchar unsigned char
#define uint unsigned int
