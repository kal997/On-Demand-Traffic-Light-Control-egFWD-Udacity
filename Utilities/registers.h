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
/************************************************************************************************/
/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52)
#define TCCR0   (*(volatile unsigned char*)0x53)
/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)
#define TIFR    (*(volatile unsigned char*)0x58)
#define TIMSK   (*(volatile unsigned char*)0x59)
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define OCR0    (*(volatile unsigned char*)0x5C)
/****************************************************************************************************/

/*TIMER 1*/


#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)
#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B       (*(volatile unsigned char*)0x4E)
#define TCCR1A        (*(volatile unsigned char*)0x4F)

#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)
/************************************************************************/
/************************************************************************/
/*                                TIMER 0                               */
/************************************************************************/
/* Timer/Counter0 Compare Match */
#define TIMER0_OC_vect		__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect		__vector_11

/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52) // timer counter register

#define TCCR0   (*(volatile unsigned char*)0x53) // Timer counter control register
/* TCCR0 PINS */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)

#define TIFR    (*(volatile unsigned char*)0x58) // timer interrupt flag register
#define TOV0 0
#define OCF0 1


#define TIMSK   (*(volatile unsigned char*)0x59) //Timer interrupt mask register
/* TIMSK  PINS*/
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define OCR0    (*(volatile unsigned char*)0x5C)


#endif /* REGISTERS_H_ */