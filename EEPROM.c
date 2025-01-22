/*
 * File:   EEPROM.c
 * Author: Ramya
 *
 * Created on January 24, 2024, 11:22 PM
 */

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
#pragma config WRT = OFF



#include <xc.h>
void LCD(char,char);
void enable();
void delay(int);
void write_eeprom(char,char);
void read_eeprom(char);
char data;
void main(void) 
{
    PORTD=PORTA=PORTC=TRISC=TRISD=ANSEL=ANSELH=0X00;
    TRISA=0X0F;
    LCD(0,0X02);
    LCD(0,0X28);
    LCD(0,0X0E);
    LCD(0,0X80);
    while(1)
    {
        if(RA0==1)
        {
            while(RA0==1);
            write_eeprom(1,'5');
            write_eeprom(2,'6');
            write_eeprom(3,'7');
        }
        if(RA1==1)
        {
            while(RA1==1);
            read_eeprom(1);
        }
        if(RA2==1)
        {
            while(RA2==1);
            read_eeprom(2);
        }
        if(RA3==1)
        {
            while(RA3==1);
            read_eeprom(3);
        }
        LCD(0,0X80);
        LCD(1,data);
    }
}
void write_eeprom(char ad,char data1)
{
    EEADR=ad;
    EEDATA=data1;
    EEPGD=0;
    WREN=1;
    EECON2=0X55;
    EECON2=0XAA;
    WR=1;
    while(EEIF==0);
    EEIF=0;
}
void read_eeprom(char ad) 
{
    EEADR=ad;
    EEPGD=0;
    RD=1;
    data = EEDATA;
}
void LCD(char i,char data2)
{
    RC6 = i;
    PORTD = (data2&0xf0);
    enable();
    PORTD = (data2&0x0f)<<4;
    enable();
}
void enable()
{
    RC7 = 1;
    delay(1000);
    RC7 = 0;
    delay(1000);
}
void delay(int i)
{
    while(i--);
}


