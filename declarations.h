/*
 * File:   globais.h
 * Author: julio
 *
 * Created on 14 de Agosto de 2015, 14:57
 */

#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <stdint.h>
#define BUFFER_SIZE 20
#define DEVICE_ADDRESS 0x01
#define BAUD 9600L
#define _XTAL_FREQ 8000000L
#define SPBRG_INIT (_XTAL_FREQ/(16UL*BAUD) - 1)//configuração da taxa serial, p/ baixa frequência
#define uchar unsigned char
#define uint unsigned int
#define joinHL(H, L) (uint16_t) ((H << 8) + L) 

typedef struct {
    uchar size;
    uchar data[BUFFER_SIZE];
} Buffer;

typedef struct {
    uchar address;
    uchar function;
    uchar data[BUFFER_SIZE - 4];
    uchar dataSize;
    uchar crcValid;
} Request;

typedef struct {
    uchar address;
    uchar function;
    uchar data[BUFFER_SIZE - 4];
    uchar dataSize;
} Response;
#endif