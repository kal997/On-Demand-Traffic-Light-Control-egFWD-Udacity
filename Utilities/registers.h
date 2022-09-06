/*
 * registers.h
 *
 * Created: 9/6/2022 2:09:42 PM
 *  Author: KHALED
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************************************************************************/
/*                              DIO_Registers                           */
/************************************************************************/


// PortA
#define DDRA (*(volatile unsigned char*)0x3A)
#define PORTA (*(volatile unsigned char*)0x3B)
#define PINA (*(volatile unsigned char*)0x39)

// PortB
#define DDRB (*(volatile unsigned char*)0x37)
#define PORTB (*(volatile unsigned char*)0x38)
#define PINB (*(volatile unsigned char*)0x36)

//PortC
#define DDRC (*(volatile unsigned char*)0x34)
#define PORTC (*(volatile unsigned char*)0x35)
#define PINC (*(volatile unsigned char*)0x33)

//PortD
#define DDRD (*(volatile unsigned char*)0x31)
#define PORTD (*(volatile unsigned char*)0x32)
#define PIND (*(volatile unsigned char*)0x30)







#endif /* REGISTERS_H_ */