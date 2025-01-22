/*
 * File:   SPI Slave2.c
 * Author: Ramya
 *
 * Created on December 20, 2023, 11:31 AM
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
void slave2();
void LCD(char,char);
char value='A';
void main(void) 
{
    PORTA=PORTB=PORTC=PORTD=TRISB=TRISD=0X00;
    TRISA = 0X20;
    TRISC = 0X18;
    ANSEL=ANSELH=0X00;
    SSPSTAT = 0X00;
    SSPCON = 0X24;
    SSPBUF = 0;
    LCD(0,0x38);
    LCD(0,0x0E);
    LCD(0,0x80);
    while(1)
    {
        slave2();
        if(value=='V')
        {
            RB0 = ~RB0;
        }
        LCD(1,value);
    }
}
void slave2()
{
    while(SSPIF==0);
    value = SSPBUF;
    SSPIF = 0;
}
void LCD(char i,char ch)
{
    RC6 = i;
    PORTD = ch;
    RC7 = 1;
    for(int i=0;i<5000;i++);
    RC7 = 0;
    for(int i=0;i<5000;i++);
}