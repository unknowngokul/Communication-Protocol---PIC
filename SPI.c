/*
 * File:   SPI.c
 * Author: Ramya
 *
 * Created on December 16, 2023, 5:28 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
void SPI(char);
void LCD(char,char);
void enable();
void delay(int);
void str(char*);
void main(void)
{
    PORTC=PORTD=PORTE=TRISD=TRISE=0X00;
    TRISC = 0X10;
    PORTA=0X00;
    TRISA=0X09;
    ANSEL = ANSELH = 0X00;
    SSPSTAT = 0X80;
    SSPCON = 0X20;
    LCD(0,0X38);
    LCD(0,0X0F);
    LCD(0,0X80);
    LCD(1,'A');
    while(1)
    {
        if(RA0==1)
        {
            while(RA0);
            str("GOKUL");
        }
        delay(10000);
        LCD(0,0XC0);
        LCD(1,'S');
    }
}
void LCD(char i,char ch)
{
    RE0 = i;
    PORTD = ch;
    enable();
}
void str(char *str)
{
    while(*str)
    {
        SPI(*str++);
    }
    
}
void SPI(char str1)
{
    SSPBUF = str1;
    while(SSPIF==0);
    SSPIF=0;
}
void enable()
{
    RE1=1;
    delay(5000);
    RE1=0;
    delay(5000);
}
void delay(int i)
{
    while(i--);
}