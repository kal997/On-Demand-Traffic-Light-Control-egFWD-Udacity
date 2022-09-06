/*
 * bit_manipulation.h
 *
 * Created: 9/6/2022 2:09:00 PM
 *  Author: KHALED
 */ 


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_


#define SET_BIT(REG, BIT) (REG|=(1<<BIT))
#define CLR_BIT(REG, BIT) (REG&=(~(1<<BIT)))
#define GET_BIT(REG, BIT) (1&(REG>>BIT))
#define TOG_BIT(REG, BIT) (REG^=(1<<BIT))
#define WRT_BIT(REG, BIT, VAL) ((REG = REG&~(1<<BIT)|(VAL<<BIT)))






#endif /* BIT_MANIPULATION_H_ */