/*
 * registers.h
 *
 * Created: 9/6/2022 2:09:42 PM
 *  Author: KHALED
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************************************************************************/
/*                              DIO Registers                           */
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


/************************************************************************/
/*                      EXTERNAL INTERRUPTS Registers                   */
/************************************************************************/
/*
 * Interrupt 0 Sense Control
ISC01 ISC00 Description
  0     0   The low level of INT0 generates an interrupt request.
  0     1   Any logical change on INT0 generates an interrupt request.
  1     0   The falling edge of INT0 generates an interrupt request.
  1     1   The rising edge of INT0 generates an interrupt request.
 * 
 */

/*
 * Interrupt 1 Sense Control
ISC11 ISC10 Description
  0     0   The low level of INT1 generates an interrupt request.
  0     1   Any logical change on INT1 generates an interrupt request.
  1     0   The falling edge of INT1 generates an interrupt request.
  1     1   The rising edge of INT1 generates an interrupt request.
 *
 */

/* INT2_State
	falling=0
	rising=1
*/

#define MCUCSR (*(volatile unsigned char*)0x54)
#define ISC2 6

#define MCUCR (*(volatile unsigned char*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR (*(volatile unsigned char*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR  (*(volatile unsigned char*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5



/************************************************************************/
/*			             EXTERNAL INTERRUPTS Vectors                    */
/************************************************************************/
#  define __INTR_ATTRS used, externally_visible
#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
void vector (void)

/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3

/************************************************************************/
/*                         GLOBAL INTERRUPT ENABLE/DISABLE              */
/************************************************************************/
# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)


#endif /* REGISTERS_H_ */